// #include "../Inc/system.hpp"

#include "../Inc/flight_management.hpp"

int reservation::resvId = 0;
std::unordered_map<int, std::shared_ptr<reservation>> reservation::reservations = {};
void reservation::add(std::shared_ptr<reservation> sptr)
{
    reservations.emplace(sptr.get()->id,sptr);

}

void reservation::cancel(int reservationId)
{
    auto& originalFlight = flightManagement::getFlight(reservations[reservationId].get()->reservedFlight.get()->flightNo);
    originalFlight.seatmap[reservations[reservationId].get()->seat] = 0; // Make the seat available again
    reservations[reservationId].get()->status="Canceled";
    std::cout<<"Reservation R"<<reservationId<<" has been sucessfully canceled."<<std::endl;
    std::cout<<"Refund Amount: "<<reservations[reservationId].get()->paymentMethod.amount<<" has been credited to your "<<reservations[reservationId].get()->paymentMethod.type<<" account."<<std::endl;
}

reservation& reservation::getReservation(int reservationId)
{
    auto it = reservations.find(reservationId);
    if (it == reservations.end()) {
        throw std::out_of_range("Reservation ID not found.");
    }
    return *(it->second);
}

void maintenance::addLog(const std::string& description){
    auto getCurrentTimeString = []() -> std::tm* {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        return localTime;
    };

    std::tm* currentTime = getCurrentTimeString();
    logs.push_back(std::make_pair(description, currentTime));
}