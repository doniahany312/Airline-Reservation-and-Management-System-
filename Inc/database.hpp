#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>

class PasswordHasher {
public:
    static std::string hash(const std::string& password);
};

#endif
