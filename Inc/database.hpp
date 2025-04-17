#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include"../Inc/users.hpp"
#include"../Inc/flight_management.hpp"


class PasswordHasher {
public:
    static std::string hash(const std::string& password);
};

class Database {
public:

    static void fetchData(); // Fetch data from JSON files
    static void saveData();  // Save data back to JSON files
};

#endif
