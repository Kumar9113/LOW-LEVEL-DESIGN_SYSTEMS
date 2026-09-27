#include <bits/stdc++.h>
using namespace std;


// ======================================================
// FORWARD DECLARATIONS
// ======================================================

class ATM;
class Card;
class State;

class IdleState;
class CardInsertedState;
class AuthenticatedState;


// ======================================================
// STATE CREATION FUNCTIONS
// ======================================================

State* createIdleState();
State* createCardInsertedState();
State* createAuthenticatedState();


// ======================================================
// CARD
// ======================================================

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


// ======================================================
// STATE INTERFACE
// ======================================================

class State {

public:

    virtual void insertCard(
        ATM* atm,
        Card* card
    ) = 0;

    virtual void enterPin(
        ATM* atm,
        int pin
    ) = 0;

    virtual void checkBalance(
        ATM* atm
    ) = 0;

    virtual void withdraw(
        ATM* atm,
        double amount
    ) = 0;

    virtual void deposit(
        ATM* atm,
        double amount
    ) = 0;

    virtual void ejectCard(
        ATM* atm
    ) = 0;

    virtual ~State() {}
};


// ======================================================
// ATM
// ======================================================

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


    // ================= CARD =================

    void setCard(Card* card) {

        this->card = card;
    }

    Card* getCard() {

        return card;
    }


    // ================= STATE =================

    void setState(State* state) {

        currentState = state;
    }


    // ================= BALANCE =================

    double getBalance() {

        return balance;
    }

    void addBalance(double amount) {

        balance = balance + amount;
    }

    void removeBalance(double amount) {

        balance = balance - amount;
    }


    // ================= OPERATIONS =================

    void insertCard(Card* card) {

        currentState->insertCard(this, card);
    }

    void enterPin(int pin) {

        currentState->enterPin(this, pin);
    }

    void checkBalance() {

        currentState->checkBalance(this);
    }

    void withdraw(double amount) {

        currentState->withdraw(this, amount);
    }

    void deposit(double amount) {

        currentState->deposit(this, amount);
    }

    void ejectCard() {

        currentState->ejectCard(this);
    }
};


// ======================================================
// IDLE STATE
// ======================================================

class IdleState : public State {

public:

    void insertCard(
        ATM* atm,
        Card* card
    ) override {

        cout << "Card inserted." << endl;

        atm->setCard(card);

        cout << "Please enter PIN." << endl;

        // IDLE -> CARD INSERTED

        atm->setState(
            createCardInsertedState()
        );
    }


    void enterPin(
        ATM* atm,
        int pin
    ) override {

        cout << "Please insert card first."
             << endl;
    }


    void checkBalance(
        ATM* atm
    ) override {

        cout << "Please insert card first."
             << endl;
    }


    void withdraw(
        ATM* atm,
        double amount
    ) override {

        cout << "Please insert card first."
             << endl;
    }


    void deposit(
        ATM* atm,
        double amount
    ) override {

        cout << "Please insert card first."
             << endl;
    }


    void ejectCard(
        ATM* atm
    ) override {

        cout << "No card inserted."
             << endl;
    }
};


// ======================================================
// CARD INSERTED STATE
// ======================================================

class CardInsertedState : public State {

public:

    void insertCard(
        ATM* atm,
        Card* card
    ) override {

        cout << "Card is already inserted."
             << endl;
    }


    void enterPin(
        ATM* atm,
        int pin
    ) override {

        Card* card =
            atm->getCard();


        if (card->getPin() == pin) {

            cout << "PIN verified."
                 << endl;

            cout << "Authentication successful."
                 << endl;


            // CARD INSERTED -> AUTHENTICATED

            atm->setState(
                createAuthenticatedState()
            );

        }
        else {

            cout << "Invalid PIN."
                 << endl;
        }
    }


    void checkBalance(
        ATM* atm
    ) override {

        cout << "Please enter PIN first."
             << endl;
    }


    void withdraw(
        ATM* atm,
        double amount
    ) override {

        cout << "Please enter PIN first."
             << endl;
    }


    void deposit(
        ATM* atm,
        double amount
    ) override {

        cout << "Please enter PIN first."
             << endl;
    }


    void ejectCard(
        ATM* atm
    ) override {

        cout << "Card ejected."
             << endl;

        atm->setCard(nullptr);

        // CARD INSERTED -> IDLE

        atm->setState(
            createIdleState()
        );
    }
};


// ======================================================
// AUTHENTICATED STATE
// ======================================================

class AuthenticatedState : public State {

public:

    void insertCard(
        ATM* atm,
        Card* card
    ) override {

        cout << "Card is already inserted."
             << endl;
    }


    void enterPin(
        ATM* atm,
        int pin
    ) override {

        cout << "Already authenticated."
             << endl;
    }


    void checkBalance(
        ATM* atm
    ) override {

        cout << "Current balance: Rs."
             << atm->getBalance()
             << endl;
    }


    void withdraw(
        ATM* atm,
        double amount
    ) override {

        if (amount <= 0) {

            cout << "Invalid amount."
                 << endl;

            return;
        }


        if (amount > atm->getBalance()) {

            cout << "Insufficient balance."
                 << endl;

            return;
        }


        atm->removeBalance(amount);


        cout << "Withdrawal successful."
             << endl;

        cout << "Amount withdrawn: Rs."
             << amount
             << endl;

        cout << "Remaining balance: Rs."
             << atm->getBalance()
             << endl;
    }


    void deposit(
        ATM* atm,
        double amount
    ) override {

        if (amount <= 0) {

            cout << "Invalid amount."
                 << endl;

            return;
        }


        atm->addBalance(amount);


        cout << "Deposit successful."
             << endl;

        cout << "Amount deposited: Rs."
             << amount
             << endl;

        cout << "Current balance: Rs."
             << atm->getBalance()
             << endl;
    }


    void ejectCard(
        ATM* atm
    ) override {

        cout << "Card ejected."
             << endl;

        atm->setCard(nullptr);


        // AUTHENTICATED -> IDLE

        atm->setState(
            createIdleState()
        );
    }
};


// ======================================================
// STATE CREATION FUNCTIONS
// ======================================================

State* createIdleState() {

    return new IdleState();
}


State* createCardInsertedState() {

    return new CardInsertedState();
}


State* createAuthenticatedState() {

    return new AuthenticatedState();
}


// ======================================================
// MAIN
// ======================================================

int main() {

    // Create card

    Card card(
        1001,
        1234
    );


    // Create ATM

    ATM atm(
        createIdleState()
    );


    // ==================================================
    // TRANSACTION 1
    // ==================================================

    cout << "\n===== TRANSACTION 1 =====\n";


    atm.insertCard(&card);

    atm.enterPin(1234);

    atm.checkBalance();

    atm.withdraw(2000);

    atm.checkBalance();

    atm.deposit(500);

    atm.checkBalance();

    atm.ejectCard();


    // ==================================================
    // TRANSACTION 2
    // ==================================================

    cout << "\n===== TRANSACTION 2 =====\n";


    atm.insertCard(&card);

    atm.enterPin(9999);

    atm.checkBalance();

    atm.ejectCard();


    // ==================================================
    // TRANSACTION 3
    // ==================================================

    cout << "\n===== TRANSACTION 3 =====\n";


    atm.insertCard(&card);

    atm.enterPin(1234);

    atm.withdraw(20000);

    atm.ejectCard();


    return 0;
}