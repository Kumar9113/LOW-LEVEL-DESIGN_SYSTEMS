# Vending Machine - Low Level Design

A simple **Vending Machine** implementation in C++ demonstrating **Object-Oriented Programming (OOP)** and the **State Design Pattern**.

## Features

The vending machine supports:

* Display available products
* Insert money
* Select a product
* Check product availability
* Check sufficient balance
* Dispense product
* Calculate and return change
* Cancel transaction and refund money
* Track product stock
* Handle different machine states

## Requirements

The machine supports the following basic flow:

```text
Start
  ↓
Display Products
  ↓
Insert Money
  ↓
Select Product
  ↓
Check Product
  ↓
Check Stock
  ↓
Check Balance
  ↓
Dispense Product
  ↓
Return Change
  ↓
Reset Machine
```

The project intentionally keeps the scope simple.

### Not Included

* UPI / online payments
* Credit/debit cards
* Payment gateway
* Database
* User accounts
* Multiple vending machines
* Billing system

---

# Class Design

```text
                    ┌──────────────────┐
                    │     Product      │
                    ├──────────────────┤
                    │ id               │
                    │ name             │
                    │ price            │
                    └──────────────────┘
                             ▲
                             │
                             │
                    ┌──────────────────┐
                    │    Inventory     │
                    ├──────────────────┤
                    │ products         │
                    │ quantity         │
                    ├──────────────────┤
                    │ addProduct()     │
                    │ getProduct()     │
                    │ isAvailable()    │
                    │ removeProduct()  │
                    └────────┬─────────┘
                             │
                             │
                    ┌────────▼─────────┐
                    │  VendingMachine  │
                    ├──────────────────┤
                    │ inventory        │
                    │ balance          │
                    │ selectedProduct  │
                    │ currentState     │
                    ├──────────────────┤
                    │ insertMoney()    │
                    │ selectProduct()  │
                    │ dispenseProduct()│
                    │ cancel()         │
                    └────────┬─────────┘
                             │
                             ▼
                       ┌───────────┐
                       │   State   │
                       └─────┬─────┘
                             │
              ┌──────────────┼──────────────┐
              ▼              ▼              ▼
       ┌────────────┐ ┌──────────────┐ ┌────────────────┐
       │ IdleState  │ │MoneyInserted │ │ProductSelected│
       │            │ │    State     │ │     State      │
       └────────────┘ └──────────────┘ └────────────────┘
```

---

# Classes

## 1. Product

Represents a product sold by the vending machine.

### Attributes

```text
id
name
price
```

### Responsibilities

* Store product information
* Provide product ID
* Provide product name
* Provide product price

---

## 2. Inventory

Responsible for managing products and their quantities.

### Responsibilities

```text
addProduct()
getProduct()
isAvailable()
removeProduct()
displayProducts()
```

Example:

```text
Coke    → Rs.40 → Stock: 5
Pepsi   → Rs.35 → Stock: 3
Chips   → Rs.20 → Stock: 10
```

The `VendingMachine` does not directly manage product quantities. That responsibility belongs to `Inventory`.

---

## 3. VendingMachine

The main class that coordinates the vending machine.

### Attributes

```text
Inventory*
State*
balance
selectedProduct
```

### Responsibilities

```text
insertMoney()
selectProduct()
dispenseProduct()
cancel()
```

The vending machine delegates these operations to the current `State`.

---

# State Design Pattern

The vending machine's behavior changes depending on its current state.

The states are:

```text
IdleState
MoneyInsertedState
ProductSelectedState
```

## State Flow

```text
              insertMoney()
       ┌────────────────────────┐
       │                        ▼
   ┌───────┐              ┌───────────────┐
   │ IDLE  │              │ MONEY INSERTED│
   └───┬───┘              └───────┬───────┘
       ▲                          │
       │                          │ selectProduct()
       │                          ▼
       │                  ┌─────────────────┐
       │                  │    PRODUCT      │
       │                  │    SELECTED     │
       │                  └────────┬────────┘
       │                           │
       │                           │ dispense
       └───────────────────────────┘
```

