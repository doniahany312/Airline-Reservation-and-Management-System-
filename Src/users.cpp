#include "../Inc/users.hpp"
#include "../Inc/flight_management.hpp"
#include "../Inc/database.hpp"
#include"../Inc/system.hpp"

// Include <algorithm> for std::find_if
#include <algorithm>
#include <limits> // Required for std::numeric_limits

// Define static member variables
int passenger::passengerId = 0;
int bookingAgent::bookingAgentId = 0;
int administrator::adminId = 0;

// Define static vectors
// admin0 - 0000
std::vector<administrator> administrator::admins = {administrator(std::string("admin0"), "cd1415b16f2e6c7d", std::string("Admin Name"))};
std::vector<bookingAgent> bookingAgent::bookingAgents = {bookingAgent(std::string("agent0"),"cd1415b16f2e6c7d",std::string("agentNo0"))};
std::vector<passenger> passenger::passengers = {passenger("passenger0","cd1415b16f2e6c7d","PassengerNo0","P456")};
std::vector<pilot> pilot::pilots = {pilot("Sarah Connor", "PL001"), pilot("James Kirk", "PL002")};
std::vector<flightAttendant> flightAttendant::flightAttendants = {flightAttendant("Emma Watson", "FA001"), flightAttendant("John Cena", "FA002")};

void administrator::displayMenu()
{
    int x;
    bool wrongChoice = true;
    while (wrongChoice)
    {
        std::cout << "--- Administrator Menu ---" << std::endl
                  << "1. Manage Flights" << std::endl
                  << "2. Manage Aircraft" << std::endl
                  << "3. Manage Users" << std::endl
                  << "4. Generate Reports" << std::endl
                  << "5. Logout" << std::endl;

        std::cin >> x;
        if (std::cin.fail())
        {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue; // Restart the loop
        }
        switch (x)
        {
        case 1: // manage flights
            flightManagement::displayAdministratorMenu();
            break;
        case 2: // manage aircrafts
            flightManagement::ManageAircraft();
            break;
        case 3: // manage users (create, update, and delete user accounts)
            manageUsers();
            break;
        case 4: // generate reports
            break;
        case 5: // logout
            wrongChoice = false;
            std::cout << "Logged out successfully!" << std::endl;
            return;
        default:
            wrongChoice = true;
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
        }
    }
}

void administrator::manageUsers()
{
    std::cin.ignore(); // Clear any leftover characters in the input buffer
    std::cout << "--- User Management Menu 1 ---" << std::endl
              << "1. Administrator" << std::endl
              << "2. Booking Agent" << std::endl
              << "3. Passenger" << std::endl;
    //   << "4. Back to Main Menu" << std::endl;

    int userTypeChoice, serviceChoice;
    std::cin >> userTypeChoice;
    std::cout << "--- User Management Menu 2 ---" << std::endl
              << "1. Create " << std::endl
              << "2. Update " << std::endl
              << "3. Delete " << std::endl
              << "4. Back to Main Menu" << std::endl;
    std::cin >> serviceChoice;
    switch (serviceChoice)
    {
    case 1:
        /* code */
        createUser(userTypeChoice - 1);
        break;
    case 2:
        updateUser(userTypeChoice - 1);
        break;
    case 3:
        deleteUser(userTypeChoice - 1);
        break;
    case 4:
        return;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }
}

void administrator::createUser(char type)
{
    std::string username, password, name;
    std::cout << "Enter username: " << std::endl;
    std::cin >> username;
    // std::getline(std::cin, username);
    std::cout << "Enter passwrod: " << std::endl;
    std::cin >> password;
    // std::getline(std::cin, password);
    std::cout << "Enter name: " << std::endl;
    // std::getline(std::cin, name);
    std::cin >> name;
    switch (type)
    {
    case 0: // admin
        /* code */
        std::cout << "--- Creating Administrator ---" << std::endl;
        admins.emplace_back(username, PasswordHasher::hash(password), name);
        std::cout << "--- Administrator Created ---" << std::endl;
        std::cout<<"Administrator ID: "<<admins.back().userId<<std::endl;
        break;
    case 1: // booking agent
        /* code */
        std::cout << "--- Creating Booking Agent ---" << std::endl;
        bookingAgent::bookingAgents.emplace_back(username, PasswordHasher::hash(password), name);
        std::cout << "--- Booking Agent Created ---" << std::endl;
        std::cout<<"Booking Agent ID: "<<bookingAgent::bookingAgents.back().userId<<std::endl;

        break;
    case 2: // passenger
        /* code */
        std::cout << "--- Creating Passenger ---" << std::endl;
        passenger::passengers.emplace_back(username, PasswordHasher::hash(password), name);
        std::cout << "--- Passenger Created ---" << std::endl;
        std::cout<<"Passenger ID: "<<passenger::passengers.back().userId<<std::endl;
        break;
    default:
        break;
    }
}

