#include <iostream>
using namespace std;

// Component
class Coffee {
public:
    virtual int cost() = 0;
    virtual void description() = 0;
    virtual ~Coffee() {}
};

// Concrete Component
class SimpleCoffee : public Coffee {
public:
    int cost() override {
        return 50;
    }

    void description() override {
        cout << "Simple Coffee";
    }
};

// Decorator
class CoffeeDecorator : public Coffee {
protected:
    Coffee& coffee;

public:
    CoffeeDecorator(Coffee& coffee) : coffee(coffee) {}
};

// Concrete Decorator
class Milk : public CoffeeDecorator {
public:
    Milk(Coffee& coffee) : CoffeeDecorator(coffee) {}

    int cost() override {
        return coffee.cost() + 10;
    }

    void description() override {
        coffee.description();
        cout << " + Milk";
    }
};

// Concrete Decorator
class Sugar : public CoffeeDecorator {
public:
    Sugar(Coffee& coffee) : CoffeeDecorator(coffee) {}

    int cost() override {
        return coffee.cost() + 5;
    }

    void description() override {
        coffee.description();
        cout << " + Sugar";
    }
};

int main() {

    SimpleCoffee coffee;

    Milk milk(coffee);

    Sugar sugar(milk);

    sugar.description();

    cout << endl;
     cout << "Cost: " << milk.cost() << endl;
    cout << "Cost: " << sugar.cost() << endl;

    return 0;
}