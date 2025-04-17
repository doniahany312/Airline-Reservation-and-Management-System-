#include "../Inc/flight_management.hpp"
#include <algorithm> // For std::find_if
#include <limits>    // For std::numeric_limits
// std::vector<flight> flightManagement::flights;
std::vector<aircraft> aircraft::aircrafts = {};
std::vector<std::pair<std::shared_ptr<flight>, std::shared_ptr<crewMember>>> AssignmentManager::assignments = {};
std::vector<flight> flightManagement::flights = {};

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
                    std::cout<<std::endl;
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
        std::string aircraftType,input;
        flight newFlight;
        std::cin.ignore(); // Clear input buffer
        std::cout << "Enter Flight Number: ";
        std::getline(std::cin, input);
        // checks for flight numebr
        auto it = std::find_if(flights.begin(), flights.end(), [input](const flight &f)
                               { return f.flightNo == input; });
        if (it != flights.end())
        {
            std::cout << "Error:Flight number already exists!!" << std::endl;
            return;
        }
        // possible point for memory leak??!!
        newFlight.flightNo=input;

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
        std::getline(std::cin, aircraftType);
    
        auto it2 = std::find_if(aircraft::aircrafts.begin(), aircraft::aircrafts.end(), [aircraftType](const aircraft &a)
                                { return a.type == aircraftType; });
        if (it2 == aircraft::aircrafts.end())
        {
            std::cout << "Failed to find an aircraft with this type" << std::endl;
            return;
        }
        newFlight.craft = std::make_shared<aircraft>(*it2); // Using shared_ptr to manage aircraft
    
        std::cout << "Enter Status (Scheduled/Delayed/Canceled): ";
        std::getline(std::cin, newFlight.status);
    
        flightManagement::flights.emplace_back(newFlight.flightNo,newFlight.origin,newFlight.destination,newFlight.departure,newFlight.arrival,newFlight.status,newFlight.craft);
        std::cout << "Flight added successfully.\n";
    }
void flightManagement::updateFlightDetails(flight &flight_ref)
{
    std::string aircraftType;
    int choice;
    std::cout << "--- Update Menu ---" << std::endl
              << "1. Update Origin" << std::endl
              << "2. Update Destination" << std::endl
              << "3. Update Departure" << std::endl
              << "4. Update Arrival" << std::endl
              << "5. Update Aircraft" << std::endl;
    // << "6. Back to Main Menu" << std::endl;
    std::cin >> choice;
    
    std::string departureStr, arrivalStr;
    std::istringstream departureStream, arrivalStream;
    std::tm departureTm = {}, arrivalTm = {};
    std::cin.ignore();

    switch (choice)
    {
    case 1:
        /* code */
        std::cout << "Enter Origin: ";
        std::getline(std::cin, flight_ref.origin);
        std::cout << "Origin updated! " << std::endl;
        Reporting::report("Updated the origin of flight number: "+flight_ref.flightNo);
        break;

    case 2:

        std::cout << "Enter Destination: ";
        std::getline(std::cin, flight_ref.destination);
        std::cout << "Destination updated! " << std::endl;
        Reporting::report("Updated the destination of flight number: "+flight_ref.flightNo);

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
        Reporting::report("Updated the Departure date and time of flight number: "+flight_ref.flightNo);

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
        Reporting::report("Updated the Arrival date and time of flight number: "+flight_ref.flightNo);

        break;

    case 5:

        std::cout << "Enter Aircraft Type: ";
        std::getline(std::cin, aircraftType);

        auto it2 = std::find_if(aircraft::aircrafts.begin(), aircraft::aircrafts.end(), [aircraftType](const aircraft &a)
                                { return a.type == aircraftType; });
        if (it2 == aircraft::aircrafts.end())
        {
            std::cout << "Failed to find an aircraft with this type" << std::endl;
            return;
        }
        flight_ref.craft = std::make_shared<aircraft>(*it2); // can be optimized?

        std::cout << "Aircraft updated! " << std::endl;
        Reporting::report("Updated the Aircraft of flight number: "+flight_ref.flightNo);

        break;

    // default:
    // std::cout << "Invalid choice! " << std::endl;
    // return;
    }
}


void flightManagement::updateFlight()
{
    std::string flightNo, aircraftType;
    std::cin.ignore();
    std::cout << "Enter Flight Number: ";
    std::getline(std::cin, flightNo);

    auto it = std::find_if(flights.begin(), flights.end(), [flightNo](const flight &f)
                           { return f.flightNo == flightNo; });
    if (it != flights.end())
    {
        flight &flight_ref = *it;
        int choice;
        std::cout << "Select information to update:" << std::endl
                  << " 1. Flight Details" << std::endl
                  << " 2. Crew Assignments" << std::endl
                  << " 3. Status" << std::endl
                  << " 4. Back to Manage Flights" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            updateFlightDetails(*it);
            /* code */
            break;
        case 2:
            AssignmentManager::crewAssignment(*it);
            break;
        case 3:
            changeStatus(*it);
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice! " << std::endl;
            break;
        }

        // flight found
        //  what to update
    }
    else
    {
        std::cout << "Flight with Flight No " << flightNo << " not found." << std::endl;
    }
}
void flightManagement::changeStatus(flight& flight_ref)
{
   
        std::string status;
        std::cout<<"Enter new status (Confirmed-Scheduled-Canceled):";
        std::getline(std::cin,status);
        if(status=="Confirmed"||status=="Scheduled"||status=="Canceled")
        {
            flight_ref.status = status;
            Reporting::report("Updated the status of flight number: "+flight_ref.flightNo + " to "+status);
        }else{std::cout<<"Status entered is invalid"<<std::endl;return;}
    
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
        Reporting::report("Flight of number: "+ flightNo +" removed ");
    }
    else
    {
        std::cerr << "Flight not found!" << std::endl;
        return;
    }
}