void administrator::updateUser(char type)
{

    std::string id;
    std::string input;
    user *user_ptr;
    std::cout << "Enter user's ID";
std::getline(std::cin,id);
    auto &userList = admins;
    // Use a pointer to handle incompatible types
    if (type == 0)
    {
        auto &userList = admins;
        // Use userList for admins
    }
    else if (type == 1)
    {
        auto &userList = bookingAgent::bookingAgents;
        // Use userList for booking agents
    }
    else if (type == 2)
    {
        auto &userList = passenger::passengers;
        // Use userList for passengers
    }
    else
    {
        std::cerr << "Invalid user type!" << std::endl;
        return;
    }

    // Use std::find_if to locate the user by userId
    auto it = std::find_if(userList.begin(), userList.end(), [id](const user &u)
                           {
                               return u.userId == id; // Match userId
                           });

    if (it != userList.end())
    {
        user_ptr = &(*it);
    }
    else
    {
        std::cerr << "User not found!" << std::endl;
        return;
    }

    // what to update
    std::cout << "--- Update Menu ---" << std::endl
              << "1. Update Name" << std::endl
              << "2. Update Phone Number" << std::endl
              << "3. Update Email" << std::endl
              << "4.Update Username" << std::endl
              << "5.Update Password" << std::endl
              << "6. Back to Main Menu" << std::endl;

    int updateChoice;
    std::cin >> updateChoice;

    switch (updateChoice)
    {
    case 1:
        std::cout << "Enter new name: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        // Update logic for name
        user_ptr->name = input;
        break;
    case 2:
        std::cout << "Enter new phone number: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        // Update logic for phone number
        user_ptr->phoneNumber = std::stoi(input);
        break;
    case 3:
        std::cout << "Enter new email: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        // Update logic for email
        user_ptr->email = input;
        break;
    case 4:
        std::cout << "Enter new username: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        // Update logic for username
        user_ptr->username = input;
        break;
    case 5:
        std::cout << "Enter new password: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        // Update logic for password
        user_ptr->password = PasswordHasher::hash(input);
        break;
    case 6:
        return;
    default:
        std::cout << "Invalid choice!" << std::endl;
    }
}

void administrator::deleteUser(char type) // to be tested
{                                         // problem here is that the ids are incremented by objects and accessed by it
    std::string id;
    std::cout << "Enter user's ID";
    std::getline(std::cin,id);
    auto &userList = admins;
    // Use a pointer to handle incompatible types
    if (type == 0)
    {
        auto &userList = admins;
        // Use userList for admins
    }
    else if (type == 1)
    {
        auto &userList = bookingAgent::bookingAgents;
        // Use userList for booking agents
    }
    else if (type == 2)
    {
        auto &userList = passenger::passengers;
        // Use userList for passengers
    }
    else
    {
        std::cerr << "Invalid user type!" << std::endl;
        return;
    }

    // Use std::find_if to locate the user by userId
    auto it = std::find_if(userList.begin(), userList.end(), [id](const user &u)
                           {
                               return u.userId == id; // Match userId
                           });

    if (it != userList.end())
    {
        admins.erase(it);
        std::cout << "User deleted successfully!" << std::endl;
    }
    else
    {
        std::cerr << "User not found!" << std::endl;
        return;
    }

    // for (int i = id; i < admins.size(); i++)
    // {
    //     admins[i].userId = admins[i].userId - 1;
    // }
    // adminId--;
}



