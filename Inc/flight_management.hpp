// this class will include flight,Flight managemnt class
// searching and scheduling of flights
// seat map
// Boarding??

#ifndef FLIGHT_MANAGEMENT_HPP
#define FLIGHT_MANAGEMENT_HPP

#include "../Inc/system.hpp"
#include "../Inc/users.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include<unordered_set>

class flightManagement;
class flight; 
class Database;

class aircraft
{
private:
    static std::vector<aircraft> aircrafts;

public:
    std::string type;
    int seatsNo;//Should be divisble by 4
    maintenance aircraftMaintenance;
    bool availability;
    aircraft(std::string type, int no, maintenance m) : type(type), seatsNo(no), aircraftMaintenance(m), availability(true) {}
        // Constructor
    aircraft(const std::string& type, int seatsNo, const maintenance& m, bool availability)
        : type(type), seatsNo(seatsNo), aircraftMaintenance(m), availability(availability) {}

    friend flightManagement;
    friend Database;
};

class flight
{ // stuff here should be private
private:
void initSeats();
public:
    std::string flightNo;
    std::string origin;
    std::string destination;
    time_t departure;
    time_t arrival;
    std::string status; // 0:Scheduled  1:Delayed 2:cancelled
    std::shared_ptr<aircraft> craft;
    std::map<std::string, int> seatmap; //12A available or not (0 available 1 not available)
    int availableSeatsNo;
    int seatPrice;
    flight(int seatprice=150):seatPrice(seatprice) {}
    flight(std::string number, std::string org, std::string dst, time_t x, time_t y, std::string status, std::shared_ptr<aircraft> craft, int seatPrice = 150) : flightNo(number), origin(org), destination(dst), departure(x), arrival(y), status(status), craft(craft) ,seatPrice(seatPrice) {initSeats();}
    void print() const;
};

class flightManagement
{
private:
    static std::vector<flight> flights; // hass all flights that is there
    static void addFlight();
    static void removeFlight();
    static void updateFlight();
    static void updateFlightDetails(flight &flight_ref);
    static void changeStatus(flight& flight_ref);


public:
    static std::vector<flight> searchFlights();
    static flight& getFlight(const std::string& flightNo);
    static std::unordered_set<std::string> getAvailableSeats(const std::string &flightNo);
    static void displayAdministratorMenu();
    static void ManageAircraft();

    friend Database;
};


#endif // FLIGHT_MANAGEMENT_HPP
