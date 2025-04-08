#include <iostream>
#include "../Inc/flight_management.hpp"
#include "../Inc/system.hpp"
#include "../Inc/users.hpp"

int main()
{
    user *user_ptr;
    int x, id;
	while (true)
	{

		std::cout << "Welcome to Airline Reservation and Management System\n"
				  << "Please select your role:\n"
				  << "1. Administrator\n"
				  << "2. Booking Agent\n"
				  << "3. Passenger\n";

		std::cin >> x;
		switch (x)
		{
		case 1:
			id = administrator::login();
			if (id >= 0)
			{
				user_ptr = &administrator::admins.at(id); // is the at function returns an object or reference to object??
			}
			break;
		case 2:
			id = bookingAgent::login();
			if (id >= 0)
			{
				user_ptr = &bookingAgent::bookingAgents.at(id);
			}
			break;
		case 3:
			id = passenger::login();
			if (id >= 0)
			{
				user_ptr = &passenger::passengers.at(id);
			}
			break;
		}
		if (id >= 0)
		{
			user_ptr->displayMenu();
		}
		else
		{
			std::cout << "Logging in failed" << std::endl;
		}
	}
}