flight& flightManagement::getFlight(const std::string& flightNo)
{
    auto it = std::find_if(flights.begin(), flights.end(), [&flightNo](const flight& f)
    {
        return f.flightNo == flightNo;
    });

    if (it != flights.end())
    {
        return *it;
    }
    else
    {
        throw std::runtime_error("Flight with Flight Number " + flightNo + " not found.");
    }
}
std::unordered_set<std::string> flightManagement::getAvailableSeats(const std::string &flightNo)
{
    for (const auto &fl : flights)
    {
        if (fl.flightNo == flightNo)
        {
            std::unordered_set<std::string> availableSeats;
            for (const auto &seat : fl.seatmap)
            {
                if (seat.second == 0) // Assuming 0 means the seat is available
                {
                    availableSeats.insert(seat.first);
                }
            }
            return availableSeats;
        }
    }
    return {}; // Return an empty set if the flight is not found
}

void flightManagement::ManageAircraft()
{
    int serviceChoice, size;
    std::string name;
    std::cout << "--- Aircraft Management ---" << std::endl
              << "1. Create " << std::endl
              << "2. Update " << std::endl
              << "3. Delete " << std::endl
              << "4. Back to Main Menu" << std::endl;
    std::cin >> serviceChoice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input

    std::cout << "Enter Type of aircraft: ";
    std::getline(std::cin, name);

    auto it = std::find_if(aircraft::aircrafts.begin(), aircraft::aircrafts.end(), [name](const aircraft &air)
                           { return air.type == name; });

    switch (serviceChoice)
    {
    case 1:
        if (aircraft::aircrafts.end() != it)
        {
            std::cout << "Error: Type already exists" << std::endl;
            return;
        }
        std::cout << "Enter Size of aircraft (prefered multiple of 4) :";
        std::cin >> size;

        aircraft::aircrafts.emplace_back(name, size, maintenance());
        Reporting::report("Aircraft Added with type: "+aircraft::aircrafts.back().type);

        std::cout << "Aircraft Created Succesfully!!" << std::endl;
        break;
    case 2:

        if (aircraft::aircrafts.end() == it)
        {
            std::cout << "Error: Type doesn't exist" << std::endl;
            return;
        }
        std::cout << "Enter Updated Size:";
        std::cin >> size;
        it->seatsNo = size;
        Reporting::report("Aircraft of type: "+(*it).type + " Updated with new size "+std::to_string((*it).seatsNo));
        std::cout << "Aircraft Updated Succesfully!!" << std::endl;
        break;
    case 3:
        aircraft::aircrafts.erase(it);
        Reporting::report("Aircraft of type: "+(*it).type + " got deleted");
        std::cout << "Aircraft Deleted Sucessfully!!" << std::endl;
        break;

    case 4:
        return;

    default:
        std::cout << "Invalid Choice!!" << std::endl;
        return;

        break;
    }
}

std::vector<flight> flightManagement::searchFlights()
{
    std::string origin, destination, departureDateStr;
    std::tm departureDateTm = {};
    std::vector<flight> matchingFlights;
    // std::string origin, std::string destination, std::string departure
    std::cin.ignore();
    std::cout << "--- Search Flights ---" << std::endl
              << "Enter Origin:";
    std::getline(std::cin, origin);
    std::cout << "Enter Destination:";
    std::getline(std::cin, destination);
    std::cout << "Enter Departure Date (YYYY-MM-DD):";
    // search by date
    std::getline(std::cin, departureDateStr);
    std::istringstream departureDateStream(departureDateStr);
    departureDateStream >> std::get_time(&departureDateTm, "%Y-%m-%d");
    if (departureDateStream.fail())
    {
        std::cerr << "Failed to parse departure date.\n";
        return {};
    }
    time_t departureDate = std::mktime(&departureDateTm);

    for (const auto &f : flightManagement::flights)
    {
        std::tm flightDepartureTm = *std::localtime(&f.departure);

        if (flightDepartureTm.tm_year == departureDateTm.tm_year &&
            flightDepartureTm.tm_mon == departureDateTm.tm_mon &&
            flightDepartureTm.tm_mday == departureDateTm.tm_mday &&
            f.origin == origin && f.destination == destination)
        {
            matchingFlights.push_back(f);
        }
    }
    std::cout <<std::endl<< "Available Flights:" <<std::endl << std::endl;
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
    auto timeToString = [](time_t time) -> std::string
    {
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&time));
        return std::string(buffer);
    };
    std::cout << "Flight Number: " << flightNo << std::endl
              << "Origin: " << origin << std::endl
              << "Destination: " << destination << std::endl;
    std::cout << "Departure Time: " << timeToString(departure) << std::endl
              << "Arrival Time: " << timeToString(arrival) << std::endl
              << "Aircraft: " << craft.get()->type << std::endl;
    std::cout <<"Available Seats: "<<availableSeatsNo<<std::endl
              <<"Price: $"<<seatPrice<<std::endl;
}

void flight::initSeats()
{
    this->availableSeatsNo=craft.get()->seatsNo;
    this->seatmap.clear(); // Clear the seatmap before initializing
    for(int i=0;i<this->craft.get()->seatsNo;i=i+4)
    {
        this->seatmap.emplace(std::to_string(i/4) + "A", 0);
        this->seatmap.emplace(std::to_string(i/4) + "B", 0);
        this->seatmap.emplace(std::to_string(i/4) + "C", 0);
        this->seatmap.emplace(std::to_string(i/4) + "D", 0);      
    }
}
