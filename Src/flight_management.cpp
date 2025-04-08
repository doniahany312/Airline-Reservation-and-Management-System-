#include "../Inc/flight_management.hpp"
#include <algorithm>                                // For std::find_if
std::vector<flight> flightManagement::flights = {}; // hass all flights that is there

void flightManagement::displayAdministratorMenu()
{
    int x;
    bool wrongChoice = true;
    while (wrongChoice)
    {
        std::cout << "--- Manage Flights ---" << std::endl
                  << "1. Add New Flight" << std::endl
                  << "2. Update Existing Flight" << std::endl
                  << "3. Remove Flight" << std::endl
                  << "4. View All Flights" << std::endl
                  << "5. Back to Main Menu" << std::endl;

        std::cin >> x;
        switch (x)
        {
        case 1: // add new flight
            addFlight();
            break;
        case 2: // update existing flight
            updateFlight();
            break;
        case 3: // remove flight
            removeFlight();
            break;
        case 4: // view all flights
            for (auto flight : flights)
            {
                flight.print();
            }
            break;
        case 5:
            wrongChoice = false;
            return;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
        }
    }
}

void flightManagement::addFlight()
{
    flight newFlight;
    std::cin.ignore(); // Clear input buffer
    std::cout << "Enter Flight Number: ";
    std::getline(std::cin, newFlight.flightNo);
//checks for flight numebr
auto it=std::find_if(flights.begin(),flights.end(),[newFlight](const flight& f){return f.flightNo==newFlight.flightNo;});
if(it!=flights.end()){std::cout<<"Error:Flight number already exists!!"<<std::endl;return;}
//possible point for memory leak??!!

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
    if (departureStream.fail())
    {
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
    if (arrivalStream.fail())
    {
        std::cerr << "Failed to parse arrival date and time.\n";
        return;
    }
    newFlight.arrival = std::mktime(&arrivalTm);

    std::cout << "Enter Aircraft Type: ";
    std::getline(std::cin, newFlight.aircraft);

    std::cout << "Enter Status (Scheduled/Delayed/Canceled): ";
    std::getline(std::cin, newFlight.status);

    flightManagement::flights.push_back(newFlight);
    std::cout << "Flight added successfully.\n";
}

void flightManagement::updateFlight()
{
    std::string flightNo;
    std::cin.ignore();
    std::cout << "Enter Flight Number: ";
    std::getline(std::cin, flightNo);

    auto it = std::find_if(flights.begin(), flights.end(), [flightNo](const flight &f)
                           { return f.flightNo == flightNo; });
    if (it != flights.end())
    {
        flight &flight_ref = *it;
        int choice;
        // flight found
        //  what to update
        std::cout << "--- Update Menu ---" << std::endl
                  << "1. Update Origin" << std::endl
                  << "2. Update Destination" << std::endl
                  << "3. Update Departure" << std::endl
                  << "4. Update Arrival" << std::endl
                  << "5. Update Aircraft" << std::endl;
        // << "6. Back to Main Menu" << std::endl;
        std::cin >> choice;
        std::cin.ignore();

        std::string departureStr, arrivalStr;
        std::istringstream departureStream, arrivalStream;
        std::tm departureTm = {}, arrivalTm = {};

        switch (choice)
        {
        case 1:
            /* code */
            std::cout << "Enter Origin: ";
            std::getline(std::cin, flight_ref.origin);
            std::cout << "Origin updated! " << std::endl;
            break;

        case 2:
            std::cout << "Enter Destination: ";
            std::getline(std::cin, flight_ref.destination);
            std::cout << "Destination updated! " << std::endl;
            break;

        case 3:
            std::cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, departureStr);
            departureStream.str(departureStr);
            departureStream.clear();
            departureStream >> std::get_time(&departureTm, "%Y-%m-%d %H:%M");
            if (departureStream.fail())
            {
                std::cerr << "Failed to parse departure date and time.\n";
                return;
            }
            flight_ref.departure = std::mktime(&departureTm);
            std::cout << "Departure date and time updated! " << std::endl;
            break;

        case 4:
            std::cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, arrivalStr);
            arrivalStream.str(arrivalStr);
            arrivalStream.clear();
            arrivalStream >> std::get_time(&arrivalTm, "%Y-%m-%d %H:%M");
            if (arrivalStream.fail())
            {
                std::cerr << "Failed to parse arrival date and time.\n";
                return;
            }
            flight_ref.arrival = std::mktime(&arrivalTm);
            std::cout << "Arrival date and time updated! " << std::endl;
            break;

        case 5:
            std::cout << "Enter Aircraft: ";
            std::getline(std::cin, flight_ref.aircraft);
            std::cout << "Aircraft updated! " << std::endl;
            break;

        default:
            std::cout << "Invalid choice! " << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "Flight with Flight No " << flightNo << " not found." << std::endl;
    }
}

