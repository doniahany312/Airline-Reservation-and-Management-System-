#ifndef SYSTEM_HPP
#define SYSTEM_HPP

//this file will include
// reservation ,Mainetnance ,payment,Reporting classes

// #include"../Inc/users.hpp"
// #include"../Inc/flight_management.hpp"
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <memory>
class flight;

class passenger;

class payment
{
    public:
    std::string from;
    int amount;
    std::string type;
    payment();
    payment(std::string from,int amount,std::string type):from(from),amount(amount),type(type){}
    
};
class reservation
{
    private:
    static  std::unordered_map<int, std::shared_ptr<reservation>> reservations;
    static int resvId;
    static std::unordered_map<std::string, std::string> flightToGateMap; // Map flightNo to gate
    static std::vector<std::string> gates;                              // List of main gates
    static int gateIndex;                                               // Index to assign gates sequentially

    public:

    int id;
    std::shared_ptr<passenger> owner;
    std::shared_ptr<flight> reservedFlight;
    std::string seat;
    int totalCost;
    std::string gate;
    time_t BoradingTime;
    payment paymentMethod;
    std::string status;//Confirmed Canceled 
  
    // Declare constructors
    reservation(std::shared_ptr<passenger> own, std::shared_ptr<flight> flight, payment x, std::string seat);
    reservation(std::shared_ptr<passenger> own, std::shared_ptr<flight> flight, int id, payment x, std::string seat);



    static std::string add(std::string passengerId);
    static void cancel(int reservationId);
    static reservation& getReservation(int reservationId);
    static std::vector<reservation> getHistory(std::vector<int> ids);
    static void Modify();

    //cancel 
};



class maintenance
{
public:
std::vector<std::pair<std::string,tm*>> schedules;
std::vector<std::pair<std::string,tm*>> logs;

maintenance()
{    
    auto getCurrentTimeString = []() -> std::tm* {
        std::time_t now = std::time(nullptr);
        now += 30 * 24 * 60 * 60; // Adding 30 days to the current time
        std::tm* localTime = std::localtime(&now);
        // std::ostringstream oss;
        // oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
        // return oss.str();
        return localTime;
    };

    std::tm* currentTime = getCurrentTimeString();
    schedules.push_back(std::make_pair("first maintenance", currentTime));
}

void addLog(const std::string& description);
};

class Reporting
{
 static  std::vector<std::string> reports;
public:

static void report(std::string entry);
static void generateReport();
};
#endif