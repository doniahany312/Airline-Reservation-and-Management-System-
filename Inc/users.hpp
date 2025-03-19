//this file will include the
//User, Admin , Passenger, Booking agent, Crew Classes
#include<iostream>
#include<vector>


class user
{
    
    
    public:
    int userId;
    std::string name;
    int phoneNumber;
    std::string email;
    std::string username;
    std::string password;
    std::string userType;//bookingAgent-Passenger-Administrator
    int getId(){return this->userId;}
    int getPhoneNumber(){return this->phoneNumber;}
    // virtual static int login()=0;//if -1 then failed auth
    virtual void displayMenu()=0;

};

class administrator:public user
{
    private:
    void createUser();
    void updateUser();
    void deleteUser();

    public:
    static int adminId;
    static std::vector<administrator> admins;
    administrator(const std::string& username,const std::string& password, std::string name =""){
        this->username = username;
        this->password = password;
        this->userType="admin";
        this->name=name;
        this->userId=adminId++;
    }
    //FLIGHT OPS*  make the crew assigment in the flight ops
    // void crewAssigment();//arguments are todo (flightid,crewid)
    void manageUsers();
    void aircraftManage();
    void generateReports();
    static int login();
    void displayMenu() override;

};


class bookingAgent:public user
{
private:
bool processPayment(std::string accType,std::string acc,int amount);//needs a payment class

 public:
 static std::vector<bookingAgent> bookingAgents;
 bookingAgent(int id,const std::string& username,const std::string& password ,const std::string& name){
    this->username = username;
    this->password = password;
    this->userType="booking agent";
    this->name=name;
    this->userId=id;
}
 void searchFlights();// couts all available flights
 void bookFlight();
 void modifyReservation();
 void cancelReservation();
 void airportCheckin();
 static int login();
 void displayMenu() override;
};

class passenger:public user
{
public:
std::vector<std::string> history;
std::string preferences;
void onlineCheckin();
void searchFlight();
void viewHistory();
int login();
void displayMenu() override;

};
// class crew:public user
// {
//     public:
//     int crewID;
//     //
// }