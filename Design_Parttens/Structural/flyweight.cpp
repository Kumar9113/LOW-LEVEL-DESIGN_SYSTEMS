#include <iostream>
#include <map>
using namespace std;

// Flyweight
class TreeType {
private:
    string name;
    string color;

public:
    TreeType(string name, string color) {
        this->name = name;
        this->color = color;
    }

    void draw(int x, int y) {
        cout << name << " tree at ("
             << x << ", " << y
             << ") Color: " << color << endl;
    }
};

// Flyweight Factory
class TreeFactory {
private:
    map<string, TreeType> treeTypes;

public:
    TreeType& getTreeType(string name, string color) {

        string key = name + color;

        if (treeTypes.find(key) == treeTypes.end()) {
            treeTypes.emplace(key, TreeType(name, color));
        }

        return treeTypes.at(key);
    }
};

int main() {

    TreeFactory factory;

    TreeType& oak1 = factory.getTreeType("Oak", "Green");
    TreeType& oak2 = factory.getTreeType("Oak", "Green");

    oak1.draw(10, 20);
    oak2.draw(50, 80);

    cout << (&oak1 == &oak2) << endl;

    return 0;
}