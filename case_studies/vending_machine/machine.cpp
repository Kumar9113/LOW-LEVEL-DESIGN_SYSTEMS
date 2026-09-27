#include <bits/stdc++.h>
using namespace std;


// ======================================================
// FORWARD DECLARATIONS
// ======================================================

class VendingMachine;
class State;

class IdleState;
class MoneyInsertedState;
class ProductSelectedState;


// ======================================================
// STATE FACTORY FUNCTIONS
// ======================================================

State* createIdleState();
State* createMoneyInsertedState();
State* createProductSelectedState();


// ======================================================
// PRODUCT
// ======================================================

class Product {

    int id;
    string name;
    double price;

public:

    Product(int id, string name, double price) {

        this->id = id;
        this->name = name;
        this->price = price;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }
};


// ======================================================
// INVENTORY
// ======================================================

class Inventory {

    map<int, pair<Product*, int>> products;

public:

    void addProduct(Product* product, int quantity) {

        products[product->getId()] =
            {product, quantity};
    }


    Product* getProduct(int productId) {

        if (products.find(productId) == products.end()) {
            return nullptr;
        }

        return products[productId].first;
    }


    bool isAvailable(int productId) {

        if (products.find(productId) == products.end()) {
            return false;
        }

        return products[productId].second > 0;
    }


    void removeProduct(int productId) {

        if (!isAvailable(productId)) {
            return;
        }

        products[productId].second--;
    }


    void displayProducts() {

        cout << "\n===== PRODUCTS =====\n";

        for (auto item : products) {

            Product* product = item.second.first;
            int quantity = item.second.second;

            cout << product->getId()
                 << ". "
                 << product->getName()
                 << " - Rs."
                 << product->getPrice()
                 << " - Stock: "
                 << quantity
                 << endl;
        }
    }
};


// ======================================================
// STATE INTERFACE
// ======================================================

class State {

public:

    virtual void insertMoney(
        VendingMachine* machine,
        double amount
    ) = 0;


    virtual void selectProduct(
        VendingMachine* machine,
        int productId
    ) = 0;


    virtual void dispenseProduct(
        VendingMachine* machine
    ) = 0;


    virtual void cancel(
        VendingMachine* machine
    ) = 0;


    virtual ~State() {}
};


// ======================================================
// VENDING MACHINE
// ======================================================

class VendingMachine {

    Inventory* inventory;

    State* currentState;

    double balance;

    Product* selectedProduct;

public:

    VendingMachine(Inventory* inventory) {

        this->inventory = inventory;

        balance = 0;

        selectedProduct = nullptr;

        currentState = createIdleState();
    }


    // ==================================================
    // STATE
    // ==================================================

    void setState(State* state) {

        currentState = state;
    }


    // ==================================================
    // BALANCE
    // ==================================================

    void addBalance(double amount) {

        balance = balance + amount;
    }


    double getBalance() {

        return balance;
    }


    void resetBalance() {

        balance = 0;
    }


    // ==================================================
    // INVENTORY
    // ==================================================

    Inventory* getInventory() {

        return inventory;
    }


    // ==================================================
    // SELECTED PRODUCT
    // ==================================================

    void setSelectedProduct(Product* product) {

        selectedProduct = product;
    }


    Product* getSelectedProduct() {

        return selectedProduct;
    }


    void resetSelectedProduct() {

        selectedProduct = nullptr;
    }


    // ==================================================
    // CUSTOMER OPERATIONS
    // ==================================================

    void insertMoney(double amount) {

        currentState->insertMoney(this, amount);
    }


    void selectProduct(int productId) {

        currentState->selectProduct(this, productId);
    }


    void dispenseProduct() {

        currentState->dispenseProduct(this);
    }


    void cancel() {

        currentState->cancel(this);
    }


    void displayProducts() {

        inventory->displayProducts();
    }
};


// ======================================================
// IDLE STATE
// ======================================================

class IdleState : public State {

public:

    void insertMoney(
        VendingMachine* machine,
        double amount
    ) override {

        if (amount <= 0) {

            cout << "Invalid amount."
                 << endl;

            return;
        }


        machine->addBalance(amount);


        cout << "Money inserted: Rs."
             << amount
             << endl;


        cout << "Balance: Rs."
             << machine->getBalance()
             << endl;


        // IDLE -> MONEY INSERTED

        machine->setState(
            createMoneyInsertedState()
        );
    }


    void selectProduct(
        VendingMachine* machine,
        int productId
    ) override {

        cout << "Please insert money first."
             << endl;
    }


    void dispenseProduct(
        VendingMachine* machine
    ) override {

        cout << "Please insert money first."
             << endl;
    }


    void cancel(
        VendingMachine* machine
    ) override {

        cout << "Nothing to cancel."
             << endl;
    }
};


// ======================================================
// MONEY INSERTED STATE
// ======================================================

class MoneyInsertedState : public State {

public:

