#include <iostream>
using namespace std;

// Subsystem 1
class Payment {
public:
    void pay() {
        cout << "Payment completed" << endl;
    }
};

// Subsystem 2
class Inventory {
public:
    void update() {
        cout << "Inventory updated" << endl;
    }
};

// Subsystem 3
class Shipping {
public:
    void ship() {
        cout << "Order shipped" << endl;
    }
};

// Subsystem 4
class Notification {
public:
    void send() {
        cout << "Notification sent" << endl;
    }
};

// Facade
class OrderFacade {
private:
    Payment payment;
    Inventory inventory;
    Shipping shipping;
    Notification notification;

public:
    void placeOrder() {
        payment.pay();
        inventory.update();
        shipping.ship();
        notification.send();
    }
};

int main() {

    OrderFacade order;

    order.placeOrder();

    return 0;
}