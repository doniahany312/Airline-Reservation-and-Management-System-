//this file will include
// reservation ,Mainetnance ,payment,Reporting classes
#include"../Inc/users.hpp"
#include"../Inc/flight_management.hpp"
class reservation
{
    public:
    int resvId;
    passenger owner;
    flight reservedFlight;
    int seat;
    int totalCost;

    static void Modify();

};