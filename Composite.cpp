#include <iostream>
#include <string>
#include <vector>
#include <memory>


class TicketComponent {
public:
    virtual ~TicketComponent() = default;
    virtual void display() const = 0;
    virtual double getPrice() const = 0;
};


class StandardTicket : public TicketComponent {
public:
    StandardTicket(const std::string& name, double price) : name(name), price(price) {}

    void display() const override {
        std::cout << "Standard Ticket: " << name << " - $" << price << std::endl;
    }

    double getPrice() const override {
        return price;
    }

private:
    std::string name;
    double price;
};


class TicketPackage : public TicketComponent {
public:
    void add(std::shared_ptr<TicketComponent> component) {
        components.push_back(component);
    }

    void remove(std::shared_ptr<TicketComponent> component) {
        components.erase(std::remove(components.begin(), components.end(), component), components.end());
    }

    void display() const override {
        std::cout << "Ticket Package:" << std::endl;
        for (const auto& component : components) {
            component->display();
        }
    }

    double getPrice() const override {
        double total = 0.0;
        for (const auto& component : components) {
            total += component->getPrice();
        }
        return total;
    }

private:
    std::vector<std::shared_ptr<TicketComponent>> components;
};


int main() {
    
    auto ticket1 = std::make_shared<StandardTicket>("Regular Seat", 50.0);
    auto ticket2 = std::make_shared<StandardTicket>("VIP Seat", 150.0);

    
    auto package = std::make_shared<TicketPackage>();
    package->add(ticket1);
    package->add(ticket2);

    
    auto superPackage = std::make_shared<TicketPackage>();
    superPackage->add(package); 
    superPackage->add(std::make_shared<StandardTicket>("Premium Seat", 250.0));

    
    std::cout << "Individual Ticket:" << std::endl;
    ticket1->display();

    std::cout << "\nTicket Package:" << std::endl;
    package->display();
    std::cout << "Total Package Price: $" << package->getPrice() << std::endl;

    std::cout << "\nSuper Ticket Package:" << std::endl;
    superPackage->display();
    std::cout << "Total Super Package Price: $" << superPackage->getPrice() << std::endl;

    return 0;
}