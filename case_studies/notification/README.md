# Notification System — Low-Level Design

## 1. Problem Statement

Design a Notification System that supports multiple notification channels such as:

* Email
* SMS
* Push Notification

The system should allow the notification channel to be changed without modifying the main notification service.

---

## 2. Requirements

### Functional Requirements

* Send notifications to users.
* Support multiple notification channels.
* Create notification objects without tightly coupling the service to concrete classes.
* Easily add new notification channels in the future.

### Non-Functional Requirements

* Low coupling
* Easy extensibility
* Follow SOLID principles
* Follow programming to an interface

---

## 3. Design

```text
                    Notification
                         ^
                         |
              +----------+----------+
              |          |          |
            Email        SMS       Push
          Notification Notification Notification


                 NotificationFactory
                         ^
                         |
          +--------------+--------------+
          |              |              |
     EmailFactory    SMSFactory    PushFactory
          |              |              |
          v              v              v
       Email           SMS            Push
```

---

## 4. Classes

### Notification

Abstract base class for all notification types.

```cpp
class Notification {
protected:
    string user;

public:
    virtual void send(string message) = 0;
};
```

It defines the common interface:

```cpp
send()
```

---

### EmailNotification

Responsible for sending email notifications.

```text
EmailNotification
        |
        +-- send()
```

---

### SMSNotification

Responsible for sending SMS notifications.

```text
SMSNotification
        |
        +-- send()
```

---

### PushNotification

Responsible for sending push notifications.

```text
PushNotification
        |
        +-- send()
```

---

## 5. Factory

`NotificationFactory` is the common factory interface.

```cpp
class NotificationFactory {
public:
    virtual Notification* createNotification(
        string user
    ) = 0;
};
```

Concrete factories:

```text
NotificationFactory
        |
        +---- EmailFactory
        |
        +---- SMSFactory
        |
        +---- PushFactory
```

Each factory is responsible for creating its corresponding notification object.

---

## 6. NotificationService

`NotificationService` does not directly depend on:

```text
EmailNotification
SMSNotification
PushNotification
```

Instead, it depends on:

```text
NotificationFactory
```

```cpp
class NotificationService {

    NotificationFactory* factory;

public:

    NotificationService(
        NotificationFactory* factory
    ) {
        this->factory = factory;
    }

    void send(string user, string message) {

        Notification* notification =
            factory->createNotification(user);

        notification->send(message);

        delete notification;
    }
};
```

This reduces coupling.

---

## 7. Flow

For Email:

```text
Client
  |
  v
EmailFactory
  |
  v
EmailNotification
  |
  v
send()
  |
  v
Email sent
```

For SMS:

```text
Client
  |
  v
SMSFactory
  |
  v
SMSNotification
  |
  v
send()
  |
  v
SMS sent
```

For Push:

```text
Client
  |
  v
PushFactory
  |
  v
PushNotification
  |
  v
send()
  |
  v
Push notification sent
```

---

## 8. Design Patterns

### Factory Pattern

The factory is responsible for object creation.

Instead of:

```cpp
new EmailNotification(...)
```

inside the service, the service asks the factory:

```cpp
factory->createNotification(...)
```

---

### Strategy-like Behavior

The service works with the common:

```cpp
Notification
```

interface.

Therefore the actual notification behavior can be changed by providing a different factory.

---

## 9. SOLID Principles

### Single Responsibility Principle

Each class has one major responsibility:

```text
EmailNotification → Email sending
SMSNotification   → SMS sending
PushNotification  → Push sending

EmailFactory      → Create EmailNotification
SMSFactory        → Create SMSNotification
PushFactory       → Create PushNotification
```

### Open/Closed Principle

To add a new notification type such as WhatsApp:

```text
WhatsAppNotification
WhatsAppFactory
```

can be added without modifying the existing notification classes.

### Dependency Inversion Principle

`NotificationService` depends on:

```cpp
NotificationFactory*
```

instead of concrete factories or concrete notification classes.

---

## 10. Adding WhatsApp

We can extend the system like this:

```text
Notification
     |
     +-- EmailNotification
     +-- SMSNotification
     +-- PushNotification
     +-- WhatsAppNotification


NotificationFactory
     |
     +-- EmailFactory
     +-- SMSFactory
     +-- PushFactory
     +-- WhatsAppFactory
```

No changes are required inside `NotificationService`.

---

## 11. Interview Explanation

### Why use a factory?

The service should not contain object-creation logic.

Bad:

```cpp
if(type == "email")
    new EmailNotification();

else if(type == "sms")
    new SMSNotification();
```

This creates tight coupling.

Instead:

```cpp
NotificationFactory* factory;
```

The factory handles object creation.

---

### Why use an abstract base class?

Because all notification channels provide the same operation:

```cpp
send()
```

So the service can work with:

```cpp
Notification*
```

without knowing the concrete implementation.

---

## 12. Important Note

With only one product hierarchy:

```text
Notification
   |
   +-- Email
   +-- SMS
   +-- Push
```

the design is more precisely a **Factory Method / factory hierarchy**.

A textbook **Abstract Factory** normally creates a **family of related products**.

For example:

```text
EmailFactory
     |
     +-- EmailNotification
     +-- EmailFormatter
     +-- EmailProvider


SMSFactory
     |
     +-- SMSNotification
     +-- SMSFormatter
     +-- SMSProvider
```

That would be a true Abstract Factory design.

---

## 13. Key Interview Takeaway

```text
Client
  |
  v
NotificationService
  |
  v
NotificationFactory
  |
  +------ EmailFactory ------> EmailNotification
  |
  +------ SMSFactory --------> SMSNotification
  |
  +------ PushFactory -------> PushNotification
```

**Main idea:**

> Separate object creation from object usage so that the NotificationService depends on abstractions rather than concrete notification classes.
