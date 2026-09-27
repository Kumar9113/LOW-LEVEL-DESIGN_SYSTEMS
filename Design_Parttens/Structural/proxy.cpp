#include <iostream>
using namespace std;

// Subject
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// Real Subject
class RealImage : public Image {
private:
    string filename;

public:
    RealImage(string filename) {
        this->filename = filename;
        loadFromDisk();
    }

    void loadFromDisk() {
        cout << "Loading " << filename << endl;
    }

    void display() override {
        cout << "Displaying " << filename << endl;
    }
};

// Proxy
class ImageProxy : public Image {
private:
    string filename;
    RealImage* realImage = nullptr;

public:
    ImageProxy(string filename) {
        this->filename = filename;
    }

    void display() override {

        if (realImage == nullptr) {
            realImage = new RealImage(filename);
        }

        realImage->display();
    }
};

int main() {

    ImageProxy image("photo.jpg");

    cout << "Image object created" << endl;

    image.display();
    image.display();

    return 0;
}