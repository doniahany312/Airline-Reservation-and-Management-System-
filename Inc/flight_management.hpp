// this class will include flight,Flight managemnt class
// searching and scheduling of flights
// seat map
// Boarding??

#ifndef FLIGHT_MANAGEMENT_HPP
#define FLIGHT_MANAGEMENT_HPP

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>

class flight
{//stuff here should be private
public:
    // std::tm tmstrct;
    std::string flightNo;
    std::string origin;
    std::string destination;
    time_t departure;
    time_t arrival;
    std::string status; // 0:Scheduled  1:Delayed 2:cancelled
    std::string aircraft;
    std::map<int, int> seatmap;
    flight() {}
    void print() const;
};

class flightManagement
{
private:
    static std::vector<flight> flights; // hass all flights that is there
    static void addFlight();
    static void removeFlight();
    static void updateFlight();

public:
    static std::vector<flight> searchFlights();
    // void addFlight(const flight& added)
    // {flights.push_back(added);}//will be in cpp file
    static void getAvailableSeats(int flightNo);
    static void displayAdministratorMenu();
};

class aircraft
{
public:
    std::string type;
    int seatsNo;
    // aircraft management
};
#endif // FLIGHT_MANAGEMENT_HPP
