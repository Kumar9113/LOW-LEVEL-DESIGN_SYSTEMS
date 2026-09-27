#include <iostream>
using namespace std;

// State Interface
class State {
public:
    virtual void next() = 0;
    virtual ~State() {}
};

// Context
class Order {
private:
    State* state;

public:
    Order(State* state) {
        this->state = state;
    }

    void setState(State* state) {
        this->state = state;
    }

    void next() {
        state->next();
    }
};

// Concrete State 1
class PendingState : public State {
public:
    void next() override {
        cout << "Order shipped" << endl;
    }
};

// Concrete State 2
class ShippedState : public State {
public:
    void next() override {
        cout << "Order delivered" << endl;
    }
};

// Concrete State 3
class DeliveredState : public State {
public:
    void next() override {
        cout << "Order already delivered" << endl;
    }
};

int main() {

    PendingState pending;
    ShippedState shipped;
    DeliveredState delivered;

    // Initial state = Pending
    Order order(&pending);

    order.next();

    // Change state to Shipped
    order.setState(&shipped);
    order.next();

    // Change state to Delivered
    order.setState(&delivered);
    order.next();

    return 0;
}