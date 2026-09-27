#include <iostream>
using namespace std;

// Product
class Computer {
public:
    string CPU;
    string RAM;
    string storage;
    string GPU;

    void show() {
        cout << "CPU: " << CPU << endl;
        cout << "RAM: " << RAM << endl;
        cout << "Storage: " << storage << endl;
        cout << "GPU: " << GPU << endl;
    }
};


// Builder
class ComputerBuilder {
private:
    Computer computer;

public:

    ComputerBuilder& setCPU(string cpu) {
        computer.CPU = cpu;
        return *this;
    }

    ComputerBuilder& setRAM(string ram) {
        computer.RAM = ram;
        return *this;
    }

    ComputerBuilder& setStorage(string storage) {
        computer.storage = storage;
        return *this;
    }

    ComputerBuilder& setGPU(string gpu) {
        computer.GPU = gpu;
        return *this;
    }

    Computer build() {
        return computer;
    }
};


int main() {

    // Create Builder object
    ComputerBuilder builder;

    // Build Computer step-by-step
    Computer computer = builder
                            .setCPU("Intel i7")
                            .setRAM("16GB")
                            .setStorage("1TB SSD")
                            .setGPU("RTX 4060")
                            .build();

    // Display Computer
    computer.show();

    return 0;
}