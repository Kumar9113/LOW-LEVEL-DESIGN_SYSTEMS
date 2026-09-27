#include <iostream>
using namespace std;

// =============================
// Product
// =============================

class Notification {
public:

    virtual void send() = 0;

    virtual ~Notification() {}
};


// =============================
// Concrete Product 1
// =============================

class EmailNotification : public Notification {

public:

    void send() override {
        cout << "Sending Email" << endl;
    }
};


// =============================
// Concrete Product 2
// =============================

class SMSNotification : public Notification {

public:

    void send() override {
        cout << "Sending SMS" << endl;
    }
};


// =============================
// Creator
// =============================

class NotificationFactory {

public:

    virtual Notification* createNotification() = 0;

    virtual ~NotificationFactory() {}
};


// =============================
// Concrete Creator 1
// =============================

class EmailFactory : public NotificationFactory {

public:

    Notification* createNotification() override {

        return new EmailNotification();
    }
};


// =============================
// Concrete Creator 2
// =============================

class SMSFactory : public NotificationFactory {

public:

    Notification* createNotification() override {

        return new SMSNotification();
    }
};


// =============================
// Main
// =============================

int main() {

    // Email

    NotificationFactory* factory1 = new EmailFactory();

    Notification* notification1 =
        factory1->createNotification();

    notification1->send();


    // SMS

    NotificationFactory* factory2 = new SMSFactory();

    Notification* notification2 =
        factory2->createNotification();

    notification2->send();


    // Free memory

    delete notification1;
    delete factory1;

    delete notification2;
    delete factory2;

    return 0;
}