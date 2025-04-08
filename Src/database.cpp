#include "../Inc/database.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

std::string PasswordHasher::hash(const std::string &password)
{
    unsigned int hash1 = 2166136261u; // FNV offset basis
    unsigned int hash2 = 0x811C9DC5;  // Another magic number

    for (size_t i = 0; i < password.length(); ++i)
    {
        char c = password[i];
        hash1 = (hash1 ^ (c + i)) * 16777619;
        hash2 = ((hash2 << 5) | (hash2 >> 27)) ^ (c * 31 + i);
        hash2 += hash1 ^ (c << 3);
    }

    // Combine both hashes into one 64-bit value
    unsigned long long finalHash = ((unsigned long long)hash1 << 32) | hash2;

    // Convert to hex string
    std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(16) << finalHash;

    return oss.str();
}