void passenger::displayMenu()
{
    int x;
    bool wrongChoice = true;
    while (wrongChoice)
    {
        std::cout << "--- Passenger Menu ---" << std::endl
                  << "1. Search Flights" << std::endl
                  << "2. View My Reservations" << std::endl
                  << "3. Check-In" << std::endl
                  << "4. Logout" << std::endl;
        std::cin >> x;
        if (std::cin.fail())
        {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue; // Restart the loop
        }
        switch (x)
        {
        case 1:
            /* code */
            std::cout << "REACHED HERE CORRECTLY" << std::endl;
            flightManagement::searchFlights();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4: // logout
            wrongChoice = false;
            std::cout << "Logged out successfully!" << std::endl;
            return;
        default:
            wrongChoice = true;
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
        }
    }
}


void bookingAgent::displayMenu()
{
    int x;
    bool wrongChoice = true;
    while (wrongChoice)
    {
        std::cout << "--- Booking Agent Menu ---" << std::endl
                  << "1. Search Flights" << std::endl
                  << "2. Book a Flight" << std::endl
                  << "3. Modify Reservation" << std::endl
                  << "4. Cancel Reservation" << std::endl
                  << "5. Logout" << std::endl;
        std::cin >> x;
        if (std::cin.fail())
        {
            std::cin.clear(); // Clear the fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue; // Restart the loop
        }
        switch (x)
        {
        case 1:
            /* code */
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            flightManagement::searchFlights();
            // bookFlight();??
            // enter no of flights & reserve for this object of a booking agent
            break;
        case 2:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        bookFlight();
            break;
        case 3:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        modifyReservation();
            break;
        case 4:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        cancelReservation();
            break;
        case 5: // logout
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            wrongChoice = false;
            std::cout << "Logged out successfully!" << std::endl;
            return;
        default:
        std::cin.ignore(); // Discard invalid input
            wrongChoice = true;
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
        }
    }
}

void bookingAgent::bookFlight()
{
    std::string flightNo, seatNo, passengerId;
    std::cout << "--- Book a Flight ---" << std::endl;
    std::cout << "Enter Passenger ID: ";
    std::getline(std::cin, passengerId);
    auto passengerIt = std::find_if(passenger::passengers.begin(), passenger::passengers.end(), [passengerId](const passenger &p)
                                    { return p.userId == passengerId; });
    if (passengerIt == passenger::passengers.end())
    {
        std::cout << "Error: Invalid Passenger ID !!" << std::endl;
        return;
    }

    std::cout << "Enter the Flight Number: ";
    std::getline(std::cin, flightNo);
    auto seats = flightManagement::getAvailableSeats(flightNo);
    if (seats.empty())
    {
        std::cout << "Flight not found or no seats available" << std::endl;
        return;
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
                return;
            }
            std::cout << "Enter Payment Details: ";
            std::getline(std::cin, details); // wrong : no check for details

            ;
            std::shared_ptr<reservation> sptr = std::make_shared<reservation>(reservation(std::make_shared<passenger>(*passengerIt), flightPtr, payment(details, 150, method), seatNo));
            reservation::add(sptr);
            reservedFlight.seatmap[seatNo]=1;//not available
            
            std::cout << "Booking Successful!" << std::endl;
            std::cout << "Reservation ID: " << "R" << sptr.get()->id << std::endl;
            std::cout << "Passenger: " << (*passengerIt).name << std::endl;
            std::cout << "Flight: " << flightNo << " from " << reservedFlight.origin << " to " << reservedFlight.destination << std::endl;
            std::cout << "Seat: " << seatNo << std::endl;
            std::cout << "Total Cost: $" <<reservedFlight.seatPrice<< std::endl; // maybe wrong
            std::cout << "Payment Method: " << method << std::endl;
        }
        else
        {
            std::cout << "Seat " << seatNo << " is not available." << std::endl;
            return;
        }
    }

    else
    {
        std::cout << "Seat number is empty! " << std::endl;
        return;
    }
}

void bookingAgent::cancelReservation()
{
std::string resvId,confirm;
std::cout<< "--- Cancel Reservation ---" << std::endl;
std::cout<<"Enter Reservation ID: ";
std::getline(std::cin,resvId);
std::cout<<" Are you sure you want to cancel Reservation ID "<<resvId<<"?";
std::cout<<"(yes/no): ";
std::cin>>confirm;//yes or no
if(confirm=="yes")
{
    resvId.erase(0, 1); // Remove the first letter from the string
    try {
        int reservationId = std::stoi(resvId); // Convert the remaining string to an integer
        if(reservation::getReservation(reservationId).status!= "Canceled")
        {reservation::cancel(reservationId);}
        else{std::cout<<"Reservation is already canceled!"<<std::endl;}
        
        // Proceed with reservationId
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid reservation ID format!" << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Reservation ID is out of range!" << std::endl;
        return;
    }
}
else 
{
std::cout<<"Canceled the Request!"<<std::endl;
return;
}
}

