#include "../Inc/users.hpp"
#include "../Inc/flight_management.hpp"
#include "../Inc/database.hpp"

// Include <algorithm> for std::find_if
#include <algorithm>

// Define static member variables
int passenger::passengerId = 0;
int bookingAgent::bookingAgentId = 0;
int administrator::adminId = 0;

// Define static vectors
// admin0 - 0000
std::vector<administrator> administrator::admins = {administrator(std::string("admin0"), std::string("cd1415b16f2e6c7d"), std::string("Admin Name"))};
std::vector<bookingAgent> bookingAgent::bookingAgents = {};
std::vector<passenger> passenger::passengers = {passenger("passenger0","cd1415b16f2e6c7d","PassengerNo0")};

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
        switch (x)
        {
        case 1: // manage flights
            flightManagement::displayAdministratorMenu();
            break;
        case 2: // manage aircrafts

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
        wrongChoice = false;
        std::cout << "--- Booking Agent Menu ---" << std::endl
                  << "1. Search Flights" << std::endl
                  << "2. Book a Flight" << std::endl
                  << "3. Modify Reservation" << std::endl
                  << "4. Cancel Reservation" << std::endl
                  << "5. Logout" << std::endl;
        std::cin >> x;
        switch (x)
        {
        case 1:
            /* code */
            flightManagement::searchFlights();
            // enter no of flights & reserve for this object of a booking agent
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5: // logout
            std::cout << "Logged out successfully!" << std::endl;
            return;
        default:
            wrongChoice = true;
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
        }
    }
}

int administrator::login()
{
    std::string username, pass;
    int id = -1;
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
            id = admin.userId;
            break;
        }
    }
    return id;
}

int bookingAgent::login()
{

    std::string username, pass;
    int id = -1;
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
            id = bookingAgent.userId;
            break;
        }
    }
    return id;
}

int passenger::login()
{

    std::string username, pass;
    int id = -1;
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
        break;
    case 1: // booking agent
        /* code */
        std::cout << "--- Creating Booking Agent ---" << std::endl;
        bookingAgent::bookingAgents.emplace_back(username, PasswordHasher::hash(password), name);
        std::cout << "--- Booking Agent Created ---" << std::endl;
        break;
    case 2: // passenger
        /* code */
        std::cout << "--- Creating Passenger ---" << std::endl;
        passenger::passengers.emplace_back(username, PasswordHasher::hash(password), name);
        std::cout << "--- Passenger Created ---" << std::endl;
        break;
    default:
        break;
    }
}

void administrator::updateUser(char type)
{

    int id;
    std::string input;
    user *user_ptr;
    std::cout << "Enter user's ID";
    std::cin >> id;

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
    int id;
    std::cout << "Enter user's ID";
    std::cin >> id;
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

    for (int i = id; i < admins.size(); i++)
    {
        admins[i].userId = admins[i].userId - 1;
    }
    adminId--;
}