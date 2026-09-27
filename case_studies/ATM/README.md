# 🏧 ATM Machine – Low-Level Design

A simple **ATM Machine Low-Level Design (LLD)** implemented in **C++**, using **Object-Oriented Programming (OOP)** and the **State Design Pattern**.

The goal of this project is to understand how an ATM can change its behavior depending on its current state.

---

## 📌 Features

The ATM supports:

1. Insert Card
2. Enter PIN
3. Authenticate Card
4. Check Balance
5. Withdraw Cash
6. Deposit Cash
7. Eject Card

### Out of Scope

This version intentionally does not include:

* Bank server
* Database
* Multiple accounts
* Network communication
* Receipt printing
* Transaction history
* Cash denomination management
* Payment gateway

The focus is on **LLD and the State Design Pattern**.

---

# 🏗️ Class Design

```text
                    ┌──────────────────┐
                    │      Card        │
                    ├──────────────────┤
                    │ accountNo        │
                    │ pin              │
                    ├──────────────────┤
                    │ getAccountNo()   │
                    │ getPin()         │
                    └────────┬─────────┘
                             │
                             │
                    ┌────────▼─────────┐
                    │       ATM        │
                    ├──────────────────┤
                    │ Card* card       │
                    │ State* state     │
                    │ balance          │
                    ├──────────────────┤
                    │ setCard()        │
                    │ getCard()        │
                    │ setState()       │
                    │ getBalance()     │
                    │ setBalance()     │
                    └────────┬─────────┘
                             │
                             │ uses
                             ▼
                    ┌──────────────────┐
                    │      State       │
                    ├──────────────────┤
                    │ insertCard()     │
                    │ enterPin()       │
                    │ checkBalance()   │
                    │ withdraw()       │
                    │ deposit()        │
                    │ ejectCard()      │
                    └────────┬─────────┘
                             │
              ┌──────────────┼──────────────┐
              │              │              │
              ▼              ▼              ▼
       ┌────────────┐ ┌───────────────┐ ┌─────────────────┐
       │ IdleState  │ │CardInserted   │ │Authenticated    │
       │            │ │    State      │ │     State       │
       └────────────┘ └───────────────┘ └─────────────────┘
```

---

# 🧩 Components

## 1. Card

The `Card` class stores the information associated with the ATM card.

```cpp
class Card {
    int accountNo;
    int pin;

public:
    Card(int accountNo, int pin) {
        this->accountNo = accountNo;
        this->pin = pin;
    }

    int getAccountNo() {
        return accountNo;
    }

    int getPin() {
        return pin;
    }
};
```

### Responsibility

* Store account number
* Store PIN
* Provide card information

---

# 2. State

`State` is the interface for all ATM states.

```cpp
class State {
public:
    virtual void insertCard(ATM* atm, Card* card) = 0;
    virtual void enterPin(ATM* atm, int pin) = 0;
    virtual void checkBalance(ATM* atm) = 0;
    virtual void withdraw(ATM* atm, double amount) = 0;
    virtual void deposit(ATM* atm, double amount) = 0;
    virtual void ejectCard(ATM* atm) = 0;

    virtual ~State() {}
};
```

Instead of putting all ATM behavior inside one huge `ATM` class, the behavior is distributed among different states.

---

# 3. ATM

The `ATM` class is the main controller.

It maintains:

```text
ATM
 ├── Card*
 ├── State*
 └── Balance
```

### Responsibilities

* Store the currently inserted card
* Store the current ATM state
* Maintain balance
* Delegate operations to the current state
* Change from one state to another

Example:

```cpp
class ATM {
    Card* card;
    State* currentState;
    double balance;

public:
    ATM(State* state) {
        card = nullptr;
        currentState = state;
        balance = 10000;
    }

    void setCard(Card* card) {
        this->card = card;
    }

    Card* getCard() {
        return card;
    }

    void setState(State* state) {
        currentState = state;
    }

    State* getState() {
        return currentState;
    }
};
```

---

# 🔄 State Pattern

The ATM behaves differently depending on its current state.

There are three states:

```text
                ┌─────────────┐
                │  IdleState  │
                └──────┬──────┘
                       │
                  insertCard()
                       │
                       ▼
             ┌────────────────────┐
             │ CardInsertedState  │
             └─────────┬──────────┘
                       │
                    enterPin()
                       │
                       ▼
             ┌────────────────────┐
             │ AuthenticatedState │
             └─────────┬──────────┘
                       │
                 ejectCard()
                       │
                       ▼
                ┌─────────────┐
                │  IdleState  │
                └─────────────┘
```

---

# 🟢 1. IdleState

This is the initial state.

The ATM is waiting for a card.

### Allowed operation

```text
insertCard()
```

When a card is inserted:

```text
IdleState
   ↓
Store Card
   ↓
Change State
   ↓
CardInsertedState
```

---

# 🟡 2. CardInsertedState

The card has been inserted, but the user has not authenticated yet.

### Allowed operation

```text
enterPin()
ejectCard()
```

The entered PIN is compared with the PIN stored in the card.

```text
Entered PIN
     ↓
Compare with Card PIN
     ↓
 ┌───────────────┐
 │ Correct PIN ? │
 └───────┬───────┘
       Yes
        ↓
AuthenticatedState
```