void bookingAgent::modifyReservation()
{
std::string resvId,seatNumber;
int reservationId;
std::cout<<"--- Modify Reservation ---"<<std::endl;
std::cout<<"Enter Reservation ID: ";
std::getline(std::cin,resvId);
resvId.erase(0, 1); // Remove the first letter from the string
    try {
        reservationId = std::stoi(resvId); // Convert the remaining string to an integer
        // Proceed with reservationId
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid reservation ID format!" << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Reservation ID is out of range!" << std::endl;
        return;
    }


auto& resvv=reservation::getReservation(reservationId);
std::cout<<"resevation returned id:"<<resvv.id<<std::endl;

if(resvv.status=="Canceled")
{
    std::cout<<"Error: This Reservation is Canceled so Can't be Modified !"<<std::endl;
    return;
}
auto seats=flightManagement::getAvailableSeats(resvv.reservedFlight.get()->flightNo);
auto& reservedFlight = flightManagement::getFlight(resvv.reservedFlight.get()->flightNo);

//changing the seat is the only thing you want to modify??
std::cout<<"Modifying the seat number.."<<std::endl;
std::cout<<"Enter the new seat:";
std::getline(std::cin,seatNumber);

if (!seatNumber.empty()) {
  
    if (seats.find(seatNumber) != seats.end()) //then seatNumber is available
    {
        // resvv.reservedFlight.get()->seatmap.at(resvv.seat)=0;//make the already reserved available
        //reserve the new seat
        reservedFlight.seatmap[resvv.seat]=0;// available
        
        reservedFlight.seatmap[seatNumber]=1;//not available
        std::cout<<"New seat is booked"<<std::endl;
        std::cout<<"Reservation is sucessfully modified!! "<<std::endl;

    }
    else
    {
        std::cout<<"The entered seat is not available"<<std::endl;
    }

}
}
std::string administrator::login()
{
    std::string username, pass;
    std::string id;
    std::cin.ignore(); // Clear any leftover characters in the input buffer
    std::cout << "--- Administrator Login ---" << std::endl
              << "Username:";
    std::getline(std::cin, username);
    // std::cin.ignore(); // Clear any leftover characters in the input buffer
    std::cout << "Password:";
    std::getline(std::cin, pass);

    std::cout << "username entered:" << username << "  password entered: " << pass
              << " password hashed: " << PasswordHasher::hash(pass) << std::endl;

    for (auto admin : admins)
    {

        std::cout << " username: " << admin.username << " password: " << admin.password << std::endl;
        if (admin.username == username && admin.password == PasswordHasher::hash(pass))
        {
            std::cout << "match found" << std::endl;
            std::cout << "user's id: " << admin.userId << std::endl;
            id=admin.userId;
            break;
        }
    }
    return id;
}

std::string bookingAgent::login()
{

    std::string username, pass;
    std::string id;
    std::cin.ignore(); // Clear any leftover characters in the input buffer
    std::cout << "--- Booking Agent Login ---" << std::endl
              << "Username:";
    std::getline(std::cin, username);
    std::cout << "Password:";
    std::getline(std::cin, pass);
    std::cout << "username entered:" << username << "  password entered: " << pass
              << "password hashed: " << PasswordHasher::hash(pass) << std::endl;
    for (auto bookingAgent : bookingAgents)
    {
        std::cout << " username: " << bookingAgent.username << " password: " << bookingAgent.password << std::endl;
        if (bookingAgent.username == username && bookingAgent.password == PasswordHasher::hash(pass))
        {
            std::cout << "match found" << std::endl;
            std::cout << "user's id: " << bookingAgent.userId << std::endl;
            id= bookingAgent.userId;
            break;
        }
    }
    return id;
}

