#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../Inc/database.hpp"
#include "../Inc/json.hpp" // Include the nlohmann/json library

using json = nlohmann::json;

// Helper function to parse date-time strings into time_t
time_t parseDateTime(const std::string& dateTimeStr) {
    std::tm tm = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date-time: " + dateTimeStr);
    }
    return std::mktime(&tm);
}

// Helper function to format time_t as a date-time string
std::string formatDateTime(time_t time) {
    std::ostringstream ss;
    std::tm* tm = std::localtime(&time);
    ss << std::put_time(tm, "%Y-%m-%d %H:%M");
    return ss.str();
}

std::string PasswordHasher::hash(const std::string &password)
{
    unsigned int hash1 = 2166136261u; // FNV offset basis
    unsigned int hash2 = 0x811C9DC5;  // Another magic number

    for (size_t i = 0; i < password.length(); ++i)
    {
        char c = password[i];
        hash1 = (hash1 ^ (c + i)) * 16777619;
        hash2 = ((hash2 << 5) | (hash2 >> 27)) ^ (c * 31 + i);
        hash2 += hash1 ^ (c << 3);
    }

    // Combine both hashes into one 64-bit value
    unsigned long long finalHash = ((unsigned long long)hash1 << 32) | hash2;

    // Convert to hex string
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(16) << finalHash;

    return oss.str();
}

void Database::fetchData() {
    std::ifstream file("database.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open database.json" << std::endl;
        return;
}

    json jsonData;
    file >> jsonData;

    // Parse administrators
    for (const auto& admin : jsonData["admins"]) {
        administrator::admins.emplace_back(
            admin["username"].get<std::string>(),
            PasswordHasher::hash(admin["password"].get<std::string>()), // Hash the password
            admin["name"].get<std::string>(),
            admin["id"].get<std::string>()
        );
    }

    // Parse booking agents
    for (const auto& agent : jsonData["bookingAgents"]) {
        bookingAgent::bookingAgents.emplace_back(
            agent["username"].get<std::string>(),
            PasswordHasher::hash(agent["password"].get<std::string>()), // Hash the password
            agent["name"].get<std::string>(),
            agent["id"].get<std::string>()
        );
    }


    // Parse passengers
    for (const auto& pass : jsonData["passengers"]) {
        passenger::passengers.emplace_back(
            pass["username"].get<std::string>(),
            PasswordHasher::hash(pass["password"].get<std::string>()), // Hash the password
            pass["name"].get<std::string>(),
            pass["id"].get<std::string>()
        );
    }

    // Parse aircrafts
    for (const auto& ac : jsonData["aircrafts"]) {
        aircraft::aircrafts.emplace_back(
            ac["type"].get<std::string>(),
            ac["seatsNo"].get<int>(),
            maintenance{}, // Placeholder for maintenance
            ac["availability"].get<bool>()
        );
    }

    // Parse flights
    for (const auto& fl : jsonData["flights"]) {
        // Find the corresponding aircraft by type
        std::shared_ptr<aircraft> assignedAircraft = nullptr;
        for (auto& ac : aircraft::aircrafts) {
            if (ac.type == fl["aircraftType"].get<std::string>()) {
                assignedAircraft = std::make_shared<aircraft>(ac);
                break;
            }
        }

        if (!assignedAircraft) {
            std::cerr << "Aircraft type not found for flight: " << fl["flightNo"].get<std::string>() << std::endl;
            continue;
        }

        flightManagement::flights.emplace_back(
            fl["flightNo"].get<std::string>(),
            fl["origin"].get<std::string>(),
            fl["destination"].get<std::string>(),
            parseDateTime(fl["departure"].get<std::string>()),
            parseDateTime(fl["arrival"].get<std::string>()),
            fl["status"].get<std::string>(),
            assignedAircraft
        );
    }

}

void Database::saveData() {
    json jsonData;

    // Serialize administrators
    for (const auto& admin : administrator::admins) {
        jsonData["admins"].push_back({
            {"username", admin.username},
            {"password", admin.password}, // Save the hashed password
            {"name", admin.name},
            {"id", admin.userId}
        });
    }

    // Serialize booking agents
    for (const auto& agent : bookingAgent::bookingAgents) {
        jsonData["bookingAgents"].push_back({
            {"username", agent.username},
            {"password", agent.password}, // Save the hashed password
            {"name", agent.name},
            {"id", agent.userId}
        });
    }

    // Serialize passengers
    for (const auto& pass : passenger::passengers) {
        jsonData["passengers"].push_back({
            {"username", pass.username},
            {"password", pass.password}, // Save the hashed password
            {"name", pass.name},
            {"id", pass.userId}
        });
    }

    // Serialize aircrafts
    for (const auto& ac : aircraft::aircrafts) {
        jsonData["aircrafts"].push_back({
            {"type", ac.type},
            {"seatsNo", ac.seatsNo},
            {"availability", ac.availability}
        });
    }

    // Serialize flights
    for (const auto& fl : flightManagement::flights) {
        jsonData["flights"].push_back({
            {"flightNo", fl.flightNo},
            {"origin", fl.origin},
            {"destination", fl.destination},
            {"departure", formatDateTime(fl.departure)},
            {"arrival", formatDateTime(fl.arrival)},
            {"status", fl.status},
            {"aircraftType", fl.craft->type} // Save the aircraft type
        });
    }

    std::ofstream file("database.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open database.json for writing" << std::endl;
        return;
    }

    file << jsonData.dump(4); // Pretty print with 4 spaces
    std::cout << "Data successfully saved to database.json" << std::endl;
}