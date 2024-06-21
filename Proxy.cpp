#include <iostream>
#include <string>
#include <memory>


class TicketBooking {
public:
    virtual void bookTicket(const std::string& ticketType) = 0;
};


class RealTicketBooking : public TicketBooking {
public:
    void bookTicket(const std::string& ticketType) override {
        std::cout << "Booking " << ticketType << " through RealTicketBooking system." << std::endl;
    }
};


class TicketBookingProxy : public TicketBooking {
public:
    TicketBookingProxy() : realBooking(std::make_unique<RealTicketBooking>()) {}

    void bookTicket(const std::string& ticketType) override {
        if (isBookingAllowed(ticketType)) {
            realBooking->bookTicket(ticketType);
        }
        else {
            std::cout << "Booking " << ticketType << " is not allowed." << std::endl;
        }
    }

private:
    bool isBookingAllowed(const std::string& ticketType) {
        
        if (ticketType == "Regular Ticket" || ticketType == "VIP Ticket") {
            return true;
        }
        return false;
    }

    std::unique_ptr<RealTicketBooking> realBooking;
};


int main() {
    TicketBookingProxy proxy;

    std::cout << "Trying to book Regular Ticket:" << std::endl;
    proxy.bookTicket("Regular Ticket");

    std::cout << "\nTrying to book VIP Ticket:" << std::endl;
    proxy.bookTicket("VIP Ticket");

    std::cout << "\nTrying to book Invalid Ticket:" << std::endl;
    proxy.bookTicket("Invalid Ticket");

    return 0;
}