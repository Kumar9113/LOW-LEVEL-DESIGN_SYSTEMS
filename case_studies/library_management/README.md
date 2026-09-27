# 📚 Library Management System — LLD

A simple **Library Management System** implemented in **C++** to demonstrate object-oriented design and commonly used **Low-Level Design (LLD) concepts and design patterns**.

## 🚀 Features

* Add books to the library
* Add library members
* Support different member types:

  * Student
  * Faculty
* Search books
* Check book availability
* Issue books to members
* Return books
* Track books currently borrowed by each member
* Notify members when an unavailable book becomes available
* Prevent issuing an already borrowed book
* Prevent returning a book that the member does not have

---

## 🏗️ Class Structure

```text
                         Library
                       /         \
                      /           \
                  Books          Members
                    │               │
                    ▼               ▼
                  Book            Member
                                    │
                              ┌─────┴─────┐
                              ▼           ▼
                           Student      Faculty


                  MemberFactory
                        │
                 ┌──────┴──────┐
                 ▼             ▼
              Student        Faculty


                    Book
                     │
                     │ observers
                     ▼
               vector<Member*>
                     │
               ┌─────┴─────┐
               ▼           ▼
             Member      Member
```

---

# 🧩 Main Classes

## 1. Book

Represents a book available in the library.

### Attributes

```cpp
int bookId;
string title;
string author;
bool available;
vector<Member*> observers;
```

### Responsibilities

* Store book information
* Maintain availability status
* Maintain members waiting for notification
* Notify members when the book becomes available

---

## 2. Member

Represents a person who can borrow books.

### Attributes

```cpp
int memberId;
string name;
vector<Book*> books;
```

### Responsibilities

* Store member information
* Maintain currently borrowed books
* Add a borrowed book
* Remove a returned book
* Check whether the member has a particular book
* Receive availability notifications

---

## 3. Student

Derived from `Member`.

```text
Member
   ▲
   │
Student
```

Used to represent student members.

---

## 4. Faculty

Derived from `Member`.

```text
Member
   ▲
   │
Faculty
```

Used to represent faculty members.

---

## 5. MemberFactory

Creates different types of members.

```cpp
Member* createStudent(int id, string name);
Member* createFaculty(int id, string name);
```

This avoids putting object-creation logic throughout the application.

---

## 6. Library

The main coordinator of the system.

### Responsibilities

```text
Library
 ├── addBook()
 ├── addMember()
 ├── searchBook()
 ├── isAvailable()
 ├── issueBook()
 ├── returnBook()
 └── subscribe()
```

The `Library` maintains:

```cpp
vector<Book*> books;
vector<Member*> members;
```

---

# 🎨 Design Patterns

## 1. Factory Pattern

Used for creating different types of members.

```text
              MemberFactory
                    │
          ┌─────────┴─────────┐
          ▼                   ▼
      Student              Faculty
```

Example:

```cpp
Member* student =
    MemberFactory::createStudent(
        1,
        "Kumar"
    );

Member* faculty =
    MemberFactory::createFaculty(
        2,
        "Ravi"
    );
```

### Why Factory?

Instead of directly creating objects everywhere:

```cpp
new Student(...);
new Faculty(...);
```

object creation is centralized inside:

```cpp
MemberFactory
```

---

# 🔔 Observer Pattern

The notification system uses a simplified Observer design.

When a book is unavailable, a member can request notification.

```text
Book is unavailable
        │
        ▼
Member wants notification
        │
        ▼
book.addObserver(member)
        │
        ▼
Member stored in observers[]
```

When the book is returned:

```text
Book returned
     │
     ▼
available = true
     │
     ▼
notifyObservers()
     │
     ▼
Member receives notification
```

### Example

```text
Clean Code
available = false

Ravi wants Clean Code
        ↓
Ravi subscribes
        ↓
Book.observers = [Ravi]
        ↓
Kumar returns Clean Code
        ↓
available = true
        ↓
Ravi is notified
```

### Important Rule

A member should **not subscribe if the book is already available**.

Instead:

```text
Book available
      ↓
Member can borrow directly
```

Subscription is useful only when:

```text
Book unavailable
      ↓
Member wants to know
when it becomes available
```

---

# 🔄 Issue Book Flow

