#include <bits/stdc++.h>
using namespace std;


// ================= PRODUCT =================

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


// ================= VENDING MACHINE =================

class VendingMachine {

    vector<Product*> products;
    vector<int> quantity;

    double balance;

public:

    VendingMachine() {
        balance = 0;
    }

    void addProduct(Product* product, int qty) {

        products.push_back(product);
        quantity.push_back(qty);
    }


    void displayProducts() {

        cout << "\n===== PRODUCTS =====\n";

        for (int i = 0; i < products.size(); i++) {

            cout << products[i]->getId()
                 << ". "
                 << products[i]->getName()
                 << " - Rs."
                 << products[i]->getPrice()
                 << " - Stock: "
                 << quantity[i]
                 << endl;
        }
    }


    void insertMoney(double amount) {

        balance = balance + amount;

        cout << "Money inserted: Rs."
             << amount << endl;

        cout << "Balance: Rs."
             << balance << endl;
    }


    void selectProduct(int productId) {

        for (int i = 0; i < products.size(); i++) {

            if (products[i]->getId() == productId) {

                // Check stock
                if (quantity[i] == 0) {

                    cout << "Product is out of stock."
                         << endl;

                    return;
                }


                // Check money
                if (balance < products[i]->getPrice()) {

                    cout << "Insufficient money."
                         << endl;

                    cout << "Required: Rs."
                         << products[i]->getPrice()
                         << endl;

                    return;
                }


                // Dispense product
                quantity[i]--;

                double change =
                    balance - products[i]->getPrice();

                cout << "Product dispensed: "
                     << products[i]->getName()
                     << endl;

                cout << "Change: Rs."
                     << change
                     << endl;

                balance = 0;

                return;
            }
        }

        cout << "Product not found."
             << endl;
    }


    void cancel() {

        cout << "Refund: Rs."
             << balance
             << endl;

        balance = 0;
    }
};


// ================= MAIN =================

int main() {

    // Create products

    Product* coke =
        new Product(1, "Coke", 40);

    Product* pepsi =
        new Product(2, "Pepsi", 35);

    Product* chips =
        new Product(3, "Chips", 20);


    // Create vending machine

    VendingMachine machine;


    // Add products

    machine.addProduct(coke, 5);
    machine.addProduct(pepsi, 3);
    machine.addProduct(chips, 10);


    // Display products

    machine.displayProducts();


    // Buy Coke

    cout << "\n===== BUY COKE =====\n";

    machine.insertMoney(50);

    machine.selectProduct(1);


    // Cancel example

    cout << "\n===== CANCEL =====\n";

    machine.insertMoney(30);

    machine.cancel();


    return 0;
}