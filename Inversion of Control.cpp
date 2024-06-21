#include <iostream>
#include <string>
#include <memory>


class ITicketBooking {
public:
    virtual void bookTicket(const std::string& ticketType) = 0;
    virtual ~ITicketBooking() = default;
};


class IPaymentProcessor {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~IPaymentProcessor() = default;
};


class TicketBookingSystem : public ITicketBooking {
public:
    void bookTicket(const std::string& ticketType) override {
        std::cout << "Booking " << ticketType << " ticket." << std::endl;
    }
};


class PaymentProcessor : public IPaymentProcessor {
public:
    void processPayment(double amount) override {
        std::cout << "Processing payment of $" << amount << "." << std::endl;
    }
};


class TicketSales {
public:
    TicketSales(std::shared_ptr<ITicketBooking> bookingSystem, std::shared_ptr<IPaymentProcessor> paymentProcessor)
        : bookingSystem(bookingSystem), paymentProcessor(paymentProcessor) {}

    void sellTicket(const std::string& ticketType, double price) {
        bookingSystem->bookTicket(ticketType);
        paymentProcessor->processPayment(price);
    }

private:
    std::shared_ptr<ITicketBooking> bookingSystem;
    std::shared_ptr<IPaymentProcessor> paymentProcessor;
};


int main() {
    auto bookingSystem = std::make_shared<TicketBookingSystem>();
    auto paymentProcessor = std::make_shared<PaymentProcessor>();

    TicketSales ticketSales(bookingSystem, paymentProcessor);

    ticketSales.sellTicket("Regular", 50.0);
    ticketSales.sellTicket("VIP", 150.0);

    return 0;
}