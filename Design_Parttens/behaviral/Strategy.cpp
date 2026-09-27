#include <bits/stdc++.h>
using namespace std;

class Payement {
public:
    virtual void pay() = 0;
    virtual ~Payement() {}
};

class upiPayement : public Payement {
public:
    void pay() override {
        cout << "Paying with UPI" << endl;
    }
};

class cardPayement : public Payement {
public:
    void pay() override {
        cout << "Paying with Card" << endl;
    }
};

class paymentMethod {
    Payement* payment;

public:
    paymentMethod(Payement* payment) {
        this->payment = payment;
    }

    void makePayment() {
        payment->pay();
    }
};

int main() {

    upiPayement upi;
    cardPayement card;

    paymentMethod method1(&upi);
    method1.makePayment();

    paymentMethod method2(&card);
    method2.makePayment();

    return 0;
}