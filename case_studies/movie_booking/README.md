# 🎬 Movie Ticket Booking System — LLD

A simple **Low-Level Design (LLD)** implementation of a Movie Ticket Booking System using **C++**.

The system allows users to:

* View movies and shows
* Select seats
* Book multiple seats
* Prevent double booking using concurrency control
* Cancel bookings
* Release cancelled seats
* Maintain separate seat availability for every show

The design focuses on **simple, interview-friendly object-oriented design** without unnecessary abstractions.

---

## 📌 System Flow

```text
User
  |
  v
BookingSystem
  |
  v
Select Movie
  |
  v
Select Cinema
  |
  v
Select Screen
  |
  v
Select Show
  |
  v
Select Seats
  |
  v
Show.bookSeats()
  |
  v
Lock Mutex
  |
  v
Check All Seats
  |
  +----------------------+
  |                      |
  v                      v
All Available         Any Booked
  |                      |
  v                      v
Book All Seats       Booking Failed
  |
  v
Create Booking
  |
  v
Booking Confirmed
```

---

# 🏗️ Class Structure

```text
                    BookingSystem
                         |
             +-----------+-----------+
             |                       |
           Movie                   Cinema
                                     |
                                   Screen
                                     |
                                   Seat
                                     |
                                    Show
                                     |
                                  Booking
                                     |
                                    User
```

---

# 📦 Classes

## 1. User

Represents a customer who wants to book movie tickets.

```cpp
class User
```

### Responsibilities

* Store user ID
* Store user name
* Provide user information

---

## 2. Movie

Represents a movie.

```cpp
class Movie
```

### Attributes

```text
id
name
language
```

### Example

```text
Avengers
English
```

---

## 3. Seat

Represents the physical seat information.

```cpp
class Seat
```

### Attributes

```text
id
number
price
```

Example:

```text
A1 → ₹200
A2 → ₹200
A3 → ₹200
```

### Important Design Decision

`Seat` does **not** maintain availability.

Availability depends on the **show**.

For example:

```text
7 PM Show

A1 → BOOKED
A2 → AVAILABLE


10 PM Show

A1 → AVAILABLE
A2 → AVAILABLE
```

The same physical screen can have different availability for different shows.

---

# 4. Screen

Represents a cinema screen.

```cpp
class Screen
```

A screen contains multiple seats.

```text
Screen
  |
  +-- A1
  +-- A2
  +-- A3
  +-- A4
```

---

# 5. Show

Represents a particular movie running on a particular screen at a particular time.

```cpp
class Show
```

### Contains

```text
Movie
Screen
Start Time
Seat Availability
```

The important part is:

```cpp
map<int, bool> seatAvailability;
```

Example:

```text
Seat ID    Availability

1          true
2          false
3          true
4          true
```

`true` means available.

`false` means booked.

---

# 🔒 Concurrency Handling

The most important part of the system is preventing two users from booking the same seat.

Suppose:

```text
Ravi  → A1
Kumar → A1
```

at the same time.

Without synchronization:

```text
Ravi  → Check A1 → Available
Kumar → Check A1 → Available

Ravi  → Book A1
Kumar → Book A1

❌ Double Booking
```

---

## Solution

Use a mutex inside `Show`.

```cpp
mutex mtx;
```

During booking:

```cpp
lock_guard<mutex> lock(mtx);
```

Then:

```text
LOCK
  |
  v
Check seats
  |
  v
Book seats
  |
  v
UNLOCK
```

Therefore, **checking and booking happen atomically**.

---

# 🎟️ Booking Flow

The `BookingSystem` receives the booking request.

```cpp
bookTickets(user, show, seatIds)
```

Then:

```text
BookingSystem
      |
      v
Show.bookSeats()
      |
      v
Check seats
      |
      +---- unavailable → FAIL
      |
      v
Book seats
      |
      v
Create Booking
      |
      v
Store Booking
```

---

# 🎫 Booking

The `Booking` class stores:

```text
Booking ID
User
Show
Selected Seats
Total Price
Active/Cancelled status
```

Example:

```text
Booking ID : 1
User       : Ravi
Movie      : Avengers
Show Time  : 7:00 PM
Seats      : A1 A2
Total Price: 400
Status     : CONFIRMED
```

---

# ❌ Cancellation

When a user cancels:

```cpp
booking->cancel();
```

Flow:

```text
Cancel Booking
      |
      v
Release Seats
      |
      v
Mark Booking Cancelled
```

Example:

```text
Before:

A1 → BOOKED
A2 → BOOKED


After Cancellation:

A1 → AVAILABLE
A2 → AVAILABLE
```

---

# 🏢 Cinema

A cinema contains multiple screens.

```text
Cinema
  |
  +-- Screen 1
  |     +-- A1
  |     +-- A2
  |
  +-- Screen 2
        +-- A1
        +-- A2
```

A cinema can also contain multiple shows.

---

# 🧩 Relationships

### Cinema → Screen

