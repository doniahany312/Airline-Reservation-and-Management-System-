#include<iostream>
#include"../Inc/flight_management.hpp"
#include"../Inc/system.hpp"
#include"../Inc/users.hpp"

int main()
{
while(true)
{
user* user_ptr;
int x,id;

std::cout << "Welcome to Airline Reservation and Management System\n"
		  << "Please select your role:\n"
		  << "1. Administrator\n"
		  << "2. Booking Agent\n"
		  << "3. Passenger\n";

std::cin>>x;
switch (x) {
case 1:
	id = administrator::login();
	if (id > 0) {
		administrator current = administrator::admins.at(id);
        current.displayMenu()
	}
	break;
case 2:
	// Add logic for case 2 here
	break;
case 3:
    break;
}




}

}