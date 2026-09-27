#include <iostream>
using namespace std;

// Handler
class Handler {
protected:
    Handler* nextHandler;

public:
    Handler() {
        nextHandler = nullptr;
    }

    void setNext(Handler* handler) {
        nextHandler = handler;
    }

    virtual void handle(int amount) = 0;

    virtual ~Handler() {}
};

// Employee
class Employee : public Handler {
public:
    void handle(int amount) override {

        if (amount <= 1000) {
            cout << "Employee handled the request: "
                 << amount << endl;
        }
        else if (nextHandler) {
            nextHandler->handle(amount);
        }
    }
};

// Manager
class Manager : public Handler {
public:
    void handle(int amount) override {

        if (amount <= 5000) {
            cout << "Manager handled the request: "
                 << amount << endl;
        }
        else if (nextHandler) {
            nextHandler->handle(amount);
        }
    }
};

// Director
class Director : public Handler {
public:
    void handle(int amount) override {

        if (amount <= 10000) {
            cout << "Director handled the request: "
                 << amount << endl;
        }
        else {
            cout << "Request cannot be handled: "
                 << amount << endl;
        }
    }
};

int main() {

    // Create handlers
    Employee employee;
    Manager manager;
    Director director;

    // Create the chain
    employee.setNext(&manager);
    manager.setNext(&director);

    // Send requests
    employee.handle(500);
    employee.handle(3000);
    employee.handle(8000);
    employee.handle(15000);

    return 0;
}