**Composition / Has-A relationship**

```text
Cinema has Screens
```

### Screen → Seat

```text
Screen has Seats
```

### Show → Movie

```text
Show is for a Movie
```

### Show → Screen

```text
Show runs on a Screen
```

### Booking → User

```text
Booking belongs to a User
```

### Booking → Show

```text
Booking is for a Show
```

---

# 🔑 Main Responsibilities

| Class           | Responsibility                            |
| --------------- | ----------------------------------------- |
| `User`          | Customer information                      |
| `Movie`         | Movie information                         |
| `Seat`          | Seat information and price                |
| `Screen`        | Contains seats                            |
| `Show`          | Movie + screen + time + seat availability |
| `Cinema`        | Contains screens and shows                |
| `Booking`       | Stores booking details                    |
| `BookingSystem` | Handles booking requests                  |

---

# 🧠 Important Interview Design Decision

### Why is seat availability inside `Show`?

Because the same screen can have multiple shows.

Example:

```text
Screen 1

7:00 PM Avengers
10:00 PM Avengers
```

A user books A1 for 7 PM.

That should **not** make A1 unavailable for the 10 PM show.

Therefore:

```text
Screen
  |
  +-- Physical Seat A1
          |
          +-- 7 PM Show → BOOKED
          |
          +-- 10 PM Show → AVAILABLE
```

This is one of the most important design decisions in this system.

---

# 🔐 Concurrency

### Single-process C++

We use:

```cpp
mutex
lock_guard<mutex>
```

The critical section is:

```cpp
lock_guard<mutex> lock(mtx);

Check all seats;

Book all seats;
```

This prevents:

```text
User A ──┐
         ├── Same Seat
User B ──┘
```

from both successfully booking it.

---

# 🌐 Production-Level Concurrency

In a real distributed application:

```text
Server 1
Server 2
Server 3
```

A C++ mutex only protects one process.

For multiple servers, the database should handle concurrency using mechanisms such as:

```text
Database Transaction
       +
Row-Level Locking
```

or:

```text
Optimistic Locking
       +
Version Number
```

### Interview Answer

> "For a single-process implementation, I use a mutex around the seat availability check and booking operation. In a distributed system, I would use database transactions with row-level locking or optimistic concurrency control."

---

# 📊 Complexity

Suppose:

* `S` = number of seats in a screen
* `K` = number of seats being booked

### Book Seats

Checking selected seats:

```text
O(K)
```

Updating selected seats:

```text
O(K)
```

So:

```text
Time: O(K)
```

If `getSeat()` searches through the screen's seats, calculating booking price/display can take:

```text
O(K × S)
```

For a simple interview implementation this is acceptable.

---

# 🎯 Design Patterns

This version intentionally does **not** force design patterns everywhere.

The main focus is:

### 1. Encapsulation

Each class manages its own data.

Example:

```cpp
Show::bookSeats()
Show::cancelSeats()
```

instead of allowing outside classes to directly modify availability.

### 2. Association

Objects reference related objects:

```text
Booking → User
Booking → Show
Show → Movie
Show → Screen
```

### 3. Concurrency Control

`Show` protects seat booking using:

```cpp
mutex
```

---

# 📁 Suggested Project Structure

```text
MovieTicketBooking/
│
├── User.h
├── Movie.h
├── Seat.h
├── Screen.h
├── Show.h
├── Cinema.h
├── Booking.h
├── BookingSystem.h
│
├── main.cpp
│
└── README.md
```

For an interview, keeping everything in one file is also perfectly fine.

---

# 🚀 Future Improvements

The system can be extended with:

* Multiple cities
* Multiple cinemas
* Multiple screens
* Multiple movies
* Different seat types
* Premium seats
* Different pricing
* Payment system
* Ticket generation
* Email/SMS notification
* Seat hold for a few minutes
* Booking history
* Search and filtering
* Database persistence
* Distributed locking

---

# 🎤 Interview Explanation

If the interviewer asks:

**"Explain your Movie Ticket Booking System."**

You can say:

> "I designed the system around User, Movie, Cinema, Screen, Seat, Show, Booking, and BookingSystem classes. A Screen contains the physical seat layout, while a Show maintains its own seat availability because the same screen can host multiple shows. The BookingSystem receives a booking request and delegates seat booking to the Show. To prevent double booking, I protect the seat availability check and update using a mutex so both operations happen atomically. Once the seats are successfully booked, a Booking object is created. During cancellation, the seats are released and the booking is marked inactive."

---

# ⭐ Most Important Points to Remember

```text
1. Screen → contains physical seats

2. Show → maintains seat availability

3. BookingSystem → handles booking request

4. Booking → stores booking details

5. mutex → prevents double booking

6. Check + Book must be atomic

7. Cancellation → releases seats

8. Distributed system → DB locking/optimistic locking
```

This keeps the design **simple enough to implement in an interview but strong enough to explain the important LLD and concurrency decisions**.
