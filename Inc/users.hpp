#ifndef USERS_HPP
#define USERS_HPP
// this file will include the
// User, Admin , Passenger, Booking agent, Crew Classes
#include <iostream>
#include <vector>
#include <memory>

class AssignmentManager;
class flight;

class user
{

public:
    std::string userId;
    std::string name;
    int phoneNumber;
    std::string email;
    std::string username;
    std::string password;
    std::string userType; // bookingAgent-Passenger-Administrator
    std::string getId() { return this->userId; }
    int getPhoneNumber() { return this->phoneNumber; }
    virtual void displayMenu() = 0;
    
};

class administrator : public user
{
private:
    void createUser(char type);//0 admin //1 booking agent //2 passenger
    void updateUser(char type);//0 admin //1 booking agent //2 passenger
    void deleteUser(char type);//0 admin //1 booking agent //2 passenger
    static int adminId;

public:
    static std::vector<administrator> admins;
    administrator(const std::string &username, const std::string &password, std::string name ,const std::string& id)
    {
        this->username = username;
        this->password = password;
        this->userType = "admin";
        this->name = name;
        this->userId = id;
    }
    administrator(const std::string &username, const std::string &password, std::string name )
    {
        this->username = username;
        this->password = password;
        this->userType = "admin";
        this->name = name;
        this->userId = "AD"+std::to_string(adminId++);
    }

    void manageUsers();
    // void generateReports();
    static std::string login();
    void displayMenu() override;
};

class bookingAgent : public user
{
private:
    bool processPayment(std::string accType, std::string acc, int amount); // needs a payment class
    static int bookingAgentId;
    void bookFlight();
    void modifyReservation();
    void cancelReservation();

public:
    static std::vector<bookingAgent> bookingAgents;
    bookingAgent(const std::string &username, const std::string &password, const std::string &name ,const std::string& id)
    {
        this->username = username;
        this->password = password;
        this->userType = "booking agent";
        this->name = name;
        this->userId = id;
    }
    bookingAgent(const std::string &username, const std::string &password, const std::string &name )
    {
        this->username = username;
        this->password = password;
        this->userType = "booking agent";
        this->name = name;
        this->userId = "BA"+ std::to_string(bookingAgentId++);
    }
    // void searchFlights(); // couts all available flights
    void airportCheckin();
    static std::string login();
    void displayMenu() override;
};

class passenger : public user
{
private:
static int passengerId;
    void bookFlight();
public:
    static std::vector<passenger> passengers;
    std::vector<int> history;//reservations ids
    std::string preferences;
    
    passenger(const std::string &username,const std::string&password,const std::string &name,const std::string& id)
    {
        this->username = username;
        this->password = password;
        this->userType = "passenger";
        this->name = name;
        this->userId = id;
    }
    passenger(const std::string &username,const std::string&password,const std::string &name)
    {
        this->username = username;
        this->password = password;
        this->userType = "passenger";
        this->name = name;
        this->userId = "P" + std::to_string(passengerId++);
    }
    static std::string login();
    void onlineCheckin();
    void viewHistory();
    void displayMenu() override;
};

class crewMember
{
    public:
    std::string name;
    std::string crewID;
    int maxFlightHours;
    int workedHours;
    bool available;
    //availability //vector of flighst assigned dates & times
    crewMember(std::string name,std::string id,int hours)
    {
        this->name=name;
        this->crewID=id;
        this->maxFlightHours=hours;
        this->workedHours=0;
        this->available=true;
    }
};
class pilot : public crewMember
{
private:
public:
static std::vector<pilot> pilots;
    pilot(std::string name, std::string id) : crewMember(name, id, 70)
    {
        // pilots.emplace_back(this);
    }
friend class AssignmentManager;
};
class flightAttendant : public crewMember
{
private:
public:
static std::vector<flightAttendant> flightAttendants;
    flightAttendant(std::string name, std::string id) : crewMember(name, id, 50)
    {
        // flightAttendants.emplace_back(this);
    }
friend class AssignmentManager;
};

class AssignmentManager
{
private:
    static std::vector<std::pair<std::shared_ptr<flight>, std::shared_ptr<crewMember>>> assignments;

public:
static void crewAssignment(flight &flight_ref);
    static void assign(crewMember &cm, flight &fl);

    static std::vector<std::shared_ptr<crewMember>> getCrewForFlight(const std::shared_ptr<flight> fl);

    static std::vector<std::shared_ptr<flight>> getFlightsForCrew(const std::shared_ptr<crewMember> cm);

    // friend flightManagement;
};
#endif