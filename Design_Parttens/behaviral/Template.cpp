#include <iostream>
using namespace std;

// Abstract class
class Beverage {
public:

    // Template Method
    void makeBeverage() {

        boilWater();

        addIngredient();

        pourIntoCup();

        addExtra();
    }

    void boilWater() {
        cout << "Boiling water" << endl;
    }

    void pourIntoCup() {
        cout << "Pouring into cup" << endl;
    }

    virtual void addIngredient() = 0;
    virtual void addExtra() = 0;

    virtual ~Beverage() {}
};

// Concrete class
class Tea : public Beverage {
public:

    void addIngredient() override {
        cout << "Adding tea leaves" << endl;
    }

    void addExtra() override {
        cout << "Adding lemon" << endl;
    }
};

// Concrete class
class Coffee : public Beverage {
public:

    void addIngredient() override {
        cout << "Adding coffee powder" << endl;
    }

    void addExtra() override {
        cout << "Adding milk" << endl;
    }
};

int main() {

    Tea tea;
    tea.makeBeverage();

    cout << endl;

    Coffee coffee;
    coffee.makeBeverage();

    return 0;
}