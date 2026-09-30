#include<bits/stdc++.h>
using namespace std;


// =========================
// Product
// =========================

class Notification {

protected:
    string user;

public:

    Notification(string user) {
        this->user = user;
    }

    virtual void send(string message) = 0;

    virtual ~Notification() {}
};


// =========================
// Concrete Products
// =========================

class EmailNotification : public Notification {

public:

    EmailNotification(string user)
        : Notification(user) {}

    void send(string message) {

        cout << "Email sent to "
             << user << ": "
             << message << endl;
    }
};


class SMSNotification : public Notification {

public:

    SMSNotification(string user)
        : Notification(user) {}

    void send(string message) {

        cout << "SMS sent to "
             << user << ": "
             << message << endl;
    }
};


class PushNotification : public Notification {

public:

    PushNotification(string user)
        : Notification(user) {}

    void send(string message) {

        cout << "Push notification sent to "
             << user << ": "
             << message << endl;
    }
};


// =========================
// Abstract Factory
// =========================

class NotificationFactory {

public:

    virtual Notification* createNotification(
        string user
    ) = 0;

    virtual ~NotificationFactory() {}
};


// =========================
// Concrete Factory
// =========================

class EmailFactory : public NotificationFactory {

public:

    Notification* createNotification(
        string user
    ) {

        return new EmailNotification(user);
    }
};


class SMSFactory : public NotificationFactory {

public:

    Notification* createNotification(
        string user
    ) {

        return new SMSNotification(user);
    }
};


class PushFactory : public NotificationFactory {

public:

    Notification* createNotification(
        string user
    ) {

        return new PushNotification(user);
    }
};


// =========================
// Notification Service
// =========================

class NotificationService {

    NotificationFactory* factory;

public:

    NotificationService(
        NotificationFactory* factory
    ) {

        this->factory = factory;
    }

    void send(
        string user,
        string message
    ) {

        Notification* notification =
            factory->createNotification(user);

        notification->send(message);

        delete notification;
    }
};


// =========================
// Main
// =========================

int main() {

    EmailFactory emailFactory;

    NotificationService emailService(
        &emailFactory
    );

    emailService.send(
        "kumar@gmail.com",
        "Your order has been shipped."
    );


    SMSFactory smsFactory;

    NotificationService smsService(
        &smsFactory
    );

    smsService.send(
        "9876543210",
        "Your OTP is 123456."
    );


    PushFactory pushFactory;

    NotificationService pushService(
        &pushFactory
    );

    pushService.send(
        "Kumar's Mobile",
        "You have a new message."
    );


    return 0;
}