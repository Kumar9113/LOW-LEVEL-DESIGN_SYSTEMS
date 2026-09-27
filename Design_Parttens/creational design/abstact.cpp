#include <iostream>
using namespace std;

// Abstract Product
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

// Abstract Product
class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() {}
};


// Concrete Product
class WindowsButton : public Button {
public:
    void render() override {
        cout << "Windows Button" << endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        cout << "Windows Checkbox" << endl;
    }
};


// Concrete Product
class MacButton : public Button {
public:
    void render() override {
        cout << "Mac Button" << endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() override {
        cout << "Mac Checkbox" << endl;
    }
};


// Abstract Factory
class GUIFactory {
public:

    virtual Button* createButton() = 0;

    virtual Checkbox* createCheckbox() = 0;

    virtual ~GUIFactory() {}
};


// Concrete Factory
class WindowsFactory : public GUIFactory {
public:

    Button* createButton() override {
        return new WindowsButton();
    }

    Checkbox* createCheckbox() override {
        return new WindowsCheckbox();
    }
};


// Concrete Factory
class MacFactory : public GUIFactory {
public:

    Button* createButton() override {
        return new MacButton();
    }

    Checkbox* createCheckbox() override {
        return new MacCheckbox();
    }
};


int main() {

    // Select Windows family
    GUIFactory* factory = new WindowsFactory();

    Button* button = factory->createButton();
    Checkbox* checkbox = factory->createCheckbox();

    button->render();
    checkbox->render();

    delete button;
    delete checkbox;
    delete factory;

    return 0;
}