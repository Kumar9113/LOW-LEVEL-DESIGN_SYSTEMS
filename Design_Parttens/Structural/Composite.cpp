#include <iostream>
#include <vector>
using namespace std;

class show {
public:
    virtual void Display() = 0;
    virtual ~show() {}
};

class Employee : public show {
public:
    string name;

    Employee(string name) {
        this->name = name;
    }

    void Display() override {
        cout << "Employee Name: " << name << endl;
    }
};

class manager : public show {
public:
    string name;
    vector<show*> subordinates;

    manager(string name) {
        this->name = name;
    }

    void add(show* subordinate) {
        subordinates.push_back(subordinate);
    }

    void Display() override {
        cout << "Manager: " << name << endl;

        for (auto e : subordinates) {
            e->Display();
        }
    }
};

int main() {

    Employee emp1("John");
    Employee emp2("Jane");
    Employee emp3("Bob");

    manager mgr1("Manager 1");
    manager mgr2("Manager 2");
    manager mgr3("Manager 3");

    mgr1.add(&emp1);
    mgr2.add(&emp2);
    mgr3.add(&emp3);

    manager mgr4("Manager 4");

    mgr4.add(&mgr1);
    mgr4.add(&mgr2);
    mgr4.add(&mgr3);

    mgr1.Display();

    return 0;
}