void flightManagement::removeFlight()
{

    std::string flightNo;
    std::cin.ignore();
    std::cout << "Enter Flight Number: ";
    std::getline(std::cin, flightNo);
    // Use std::find_if to locate the user by userId
    auto it = std::find_if(flights.begin(), flights.end(), [flightNo](const flight &f)
                           {
                               return f.flightNo == flightNo; // Match userId
                           });

    if (it != flights.end())
    {
        flights.erase(it);
        std::cout << "Flight removed succesfully!" << std::endl;
    }
    else
    {
        std::cerr << "Flight not found!" << std::endl;
        return;
    }
}

void flight::print() const
{ // std::tm tmstrct;
    // int flightNo;
    // std::string origin;
    // std::string destination;
    // time_t departure;
    // time_t arrival;
    // std::string status; // 0:Scheduled  1:Delayed 2:cancelled
    // std::string aircraft;
    // std::map<int, int> seatmap;
    auto timeToString = [](time_t time) -> std::string {
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&time));
        return std::string(buffer);
    };
    std::cout << "Flight Number: " << flightNo << std::endl
              << "Origin: " << origin << std::endl
              << "Destination: " << destination << std::endl;
    std::cout << "Departure Time: " << timeToString(departure) << std::endl
              << "Arrival Time: " << timeToString(arrival) << std::endl
              << "Aircraft: " << aircraft << std::endl;
}
std::vector<flight> flightManagement::searchFlights()
{
    std::string origin,destination,departureDateStr;
    std::tm departureDateTm = {};
    std::vector<flight> matchingFlights;
//std::string origin, std::string destination, std::string departure
std::cin.ignore();
std::cout<<"--- Search Flights ---"<<std::endl
         <<"Enter Origin:";
std::getline(std::cin,origin);
std::cout<<"Enter Destination:";
std::getline(std::cin,destination);
std::cout<<"Enter Departure Date (YYYY-MM-DD):";
//search by date
std::getline(std::cin, departureDateStr);
std::istringstream departureDateStream(departureDateStr);
departureDateStream >> std::get_time(&departureDateTm, "%Y-%m-%d");
if (departureDateStream.fail())
{
    std::cerr << "Failed to parse departure date.\n";
    return {};
}
time_t departureDate = std::mktime(&departureDateTm);

for (const auto &f : flights)
{
    std::tm flightDepartureTm = *std::localtime(&f.departure);
    
    if (flightDepartureTm.tm_year == departureDateTm.tm_year &&
        flightDepartureTm.tm_mon == departureDateTm.tm_mon &&
        flightDepartureTm.tm_mday == departureDateTm.tm_mday &&
        f.origin == origin && f.destination == destination )
    {
        matchingFlights.push_back(f);
    }
}
std::cout<<"Available Flights:"<<std::endl;
if (matchingFlights.empty())
{
}
else
{
    for (const auto &f : matchingFlights)
    {
        f.print();
    }
}

return matchingFlights;

}