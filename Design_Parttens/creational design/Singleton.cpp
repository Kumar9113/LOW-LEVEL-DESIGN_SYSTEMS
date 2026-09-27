#include<bits/stdc++.h>
using namespace std;
class Singleton {
private:
    Singleton() {}  // private constructor

public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void show() {
        cout << "Singleton instance";
    }
};
int main() {
    Singleton& obj1 = Singleton::getInstance();
    Singleton& obj2 = Singleton::getInstance();

    cout << (&obj1 == &obj2);  // 1
}