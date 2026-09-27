#include <iostream>
using namespace std;

class Order;

// State interface
class State {
public:
    virtual void next(Order& order) = 0;
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
        state->next(*this);
    }
};

// Concrete State
class PendingState : public State {
public:
    void next(Order& order) override {
        cout << "Order shipped" << endl;
    }
};

// Concrete State
class ShippedState : public State {
public:
    void next(Order& order) override {
        cout << "Order delivered" << endl;
    }
};

// Concrete State
class DeliveredState : public State {
public:
    void next(Order& order) override {
        cout << "Order already delivered" << endl;
    }
};

int main() {

    PendingState pending;
    ShippedState shipped;
    DeliveredState delivered;

    Order order(&pending);

    order.next();

    order.setState(&shipped);
    order.next();

    order.setState(&delivered);
    order.next();

    return 0;
}