If the PIN is incorrect, authentication fails.

---

# 🔵 3. AuthenticatedState

The user has successfully authenticated.

The ATM now allows:

```text
checkBalance()
withdraw()
deposit()
ejectCard()
```

After the card is ejected:

```text
AuthenticatedState
        ↓
    ejectCard()
        ↓
   Remove Card
        ↓
    IdleState
```

---

# 🔁 Complete State Flow

```text
                    ATM START
                        │
                        ▼
                  ┌───────────┐
                  │   IDLE    │
                  └─────┬─────┘
                        │
                   Insert Card
                        │
                        ▼
             ┌────────────────────┐
             │   CARD INSERTED    │
             └─────────┬──────────┘
                       │
                    Enter PIN
                       │
                  ┌────▼─────┐
                  │ PIN Valid?│
                  └────┬─────┘
                       │
                      Yes
                       │
                       ▼
             ┌────────────────────┐
             │   AUTHENTICATED    │
             └─────────┬──────────┘
                       │
          ┌────────────┼─────────────┐
          │            │             │
          ▼            ▼             ▼
    Check Balance   Withdraw      Deposit
          │            │             │
          └────────────┴─────────────┘
                       │
                   Eject Card
                       │
                       ▼
                  ┌───────────┐
                  │   IDLE    │
                  └───────────┘
```

---

# 🏭 State Factory Functions

The project uses small factory functions to create state objects.

```cpp
State* createIdleState();
State* createCardInsertedState();
State* createAuthenticatedState();
```

After all state classes are defined:

```cpp
State* createIdleState() {
    return new IdleState();
}

State* createCardInsertedState() {
    return new CardInsertedState();
}

State* createAuthenticatedState() {
    return new AuthenticatedState();
}
```

This also helps avoid incomplete-type problems when states need to create other states.

---

# 🧱 Object Creation Flow

The main components are created in this order:

```text
             main()
                │
                ▼
       ┌─────────────────┐
       │ Create Card     │
       └────────┬────────┘
                │
                ▼
       ┌─────────────────┐
       │ Create State    │
       │   IdleState     │
       └────────┬────────┘
                │
                ▼
       ┌─────────────────┐
       │ Create ATM      │
       └────────┬────────┘
                │
                ▼
       ATM stores State*
                │
                ▼
       User inserts Card
                │
                ▼
       ATM stores Card*
```

### Important distinction

| Component            | Responsibility                 |
| -------------------- | ------------------------------ |
| `Card`               | Stores card data               |
| `ATM`                | Main controller                |
| `State`              | Defines ATM behavior           |
| `IdleState`          | Handles idle behavior          |
| `CardInsertedState`  | Handles inserted-card behavior |
| `AuthenticatedState` | Handles authenticated behavior |

---

# 💡 Why State Pattern?

Without State Pattern, we might write:

```cpp
if (state == "IDLE") {
    ...
}
else if (state == "CARD_INSERTED") {
    ...
}
else if (state == "AUTHENTICATED") {
    ...
}
```

As the ATM grows, this can become difficult to maintain.

With State Pattern:

```text
ATM
 │
 └── Current State
       │
       ├── IdleState
       ├── CardInsertedState
       └── AuthenticatedState
```

Each state controls its own behavior.

### Main benefit

> **The object's behavior changes automatically when its state changes.**

---

# 🧠 OOP Concepts Used

### 1. Encapsulation

Data is kept inside classes:

```cpp
class Card {
    int accountNo;
    int pin;
};
```

---

### 2. Abstraction

`State` provides common operations:

```cpp
virtual void insertCard(...) = 0;
virtual void enterPin(...) = 0;
```

---

### 3. Inheritance

Concrete states inherit from `State`:

```text
State
 ├── IdleState
 ├── CardInsertedState
 └── AuthenticatedState
```

---

### 4. Polymorphism

ATM stores:

```cpp
State* currentState;
```

The pointer can refer to:

```text
IdleState
CardInsertedState
AuthenticatedState
```

So the same operation can behave differently depending on the current state.

---

# 📁 Project Structure

```text
atm/
│
├── atm.cpp
└── README.md
```

---

# ▶️ Compile and Run

### Compile

```bash
g++ atm.cpp -o atm
```

### Run

```bash
./atm
```

---

# 🎯 Interview Explanation

If asked:

### "Why did you use State Pattern?"

You can answer:

> An ATM behaves differently depending on its current state. For example, we cannot withdraw money before authentication. Instead of writing many condition checks inside the ATM class, I used the State Pattern where each state handles its own behavior. The ATM maintains a pointer to the current state and changes that state when an operation occurs.

### "What is the role of ATM?"

> ATM acts as the main context/controller. It stores the current card, current state, and balance, while delegating operations to the current state.

### "What is the role of Card?"

> Card is a data object that stores information such as account number and PIN.

### "What are the states?"

> The ATM has three states: IdleState, CardInsertedState, and AuthenticatedState.

---

# 📌 Key Takeaway

```text
Card  → Data
ATM   → Controller / Context
State → Behavior
```

The central idea is:

```text
             ATM
              │
              ▼
        Current State
              │
      ┌───────┼────────┐
      ▼       ▼        ▼
    Idle   Card In   Authenticated
```

The ATM changes its behavior by changing its current state.
