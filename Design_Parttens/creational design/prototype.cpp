#include <iostream>
using namespace std;


// Prototype
class Enemy {

private:
    int health;
    int speed;
    string weapon;

public:

    Enemy(int health, int speed, string weapon) {

        this->health = health;
        this->speed = speed;
        this->weapon = weapon;
    }


    // Clone method
    Enemy* clone() {

        return new Enemy(*this);
    }


    void show() {

        cout << "Health: " << health << endl;
        cout << "Speed: " << speed << endl;
        cout << "Weapon: " << weapon << endl;
        cout << endl;
    }
};


int main() {

    // Create original object
    Enemy* prototype =
        new Enemy(100, 20, "AK47");


    cout << "Original Enemy:" << endl;

    prototype->show();


    // Clone 1
    Enemy* enemy1 = prototype->clone();

    cout << "Cloned Enemy 1:" << endl;

    enemy1->show();


    // Clone 2
    Enemy* enemy2 = prototype->clone();

    cout << "Cloned Enemy 2:" << endl;

    enemy2->show();


    delete prototype;
    delete enemy1;
    delete enemy2;

    return 0;
}