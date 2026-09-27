#include <iostream>
using namespace std;

// Implementation
class Device {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setVolume(int volume) = 0;

    virtual ~Device() {}
};

// Concrete Implementation
class TV : public Device {
public:
    void turnOn() override {
        cout << "TV ON" << endl;
    }

    void turnOff() override {
        cout << "TV OFF" << endl;
    }

    void setVolume(int volume) override {
        cout << "TV Volume: " << volume << endl;
    }
};

// Concrete Implementation
class Radio : public Device {
public:
    void turnOn() override {
        cout << "Radio ON" << endl;
    }

    void turnOff() override {
        cout << "Radio OFF" << endl;
    }

    void setVolume(int volume) override {
        cout << "Radio Volume: " << volume << endl;
    }
};

// Abstraction
class Remote {
protected:
    Device& device;

public:
    Remote(Device& device) : device(device) {}

    virtual void power() = 0;

    virtual ~Remote() {}
};

// Refined Abstraction
class BasicRemote : public Remote {
private:
    bool on = false;

public:
    BasicRemote(Device& device) : Remote(device) {}

    void power() override {
        if (on) {
            device.turnOff();
            on = false;
        }
        else {
            device.turnOn();
            on = true;
        }
    }
};

int main() {

    TV tv;

    BasicRemote remote(tv);

    remote.power();
    remote.power();

    return 0;
}