std::string passenger::login()
{

    std::string username, pass;
    std::string id;
    std::cin.ignore(); // Clear any leftover characters in the input buffer
    std::cout << "--- Passenger Login ---" << std::endl
              << "Username:";
    std::getline(std::cin, username);
    std::cout << "Password:";
    std::getline(std::cin, pass);
    std::cout << "username entered:" << username << "  password entered: " << pass
              << "password hashed: " << PasswordHasher::hash(pass) << std::endl;
    for (auto passenger : passengers)
    {
        std::cout << " username: " << passenger.username << " password: " << passenger.password << std::endl;
        if (passenger.username == username && passenger.password == PasswordHasher::hash(pass))
        {
            std::cout << "match found" << std::endl;
            std::cout << "user's id: " << passenger.userId << std::endl;
            id = passenger.userId;
            break;
        }
    }
    return id;
}


void AssignmentManager::crewAssignment(flight &flight_ref)
{
    std::string PilotID, FlightAttendantID;
    std::vector<std::string> availablePilots;
    std::vector<std::string> availableAttendants;
    int count = 1;
    std::cout << "--- Crew Assignments ---" << std::endl;
    std::cout << "Available Pilots:" << std::endl;
    for (auto p : pilot::pilots)
    {
        if (p.available)
        {
            std::cout << count++ << ". ";
            std::cout << "Pilot ID: " << p.crewID << " - Captain " << p.name << std::endl;
            availablePilots.push_back(p.crewID);
        }
    }
    std::cin.ignore();
    std::cout << std::endl
              << "Select Pilot by ID:";
    std::getline(std::cin, PilotID);
    count = 1;
    std::cout << "Available Flight Attendats:" << std::endl;
    for (auto FA : flightAttendant::flightAttendants)
    {
        if (FA.available)
        {
            std::cout << count++ << ". ";
            std::cout << "Flight Attendant ID: " << FA.crewID << " - " << FA.name << std::endl;
            availableAttendants.push_back(FA.crewID);
        }
    }
    // std::cin.ignore();
    std::cout << std::endl
              << "Select Flight Attendant by ID:";
    std::getline(std::cin, FlightAttendantID);

    if (availablePilots.end() == std::find_if(availablePilots.begin(), availablePilots.end(), [PilotID](const std::string &p)
                                              { return p == PilotID; }))
    { // if the chosen pilot id is not in the available pilots
        std::cout << "Error: Pilot ID not from the available list" << std::endl;
        return;
    }
    if (availableAttendants.end() == std::find_if(availableAttendants.begin(), availableAttendants.end(), [FlightAttendantID](const std::string &f)
                                                  { return f == FlightAttendantID; }))
    {
        std::cout << "Error: Flight Attendant ID not from the available list" << std::endl;
        return;
    }

    auto pilotIt = std::find_if(pilot::pilots.begin(), pilot::pilots.end(), [PilotID](const pilot &p)
                                { return p.crewID == PilotID; });
    auto attendantIt = std::find_if(flightAttendant::flightAttendants.begin(), flightAttendant::flightAttendants.end(), [FlightAttendantID](const flightAttendant &f)
                                    { return f.crewID == FlightAttendantID; });

    AssignmentManager::assign(*pilotIt, flight_ref);
    AssignmentManager::assign(*attendantIt, flight_ref);

    std::cout << "Crew assigned successfully to Flight AA123." << std::endl;
}

// void  AssignmentManager::assign(std::shared_ptr<crewMember> cm, std::shared_ptr<flight> fl)
void AssignmentManager::assign(crewMember &cm, flight &fl)

{
    cm.available = false;
    for (auto p : pilot::pilots)
    {
        std::cout << "Pilot ID: " << p.crewID << " Av: " << p.available << std::endl;
    }
    for (auto p : flightAttendant::flightAttendants)
    {
        std::cout << "Flight Attendant ID: " << p.crewID << " Av: " << p.available << std::endl;
    }

    assignments.emplace_back(std::make_shared<flight>(fl), std::make_shared<crewMember>(cm));
}

std::vector<std::shared_ptr<crewMember>> AssignmentManager::getCrewForFlight(const std::shared_ptr<flight> fl)
{
    std::vector<std::shared_ptr<crewMember>> crew;
    for (auto &a : assignments)
        if (a.first == fl)
            crew.push_back(a.second); // push the shared_ptr directly
    return crew;
}

std::vector<std::shared_ptr<flight>> AssignmentManager::getFlightsForCrew(const std::shared_ptr<crewMember> cm)

{
    std::vector<std::shared_ptr<flight>> flights;
    for (auto &a : assignments)
        if (a.second == cm)
            flights.push_back(a.first);
    return flights;
}