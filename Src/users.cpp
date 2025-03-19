#include "../Inc/users.hpp"
std::vector<administrator> administrator::admins = {administrator(std::string("admin0"), std::string("0000"), std::string("Admin Name"))};

void administrator::displayMenu()
{
    std::cout << "--- Administrator Menu ---" << std::endl
              << "1. Manage Flights" << std::endl
              << "2. Manage Aircraft" << std::endl
              << "3. Manage Users" << std::endl
              << "4. Generate Reports" << std::endl
              << "5. Logout" << std::endl;
}

void passenger::displayMenu()
{
    std::cout << "--- Passenger Menu ---" << std::endl
              << "1. Search Flights" << std::endl
              << "2. View My Reservations" << std::endl
              << "3. Check-In" << std::endl
              << "4. Logout" << std::endl;
}

void bookingAgent::displayMenu()
{
    std::cout << "--- Booking Agent Menu ---" << std::endl
              << "1. Search Flights" << std::endl
              << "2. Book a Flight" << std::endl
              << "3. Modify Reservation" << std::endl
              << "4. Cancel Reservation" << std::endl
              << "5. Logout" << std::endl;
}

int administrator::login()
{
    std::string username, pass;
    int id=-1;
    std::cout << "--- Administrator Login ---" << std::endl
              << "Username:";
    std::cin >> username;
    std::cout << "Password:";
    std::cin >> pass;
    for(auto admin:admins)
    {
        if(admin.username==username&&admin.password==pass)
        {
            id=admin.adminId;
            break;
        }
    }
return id;
}
void administrator::manageUsers()
{
}