```text
              issueBook()
                   │
                   ▼
              Find Book
                   │
              ┌────┴────┐
              │         │
            Found     Not Found
              │
              ▼
          Find Member
              │
         ┌────┴────┐
         │         │
       Found     Not Found
         │
         ▼
    Is Book Available?
         │
      ┌──┴───┐
      │      │
     YES     NO
      │      │
      ▼      ▼
 Add Book   Reject
 to Member
      │
      ▼
available = false
```

---

# 🔄 Return Book Flow

```text
              returnBook()
                    │
                    ▼
                Find Book
                    │
                    ▼
               Find Member
                    │
                    ▼
             Does member
             have the book?
                /      \
              NO        YES
              │          │
              ▼          ▼
            Reject    Remove Book
                          │
                          ▼
                   available = true
                          │
                          ▼
                  notifyObservers()
                          │
                          ▼
                    Clear observers
```

---

# 🔔 Notification Flow

```text
Book is borrowed
       │
       ▼
available = false
       │
       ▼
Member requests notification
       │
       ▼
addObserver(member)
       │
       ▼
Member stored in observers[]
       │
       ▼
Book is returned
       │
       ▼
available = true
       │
       ▼
notifyObservers()
       │
       ▼
member->notify(book)
       │
       ▼
"Book is now available!"
```

---

# 🧠 Relationships

### Inheritance

```text
          Member
          /    \
         /      \
    Student    Faculty
```

### Association

```text
Member ───────────► Book
       borrows
```

A member maintains pointers to books currently borrowed.

### Composition of Library's Collections

```text
Library
 ├── vector<Book*>
 └── vector<Member*>
```

The library manages the collections of books and members.

---

# 🛠️ Technologies

* **Language:** C++
* **Standard Library:** STL
* **Concepts:**

  * OOP
  * Encapsulation
  * Inheritance
  * Polymorphism
  * Association
  * Factory Pattern
  * Observer Pattern
  * STL containers

---

# ▶️ Example Usage

```cpp
Library library;

Book* book =
    new Book(
        101,
        "Clean Code",
        "Robert Martin"
    );

library.addBook(book);

Member* student =
    MemberFactory::createStudent(
        1,
        "Kumar"
    );

library.addMember(student);

library.issueBook(101, 1);
```

If another member wants to be notified:

```cpp
library.subscribe(101, 2);
```

When the book is returned:

```cpp
library.returnBook(101, 1);
```

the waiting member receives a notification.

---

# 📁 Suggested Project Structure

```text
LibraryManagement/
│
├── Book.h
├── Book.cpp
│
├── Member.h
├── Member.cpp
│
├── Student.h
├── Faculty.h
│
├── MemberFactory.h
├── MemberFactory.cpp
│
├── Library.h
├── Library.cpp
│
├── main.cpp
│
└── README.md
```

For interview practice, the entire implementation can also be kept in a single:

```text
main.cpp
```

---

# 🎯 Interview Explanation

If asked:

### "Explain your design."

You can say:

> "I modeled Book and Member as the main domain classes. A Member can have multiple borrowed books, and a Book maintains its availability. Library acts as the coordinator for adding books and members, issuing and returning books, searching, and subscriptions. I used the Factory Pattern to create Student and Faculty members. I used the Observer Pattern for notifying members when an unavailable book becomes available."

### "Why Factory?"

> "Because there are multiple member types such as Student and Faculty, so I centralized member creation inside MemberFactory."

### "Why Observer?"

> "Because multiple members may be waiting for an unavailable book. When the book becomes available, the Book can notify all interested members without the Library explicitly notifying each one."

### "Why no Borrow class?"

> "For this version, I don't need a separate Borrow entity because the requirement is simply to track which books a member currently has. Therefore, Member maintains a collection of Book pointers."

---

# 🚀 Possible Future Extensions

The current design intentionally keeps the requirements simple.

Possible extensions include:

```text
Library Management System
        │
        ├── Book Reservation
        ├── Due Dates
        ├── Fine Calculation
        ├── Book Categories
        ├── ISBN
        ├── Multiple Copies
        ├── Librarian
        ├── Email Notifications
        ├── SMS Notifications
        ├── Database Persistence
        └── Authentication
```

These should be added only when the requirements require them.

---

## 📌 Current Design Summary

```text
Classes:
    Book
    Member
    Student
    Faculty
    MemberFactory
    Library

Patterns:
    Factory
    Observer

Core Operations:
    addBook()
    addMember()
    searchBook()
    isAvailable()
    issueBook()
    returnBook()
    subscribe()

Main Relationship:
    Member ──── borrows ────► Book

Notification:
    Book ────► Member(s)
```
