# 🚗 Car Rental System — LLD

A Low-Level Design implementation of a **Car Rental System** using Object-Oriented Programming and the **Observer Design Pattern** in C++.

The system allows customers to rent vehicles, handles unavailable vehicles through a waiting queue, and notifies the next waiting customer when a vehicle is returned.

---

## 📌 Features

* Add vehicles to the rental system
* Rent an available vehicle
* Maintain a waiting queue when a vehicle is unavailable
* Return a rented vehicle
* Notify the first waiting customer when the vehicle becomes available
* Reserve the returned vehicle for the notified customer
* Maintain rental records
* Calculate rental price based on number of days

---

## 🏗️ Class Design

```text
                    RentalSystem
                   /      |      \
                  /       |       \
                 ↓        ↓        ↓
             Vehicle    Rental   Customer
                |
                ↓
          Waiting Queue
                |
        ┌───────┴───────┐
        ↓               ↓
    Customer         Customer
```

### Main Classes

### 1. Customer

Represents a customer who wants to rent a vehicle.

Responsibilities:

* Store customer ID
* Store customer name
* Receive availability notifications

```cpp
class Customer {
private:
    int id;
    string name;

public:
    void update();
};
```

---

### 2. Vehicle

Represents a vehicle that can be rented.

Responsibilities:

* Store vehicle information
* Maintain availability
* Maintain waiting customers
* Add customers to waiting queue
* Notify the next waiting customer

```cpp
class Vehicle {
private:
    int id;
    string model;
    bool available;

    queue<Customer*> waitingQueue;
};
```

---

### 3. Rental

Represents one rental transaction.

Responsibilities:

* Store customer
* Store vehicle
* Store rental duration
* Store rental price

```text
Rental
 ├── Customer
 ├── Vehicle
 ├── Days
 └── Price
```

---

### 4. RentalSystem

Acts as the main controller of the application.

Responsibilities:

* Add vehicles
* Rent vehicles
* Return vehicles
* Create rental records
* Manage the overall rental flow

---

# 🔄 Rental Flow

## Case 1: Vehicle is Available

```text
Customer
    ↓
RentalSystem
    ↓
Vehicle
    ↓
Available?
    ↓ YES
Rent Vehicle
    ↓
Create Rental
```

The vehicle becomes unavailable.

---

## Case 2: Vehicle is Unavailable

```text
Customer
    ↓
RentalSystem
    ↓
Vehicle
    ↓
Available?
    ↓ NO
Waiting Queue
```

The customer is added to the vehicle's waiting queue.

Example:

```text
Honda City
    |
    ↓
Waiting Queue

Kumar
Rahul
Anil
```

The queue follows **FIFO**:

```text
First Customer In
        ↓
First Customer Notified
```

---

# 🔔 Observer Pattern

The system uses the **Observer Pattern** for vehicle availability notifications.

```text
             Subject
             Vehicle
                |
                | notify
                ↓
            Observer
            Customer
```

When a vehicle is returned:

```text
Vehicle Returned
      ↓
Check Waiting Queue
      ↓
Get First Customer
      ↓
Notify Customer
      ↓
Reserve Vehicle
```

Only the **first waiting customer** is notified because there is only one vehicle.

---

# 💰 Rental Price

The current implementation calculates the rental price as:

```text
Total Price = Number of Days × Price Per Day
```

Example:

```text
Days = 3
Price Per Day = ₹1000

Total = 3 × 1000
      = ₹3000
```

---

# 🧩 Design Principles Used

## Encapsulation

Vehicle availability is private:

```cpp
bool available;
```

It is modified through:

```cpp
rent();
makeAvailable();
```

This prevents outside classes from directly changing the vehicle's state.

---

## Composition / Association

`RentalSystem` manages vehicles and rental records:

```cpp
vector<Vehicle*> vehicles;
vector<Rental*> rentals;
```

`Rental` associates a customer with a vehicle:

```text
Customer ───── Rental ───── Vehicle
```

---

## Polymorphism

The current version focuses mainly on the rental flow.

Vehicle types such as:

```text
Car
SUV
Luxury
```

can later be introduced using inheritance and polymorphism.

---

# 📊 Complete System Flow

```text
                  Customer
                     |
                     | Request Vehicle
                     ↓
                RentalSystem
                     |
                     ↓
                  Vehicle
                     |
              Is Available?
                /        \
              YES         NO
               |           |
               ↓           ↓
             Rent      Waiting Queue
               |           |
               ↓           ↓
            Rental      Customer
                           |
                           |
                     Vehicle Returned
                           |
                           ↓
                    First Customer
                           |
                           ↓
                       Notify
                           |
                           ↓
                      Reservation
```

---

# 🧠 Interview Explanation

A simple way to explain the design in an interview:

> "The Car Rental System has four main classes: Customer, Vehicle, Rental, and RentalSystem. RentalSystem acts as the controller and handles renting and returning vehicles. Vehicle maintains its availability and a FIFO waiting queue for customers who want that vehicle. When a vehicle is returned, the first waiting customer is notified and the vehicle is reserved for that customer. Rental represents an individual rental transaction. The Observer pattern is used so that customers can receive vehicle availability notifications."

---

# 🔮 Possible Extensions

The system can be extended with:

* Different vehicle types
* Different pricing strategies
* Multiple branches/locations
* Vehicle search and filtering
* Pickup and drop-off locations
* Reservation cancellation
* Rental cancellation
* Payment system
* Customer verification
* Insurance
* Late fees
* Damage tracking
* Discount/coupon system
* Notification service
* Database persistence

---

# 🎯 Design Patterns

Current:

```text
Observer Pattern
```

Possible future patterns:

```text
Strategy Pattern
    ↓
Different pricing strategies

Factory Pattern
    ↓
Create different vehicle types

State Pattern
    ↓
Available / Rented / Reserved / Maintenance

Singleton
    ↓
Central RentalSystem (only if actually required)
```

---

# 📁 Suggested Project Structure

```text
car-rental-system/
│
├── Customer.h
├── Vehicle.h
├── Rental.h
├── RentalSystem.h
│
├── Customer.cpp
├── Vehicle.cpp
├── Rental.cpp
├── RentalSystem.cpp
│
└── main.cpp
```

For interview practice, however, keeping everything in a **single C++ file** is perfectly fine.

---

## Complexity

For the basic implementation:

| Operation                     | Complexity |
| ----------------------------- | ---------: |
| Add vehicle                   |       O(1) |
| Add customer to waiting queue |       O(1) |
| Get next waiting customer     |       O(1) |
| Return vehicle                |       O(1) |
| Create rental                 |       O(1) |

The waiting queue uses:

```cpp
queue<Customer*>
```

which naturally provides FIFO behavior.
