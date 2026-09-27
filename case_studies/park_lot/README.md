# 🚗 Parking Lot Management System

A simple **Parking Lot Management System** implemented in **C++** using Object-Oriented Programming (OOP) principles.

The system focuses only on two core operations:

* **Park a vehicle**
* **Remove a vehicle**

It intentionally does **not** include tickets, payment, billing, entry/exit gates, or other unnecessary features.

---

## 📌 Features

* Supports different vehicle types:

  * 🏍️ Bike
  * 🚗 Car
  * 🚚 Truck
* Supports different parking spot types:

  * BIKE
  * CAR
  * TRUCK
* Checks whether a parking spot is available.
* Ensures the vehicle is parked only in a matching spot type.
* Finds a vehicle using its vehicle number.
* Frees the parking spot when a vehicle leaves.
* Uses inheritance for different vehicle types.
* Uses composition/association between `ParkingLot` and `ParkingSpot`.

---

## 🏗️ Class Structure

```text
                         Vehicle
                            │
              ┌─────────────┼─────────────┐
              │             │             │
            Bike           Car          Truck
              │             │             │
              └─────────────┼─────────────┘
                            │
                            ▼
                     ParkingSpot
                            │
                            │ managed by
                            ▼
                       ParkingLot
```

---

# 📦 Classes

## 1. Vehicle

The base class for all vehicles.

```cpp
class Vehicle {
    string vehicleNo;
    string type;
};
```

### Responsibilities

* Store vehicle number.
* Store vehicle type.
* Provide getters for vehicle number and type.

Example:

```text
Vehicle No: TS01AB1234
Type: BIKE
```

---

## 2. Bike

Derived from `Vehicle`.

```cpp
class Bike : public Vehicle {
public:
    Bike(string vehicleNo)
        : Vehicle(vehicleNo, "BIKE") {}
};
```

When a `Bike` object is created, its type is automatically set to `"BIKE"`.

---

## 3. Car

Derived from `Vehicle`.

```cpp
class Car : public Vehicle {
public:
    Car(string vehicleNo)
        : Vehicle(vehicleNo, "CAR") {}
};
```

---

## 4. Truck

Derived from `Vehicle`.

```cpp
class Truck : public Vehicle {
public:
    Truck(string vehicleNo)
        : Vehicle(vehicleNo, "TRUCK") {}
};
```

---

# 🅿️ ParkingSpot

Represents one individual parking space.

```cpp
class ParkingSpot {
    int spotId;
    string type;
    Vehicle* vehicle;
};
```

### Attributes

| Attribute | Purpose                              |
| --------- | ------------------------------------ |
| `spotId`  | Unique ID of the parking spot        |
| `type`    | Type of vehicle the spot accepts     |
| `vehicle` | Vehicle currently occupying the spot |

If no vehicle is parked:

```cpp
vehicle == nullptr
```

Therefore:

```cpp
bool isAvailable() {
    return vehicle == nullptr;
}
```

---

## Parking Spot Matching

A vehicle can park only if its type matches the parking spot type.

```cpp
bool canPark(Vehicle* vehicle) {
    return type == vehicle->getType();
}
```

Example:

```text
CAR vehicle
    ↓
CAR parking spot
    ↓
      ✓ Allowed
```

But:

```text
CAR vehicle
    ↓
BIKE parking spot
    ↓
      ✗ Not allowed
```

---

# 🏢 ParkingLot

`ParkingLot` manages all parking spots.

```cpp
class ParkingLot {
    vector<ParkingSpot*> spots;
};
```

Its main responsibilities are:

```text
ParkingLot
    │
    ├── addSpot()
    ├── parkVehicle()
    └── leaveVehicle()
```

---

# 🚗 Park Vehicle

Method:

```cpp
bool parkVehicle(Vehicle* vehicle)
```

### Flow

```text
             Vehicle arrives
                    │
                    ▼
             parkVehicle()
                    │
                    ▼
          Check all parking spots
                    │
                    ▼
          Is spot available?
              /           \
            NO             YES
            │               │
        Next spot       Check type
                            │
                     ┌──────┴──────┐
                     │             │
                  Different      Same
                     │             │
                  Next spot      Park
                                   │
                                   ▼
                              Return true
```

Example:

```text
Vehicle:
TS09CD1111
CAR

Parking spots:

Spot 1 → BIKE → Occupied
Spot 2 → BIKE → Empty
Spot 3 → CAR  → Empty
Spot 4 → CAR  → Empty

                 ↓

Vehicle gets Spot 3
```

---

# 🚪 Leave Vehicle

Method:

```cpp
bool leaveVehicle(string vehicleNo)
```

The parking lot searches for the vehicle using its vehicle number.

### Flow

```text
          Vehicle Number
                │
                ▼
        leaveVehicle()
                │
                ▼
       Search all spots
                │
                ▼
          Vehicle found?
           /          \
         NO            YES
         │              │
       Reject        Remove vehicle
                        │
                        ▼
                  Spot becomes free
                        │
                        ▼
                    Return true
```

Example:

