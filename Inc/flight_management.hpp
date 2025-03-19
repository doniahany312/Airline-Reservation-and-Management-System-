// this class will include flight,Flight managemnt class
// searching and scheduling of flights
// seat map
// Boarding??
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <chrono>
#include <map>

class flight
{
public:
    std::tm tmstrct;
    int flightNo;
    std::string origin;
    std::string destination;
    time_t departure;
    time_t arrival;
    std::string status; // 0:Scheduled  1:Delayed 2:cancelled
    std::string aircraft;
    std::map<int,int> seatmap;
    flight(){}
};

class flightManagement
{
private:
    static std::vector<flight> flights; // hass all flights that is there

public:
    std::vector<flight> searchFlights(std::string origin, std::string destination, std::string departure);
    // void addFlight(const flight& added)
    // {flights.push_back(added);}//will be in cpp file
    void addFlight();
    void removeFlight(int flightNo);
    void updateFlight(int flightNo);
    void getAvailableSeats(int flightNo);
};

class aircraft
{
    public:
    std::string type;
    int seatsNo;
    //availability
};