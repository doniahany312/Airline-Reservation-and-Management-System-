#include"../Inc/flight_management.hpp"

void flightManagement::addFlight()
{
    flight newFlight;
    std::cout << "Enter Flight Number: ";
    std::cin >> newFlight.flightNo;
    std::cin.ignore();

    std::cout << "Enter Origin: ";
    std::getline(std::cin, newFlight.origin);

    std::cout << "Enter Destination: ";
    std::getline(std::cin, newFlight.destination);

    std::cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
    std::string departureStr;
    std::getline(std::cin, departureStr);
    std::istringstream departureStream(departureStr);
    std::tm departureTm = {};
    departureStream >> std::get_time(&departureTm, "%Y-%m-%d %H:%M");
    if (departureStream.fail()) {
        std::cerr << "Failed to parse departure date and time.\n";
        return;
    }
    newFlight.departure = std::mktime(&departureTm);

    std::cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
    std::string arrivalStr;
    std::getline(std::cin, arrivalStr);
    std::istringstream arrivalStream(arrivalStr);
    std::tm arrivalTm = {};
    arrivalStream >> std::get_time(&arrivalTm, "%Y-%m-%d %H:%M");
    if (arrivalStream.fail()) {
        std::cerr << "Failed to parse arrival date and time.\n";
        return;
    }
    newFlight.arrival = std::mktime(&arrivalTm);

    std::cout << "Enter Aircraft Type: ";
    std::getline(std::cin, newFlight.aircraft);
//the no of seats is how a variable???

    std::cout << "Enter Status (Scheduled/Delayed/Canceled): ";
    std::getline(std::cin, newFlight.status);

    flights.push_back(newFlight);
    std::cout << "Flight added successfully.\n";
}