    void insertMoney(
        VendingMachine* machine,
        double amount
    ) override {

        if (amount <= 0) {

            cout << "Invalid amount."
                 << endl;

            return;
        }


        // Add more money

        machine->addBalance(amount);


        cout << "Money added: Rs."
             << amount
             << endl;


        cout << "Balance: Rs."
             << machine->getBalance()
             << endl;
    }


    void selectProduct(
        VendingMachine* machine,
        int productId
    ) override {

        // Find product

        Product* product =
            machine->getInventory()
                   ->getProduct(productId);


        if (product == nullptr) {

            cout << "Product not found."
                 << endl;

            return;
        }


        // Check stock

        if (!machine->getInventory()
                    ->isAvailable(productId)) {

            cout << "Product is out of stock."
                 << endl;

            return;
        }


        // Check money

        if (machine->getBalance()
                < product->getPrice()) {

            cout << "Insufficient money."
                 << endl;

            cout << "Required: Rs."
                 << product->getPrice()
                 << endl;

            return;
        }


        // Store selected product

        machine->setSelectedProduct(product);


        cout << "Product selected: "
             << product->getName()
             << endl;


        // MONEY INSERTED -> PRODUCT SELECTED

        machine->setState(
            createProductSelectedState()
        );
    }


    void dispenseProduct(
        VendingMachine* machine
    ) override {

        cout << "Please select a product first."
             << endl;
    }


    void cancel(
        VendingMachine* machine
    ) override {

        cout << "Transaction cancelled."
             << endl;


        cout << "Refund: Rs."
             << machine->getBalance()
             << endl;


        machine->resetBalance();


        // MONEY INSERTED -> IDLE

        machine->setState(
            createIdleState()
        );
    }
};


// ======================================================
// PRODUCT SELECTED STATE
// ======================================================

class ProductSelectedState : public State {

public:

    void insertMoney(
        VendingMachine* machine,
        double amount
    ) override {

        if (amount <= 0) {

            cout << "Invalid amount."
                 << endl;

            return;
        }


        // User can add more money

        machine->addBalance(amount);


        cout << "Money added: Rs."
             << amount
             << endl;


        cout << "Balance: Rs."
             << machine->getBalance()
             << endl;
    }


    void selectProduct(
        VendingMachine* machine,
        int productId
    ) override {

        cout << "A product is already selected."
             << endl;
    }


    void dispenseProduct(
        VendingMachine* machine
    ) override {

        Product* product =
            machine->getSelectedProduct();


        if (product == nullptr) {

            cout << "No product selected."
                 << endl;

            return;
        }


        double price =
            product->getPrice();


        double balance =
            machine->getBalance();


        // Check money

        if (balance < price) {

            cout << "Insufficient money."
                 << endl;

            cout << "Required: Rs."
                 << price
                 << endl;

            cout << "Current balance: Rs."
                 << balance
                 << endl;

            return;
        }


        // Remove product from inventory

        machine->getInventory()
               ->removeProduct(
                   product->getId()
               );


        // Calculate change

        double change =
            balance - price;


        cout << "\nProduct dispensed: "
             << product->getName()
             << endl;


        cout << "Price: Rs."
             << price
             << endl;


        cout << "Change: Rs."
             << change
             << endl;


        // Finish transaction

        machine->resetBalance();

        machine->resetSelectedProduct();


        // PRODUCT SELECTED -> IDLE

        machine->setState(
            createIdleState()
        );
    }


    void cancel(
        VendingMachine* machine
    ) override {

        cout << "Transaction cancelled."
             << endl;


        cout << "Refund: Rs."
             << machine->getBalance()
             << endl;


        machine->resetBalance();

        machine->resetSelectedProduct();


        // PRODUCT SELECTED -> IDLE

        machine->setState(
            createIdleState()
        );
    }
};


// ======================================================
// STATE FACTORIES
// ======================================================

State* createIdleState() {

    return new IdleState();
}


State* createMoneyInsertedState() {

    return new MoneyInsertedState();
}


State* createProductSelectedState() {

    return new ProductSelectedState();
}


// ======================================================
// MAIN
// ======================================================

int main() {

    // Create products

    Product* coke =
        new Product(1, "Coke", 40);

    Product* pepsi =
        new Product(2, "Pepsi", 35);

    Product* chips =
        new Product(3, "Chips", 20);


    // Create inventory

    Inventory inventory;

    inventory.addProduct(coke, 5);

    inventory.addProduct(pepsi, 3);

    inventory.addProduct(chips, 10);


    // Create vending machine

    VendingMachine machine(&inventory);


    // Display products

    machine.displayProducts();


    // ==================================================
    // TRANSACTION 1
    // ==================================================

    cout << "\n===== BUY COKE =====\n";

    machine.insertMoney(50);

    machine.selectProduct(1);

    machine.dispenseProduct();


    // ==================================================
    // TRANSACTION 2
    // ==================================================

    cout << "\n===== CANCEL =====\n";

    machine.insertMoney(30);

    machine.cancel();


    return 0;
}