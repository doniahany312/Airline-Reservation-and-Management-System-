// #include "../Inc/system.hpp"

#include "../Inc/flight_management.hpp"
#include <limits>
#include <algorithm>
#include <fstream> // Include for file handling
#include <iostream> // Include for error handling

int reservation::resvId = 0;
std::unordered_map<int, std::shared_ptr<reservation>> reservation::reservations = {};

std::string reservation::add(std::string passengerId)//std::shared_ptr<passenger> passengerPtr
{
    std::string flightNo, seatNo;
    auto passengerIt = std::find_if(passenger::passengers.begin(), passenger::passengers.end(),
                                [passengerId](const passenger& p) { return p.userId == passengerId; });

if (passengerIt == passenger::passengers.end()) {
    std::cerr << "Error: Passenger not found in passengers list!" << std::endl;
    return "Failed";
}

// Create a shared_ptr to the object in the vector
std::shared_ptr<passenger> passengerPtr(&(*passengerIt), [](passenger*) {
    // Custom deleter does nothing
});
    std::cout << "Enter the Flight Number: ";
    std::getline(std::cin, flightNo);
    auto seats = flightManagement::getAvailableSeats(flightNo);
    if (seats.empty())
    {
        std::cout << "Flight not found or no seats available" << std::endl;
        return "Failed";
    }
    std::cout << "Enter Seat Number (e.g., 14C): ";
    std::getline(std::cin, seatNo);
    if (!seatNo.empty())
    {

        if (seats.find(seatNo) != seats.end())
        {
            std::string method, details;
            std::cout << "Seat " << seatNo << " is available." << std::endl;
            auto& reservedFlight = flightManagement::getFlight(flightNo); // Get a reference to the original flight
            std::shared_ptr<flight> flightPtr = std::make_shared<flight>(reservedFlight); // Use the same shared_ptr
            std::cout << "Enter Payment Method (Credit Card/Cash/PayPal): ";
            std::getline(std::cin, method);
            if (method != "Credit Card" && method != "Cash" && method != "PayPal")
            {
                std::cout << "Invalid Payment method!" << std::endl;
                return "Failed";
            }
            std::cout << "Enter Payment Details: ";
            std::getline(std::cin, details); // wrong : no check for details

            ;
            std::shared_ptr<reservation> sptr = std::make_shared<reservation>(reservation(passengerPtr, flightPtr, payment(details, 150, method), seatNo));
            // reservation::add(sptr);
            reservations.emplace(sptr.get()->id,sptr);
            reservedFlight.seatmap[seatNo]=1;//not available
            passengerPtr.get()->history.push_back(sptr.get()->id);
            // passenger::passengers[passengerPtr.get().i]
            return "R" + std::to_string(sptr.get()->id);
            
        }
        else
        {
            std::cout << "Seat " << seatNo << " is not available." << std::endl;
            return"Failed";
        }
    }

    else
    {
        std::cout << "Seat number is empty! " << std::endl;
        return"Failed";
    }
}
std::vector<std::string> Reporting::reports = {};
void reservation::cancel(int reservationId)
{
    auto& originalFlight = flightManagement::getFlight(reservations[reservationId].get()->reservedFlight.get()->flightNo);
    originalFlight.seatmap[reservations[reservationId].get()->seat] = 0; // Make the seat available again
    reservations[reservationId].get()->status="Canceled";
    std::cout<<"Reservation R"<<reservationId<<" has been sucessfully canceled."<<std::endl;
    std::cout<<"Refund Amount: "<<reservations[reservationId].get()->paymentMethod.amount<<" has been credited to your "<<reservations[reservationId].get()->paymentMethod.type<<" account."<<std::endl;
}

std::vector<reservation> reservation::getHistory(std::vector<int> ids)
{
    std::vector<reservation> results;
    for(auto id:ids){
    results.push_back(*reservations[id].get());
    }
    return results;
}

reservation& reservation::getReservation(int reservationId)
{
    auto it = reservations.find(reservationId);
    if (it == reservations.end()) {
        throw std::out_of_range("Reservation ID not found.");
    }
    return *(it->second);
}

void maintenance::addLog(const std::string& description){
    auto getCurrentTimeString = []() -> std::tm* {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        return localTime;
    };

    std::tm* currentTime = getCurrentTimeString();
    logs.push_back(std::make_pair(description, currentTime));
}

void Reporting::report(std::string entry)
{Reporting::reports.push_back(entry);}

void Reporting::generateReport()
{
    // Create the file explicitly before opening it in write mode
    std::ofstream createFile("report.txt", std::ios::app); // Open in append mode to ensure the file is created
    if (!createFile) {
        std::cerr << "Error: Unable to create the report file!" << std::endl;
        return;
    }
    createFile.close(); // Close the file after creating it

    // Open the file in write mode
    std::ofstream reportFile("report.txt");
    if (!reportFile.is_open()) {
        std::cerr << "Error: Unable to open the report file for writing!" << std::endl;
        return;
    }

    // Write each entry from the reports vector to the file
    for (const auto& entry : Reporting::reports) {
        reportFile << entry << std::endl;
    }

    // Close the file
    reportFile.close();

    std::cout << "Report generated successfully in 'report.txt'." << std::endl;
}