```text
Before:

Spot 1 → BIKE
Spot 2 → BIKE
Spot 3 → CAR → TS09CD1111
Spot 4 → CAR

        ↓

TS09CD1111 leaves

        ↓

After:

Spot 1 → BIKE
Spot 2 → BIKE
Spot 3 → EMPTY
Spot 4 → CAR
```

---

# 🔄 Complete System Flow

```text
                    ┌──────────────┐
                    │   Vehicle    │
                    └──────┬───────┘
                           │
                           ▼
                 ┌──────────────────┐
                 │   ParkingLot     │
                 └────────┬─────────┘
                          │
              ┌───────────┴───────────┐
              │                       │
              ▼                       ▼
       parkVehicle()            leaveVehicle()
              │                       │
              ▼                       ▼
      Find suitable spot       Find vehicle
              │                       │
              ▼                       ▼
       Assign vehicle          Remove vehicle
              │                       │
              ▼                       ▼
        Spot occupied          Spot available
```

---

# 🧩 Relationships

### Inheritance

```text
Vehicle
   ▲
   │
 ┌─┼────────────┐
 │ │            │
Bike Car       Truck
```

`Bike`, `Car`, and `Truck` **is-a** `Vehicle`.

---

### Association

A `ParkingSpot` has a reference to the vehicle currently parked in it.

```text
ParkingSpot ──────── Vehicle
```

---

### ParkingLot → ParkingSpot

The parking lot maintains a collection of parking spots.

```text
ParkingLot
     │
     ├── ParkingSpot
     ├── ParkingSpot
     ├── ParkingSpot
     └── ParkingSpot
```

---

# 🎯 OOP Concepts Used

| Concept                    | Usage                                       |
| -------------------------- | ------------------------------------------- |
| **Encapsulation**          | Data members are private                    |
| **Inheritance**            | `Bike`, `Car`, `Truck` inherit `Vehicle`    |
| **Abstraction**            | Each class handles its own responsibility   |
| **Polymorphism**           | `Vehicle*` can point to Bike, Car, or Truck |
| **Association**            | Parking spot stores `Vehicle*`              |
| **Composition/Management** | Parking lot manages parking spots           |

---

# 💡 Why No Design Pattern?

For this simplified requirement, we don't need a design pattern.

The requirements are only:

```text
Park vehicle
     +
Leave vehicle
```

Therefore, adding Factory, Strategy, Observer, Singleton, etc. would unnecessarily complicate the design.

The design should be extended only when requirements actually justify it.

---

# 🧪 Example

```cpp
ParkingLot parkingLot;

ParkingSpot* bikeSpot = new ParkingSpot(1, "BIKE");
ParkingSpot* carSpot = new ParkingSpot(2, "CAR");

parkingLot.addSpot(bikeSpot);
parkingLot.addSpot(carSpot);

Vehicle* bike = new Bike("TS01AB1234");
Vehicle* car = new Car("TS09CD1111");

parkingLot.parkVehicle(bike);
parkingLot.parkVehicle(car);

parkingLot.leaveVehicle("TS09CD1111");
```

Expected behavior:

```text
TS01AB1234 parked at spot 1
TS09CD1111 parked at spot 2
TS09CD1111 left spot 2
```

---

# ⏱️ Complexity

Let:

* `N` = number of parking spots

### Park

We may need to check every spot:

```text
Time: O(N)
```

### Leave

We search every spot for the vehicle:

```text
Time: O(N)
```

### Space

The parking lot stores `N` parking spots:

```text
Space: O(N)
```

---

# 🎤 Interview Explanation

If asked to explain the design:

> "I have modeled the system using three main concepts: Vehicle, ParkingSpot, and ParkingLot. Vehicle is the base class with Bike, Car, and Truck as derived classes. Each ParkingSpot has a type and can hold one vehicle. ParkingLot maintains a collection of parking spots and provides two operations: parkVehicle and leaveVehicle. When parking, we find an available spot whose type matches the vehicle. When leaving, we search for the vehicle by its number and free the corresponding spot. Since the requirements are simple, I have intentionally avoided unnecessary design patterns."

---

# 🚀 Possible Future Extensions

If requirements increase, we can add:

```text
Current System
      │
      ├── Ticket
      ├── Payment
      ├── Pricing Strategy
      ├── Multiple Floors
      ├── Entry/Exit Gates
      ├── Display Board
      ├── Vehicle Search
      └── Nearest Spot Strategy
```

For example, if the requirement becomes:

> "Always assign the nearest available spot."

Then a **Strategy Pattern** could be introduced.

---

# 📁 Suggested Project Structure

```text
ParkingLot/
│
├── Vehicle.h
├── ParkingSpot.h
├── ParkingLot.h
├── Vehicle.cpp
├── ParkingSpot.cpp
├── ParkingLot.cpp
└── main.cpp
```

For interview practice, however, keeping everything in a single `.cpp` file is completely fine.

---

## ✅ Current Scope

```text
                    PARKING LOT
                         │
             ┌───────────┴───────────┐
             │                       │
          PARK                     LEAVE
             │                       │
       Find suitable            Find vehicle
           spot                      │
             │                       ▼
             ▼                  Free spot
        Assign vehicle
```

**No ticket • No payment • No billing • No gates**