---

# State Responsibilities

## IdleState

Initial state of the machine.

```text
insertMoney()      → Accept money
selectProduct()    → Reject
dispenseProduct()  → Reject
cancel()           → Nothing to cancel
```

Example:

```text
User selects Coke without inserting money

↓

Please insert money first.
```

---

## MoneyInsertedState

Entered after the customer inserts money.

```text
insertMoney()      → Accept additional money
selectProduct()    → Select product
dispenseProduct()  → Reject
cancel()           → Refund money
```

Flow:

```text
Money Inserted
      ↓
Select Product
      ↓
Check Product
      ↓
Check Stock
      ↓
Product Selected
```

---

## ProductSelectedState

Entered after a valid product is selected.

```text
insertMoney()      → Accept additional money
selectProduct()    → Reject
dispenseProduct()  → Dispense product
cancel()           → Refund money
```

Dispensing flow:

```text
Product Selected
       ↓
Check Balance
       ↓
Remove Product
       ↓
Calculate Change
       ↓
Dispense Product
       ↓
Reset Transaction
       ↓
IDLE
```

---

# Complete Transaction Example

Suppose Coke costs Rs.40.

The customer inserts Rs.50.

```text
IDLE
  ↓
insertMoney(50)
  ↓
MONEY INSERTED
  ↓
selectProduct(1)
  ↓
PRODUCT SELECTED
  ↓
dispenseProduct()
  ↓
Coke dispensed
  ↓
Change = 50 - 40
  ↓
Change = Rs.10
  ↓
IDLE
```

Expected output:

```text
Money inserted: Rs.50
Balance: Rs.50
Product selected: Coke

Product dispensed: Coke
Change: Rs.10
```

---

# Cancel Transaction

The user can cancel after inserting money.

Example:

```text
IDLE
  ↓
insertMoney(30)
  ↓
MONEY INSERTED
  ↓
cancel()
  ↓
Refund: Rs.30
  ↓
IDLE
```

---

# State Pattern Benefits

Without the State Pattern, the vending machine could become a large collection of conditions:

```cpp
if (state == IDLE) {
    ...
}
else if (state == MONEY_INSERTED) {
    ...
}
else if (state == PRODUCT_SELECTED) {
    ...
}
```

With the State Pattern:

```text
VendingMachine
      ↓
Current State
      ↓
State handles operation
```

Each state decides what should happen for each operation.

This makes the behavior easier to organize and extend.

---

# OOP Concepts Used

### Encapsulation

Data such as:

```text
balance
selectedProduct
price
quantity
```

is kept inside classes.

### Abstraction

`State` defines the common operations:

```text
insertMoney()
selectProduct()
dispenseProduct()
cancel()
```

### Polymorphism

The vending machine stores:

```cpp
State* currentState;
```

and calls:

```cpp
currentState->insertMoney(...);
```

The actual behavior depends on whether the current state is:

```text
IdleState
MoneyInsertedState
ProductSelectedState
```

### Composition / Has-A Relationship

```text
VendingMachine
    ├── has an Inventory
    └── has a State
```

---

# Project Structure

```text
vending_machine/
│
├── machine.cpp
└── README.md
```

Compile:

```bash
g++ machine.cpp -o machine
```

Run:

```bash
./machine
```

---

# Key Interview Explanation

If asked **"Why did you use State Pattern?"**, explain:

> The vending machine behaves differently depending on its current state. For example, selecting a product is invalid in the Idle state, while dispensing is valid only after a product has been selected. The State Pattern moves these state-specific behaviors into separate classes instead of putting many condition checks inside VendingMachine.

### Main State Flow

```text
IDLE
  │
  │ insert money
  ▼
MONEY INSERTED
  │
  │ select product
  ▼
PRODUCT SELECTED
  │
  │ dispense
  ▼
IDLE
```

### Main Classes

```text
Product
Inventory
VendingMachine
State
 ├── IdleState
 ├── MoneyInsertedState
 └── ProductSelectedState
```

This project demonstrates a practical application of the **State Design Pattern** in a simple LLD problem.
