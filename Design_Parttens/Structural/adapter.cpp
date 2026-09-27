#include <iostream>
using namespace std;

// Target interface
class PaymentProcessor {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentProcessor() {}
};

// Existing / Third-party class
class Razorpay {
public:
    void makePayment(int amount) {
        cout << "Razorpay payment: " << amount << endl;
    }
};

// Adapter
class RazorpayAdapter : public PaymentProcessor {
private:
    Razorpay razorpay;

public:
    void pay(int amount) override {
        razorpay.makePayment(amount);
    }
};

int main() {
    RazorpayAdapter adapter;

    adapter.pay(1000);

    return 0;
}