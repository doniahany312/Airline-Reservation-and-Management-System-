#include <iostream>
#include "../Inc/flight_management.hpp"
#include "../Inc/system.hpp"
#include "../Inc/users.hpp"
#include <limits>
#include <algorithm>

int main()
{
	user *user_ptr;
	std::string id="initialized";
	int x;
	bool wrongChoice = true;
    while (wrongChoice)
    {
	
		std::cout << "Welcome to Airline Reservation and Management System\n"
				  << "Please select your role:\n"
				  << "1. Administrator\n"
				  << "2. Booking Agent\n"
				  << "3. Passenger\n";

		std::cin >> x;
		// Check if the input is valid
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
			id = administrator::login();
			if (!id.empty() && id!="initialized")
			{
				auto it =std::find_if(administrator::admins.begin(),administrator::admins.end(),
				[id](const administrator& adm){return adm.userId==id;});
				user_ptr = &(*it);
			}
			break;
		case 2:
			id = bookingAgent::login();
			if (!id.empty() && id!="initialized")
			{
				auto it =std::find_if(bookingAgent::bookingAgents.begin(),bookingAgent::bookingAgents.end(),
				[id](const bookingAgent& bk){return bk.userId==id;});
				user_ptr = &(*it);
			}
			break;
		case 3:
			id = passenger::login();
			if (!id.empty() && id!="initialized")
			{
				auto it =std::find_if(passenger::passengers.begin(),passenger::passengers.end(),
				[id](const passenger& bk){return bk.userId==id;});
				user_ptr = &(*it);
			}
			break;
		default:
		std::cin.ignore();
			
			std::cout << "Invalid choice! Please try again." << std::endl;
			break;
		}
		if (!id.empty() && id!="initialized")
		{
			Reporting::report(user_ptr->userType+" with ID: "+user_ptr->userId+" Logged in succesfully");
			user_ptr->displayMenu();
			Reporting::report(user_ptr->userType+" with ID: "+user_ptr->userId+" Logged out succesfully");

		}
		else if (id.empty())
		{
			std::cout << "Logging in failed" << std::endl;
		}
	}
}
