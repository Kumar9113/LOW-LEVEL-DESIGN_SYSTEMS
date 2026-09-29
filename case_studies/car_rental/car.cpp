#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// ================= CUSTOMER =================

class Customer {
private:
    int id;
    string name;

public:
    Customer(int id, string name) {
        this->id = id;
        this->name = name;
    }

    string getName() {
        return name;
    }

    void update() {
        cout << name
             << " is notified: Vehicle is available."
             << endl;
    }
};


// ================= VEHICLE =================

class Vehicle {
private:
    int id;
    string model;
    bool available;

    queue<Customer*> waitingQueue;

public:
    Vehicle(int id, string model) {
        this->id = id;
        this->model = model;
        available = true;
    }

    bool isAvailable() {
        return available;
    }

    string getModel() {
        return model;
    }

    void rent() {
        available = false;
    }

    void makeAvailable() {
        available = true;
    }

    void addObserver(Customer* customer) {
        waitingQueue.push(customer);
    }

    Customer* getNextCustomer() {

        if (waitingQueue.empty())
            return nullptr;

        Customer* customer = waitingQueue.front();

        waitingQueue.pop();

        return customer;
    }
};


// ================= RENTAL =================

class Rental {
private:
    Customer* customer;
    Vehicle* vehicle;
    int days;
    double price;

public:
    Rental(Customer* customer,
           Vehicle* vehicle,
           int days,
           double price) {

        this->customer = customer;
        this->vehicle = vehicle;
        this->days = days;
        this->price = price;
    }

    void showRental() {

        cout << customer->getName()
             << " rented "
             << vehicle->getModel()
             << " for "
             << days
             << " days. Price = "
             << price
             << endl;
    }
};


// ================= RENTAL SYSTEM =================

class RentalSystem {
private:
    vector<Vehicle*> vehicles;
    vector<Rental*> rentals;

public:

    void addVehicle(Vehicle* vehicle) {
        vehicles.push_back(vehicle);
    }


    void rentVehicle(Vehicle* vehicle,
                     Customer* customer,
                     int days,
                     double pricePerDay) {

        if (!vehicle->isAvailable()) {

            vehicle->addObserver(customer);

            cout << customer->getName()
                 << " added to waiting list."
                 << endl;

            return;
        }

        vehicle->rent();

        double price = days * pricePerDay;

        Rental* rental =
            new Rental(customer,
                       vehicle,
                       days,
                       price);

        rentals.push_back(rental);

        cout << "Vehicle rented successfully." << endl;

        rental->showRental();
    }


    void returnVehicle(Vehicle* vehicle) {

        vehicle->makeAvailable();

        cout << endl;
        cout << vehicle->getModel()
             << " returned."
             << endl;


        // Check waiting customers

        Customer* nextCustomer =
            vehicle->getNextCustomer();


        if (nextCustomer != nullptr) {

            // Notify first waiting customer

            nextCustomer->update();

            // Reserve vehicle for him

            vehicle->rent();

            cout << vehicle->getModel()
                 << " reserved for "
                 << nextCustomer->getName()
                 << endl;
        }
    }
};

int main() {

    Vehicle v1(101, "Honda City");

    Customer ravi(1, "Ravi");
    Customer kumar(2, "Kumar");
    Customer rahul(3, "Rahul");

    RentalSystem system;

    system.addVehicle(&v1);


    // Ravi rents the car

    system.rentVehicle(
        &v1,
        &ravi,
        3,
        1000
    );


    // Kumar wants the same car

    system.rentVehicle(
        &v1,
        &kumar,
        2,
        1000
    );


    // Rahul also wants the same car

    system.rentVehicle(
        &v1,
        &rahul,
        4,
        1000
    );


    // Ravi returns

    system.returnVehicle(&v1);

    return 0;
}