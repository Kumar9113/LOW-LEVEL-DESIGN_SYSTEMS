#include <bits/stdc++.h>
using namespace std;

// Receiver
class TV {
public:
    void turnOn() {
        cout << "TV ON" << endl;
    }

    void turnOff() {
        cout << "TV OFF" << endl;
    }
};

// Command
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// Concrete Command
class TurnOnCommand : public Command {
private:
    TV& tv;

public:
    TurnOnCommand(TV& tv) : tv(tv) {}

    void execute() override {
        tv.turnOn();
    }
};

// Concrete Command
class TurnOffCommand : public Command {
private:
    TV& tv;

public:
    TurnOffCommand(TV& tv) : tv(tv) {}

    void execute() override {
        tv.turnOff();
    }
};

// Invoker
class Remote {
private:
    Command& command;

public:
    Remote(Command& command) : command(command) {}

    void pressButton() {
        command.execute();
    }
};

int main() {

    TV tv;

    TurnOnCommand on(tv);
    Remote remote(on);

    remote.pressButton();

    TurnOffCommand off(tv);
    Remote remote2(off);

    remote2.pressButton();

    return 0;
}