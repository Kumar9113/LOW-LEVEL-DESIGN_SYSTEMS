#include <bits/stdc++.h>
using namespace std;

// Observer
class Subscriber {
public:
    virtual void update(string video) = 0;
    virtual ~Subscriber() {}
};

// Concrete Observer
class User : public Subscriber {
private:
    string name;

public:
    User(string name) {
        this->name = name;
    }

    void update(string video) override {
        cout << name << " got notification: "
             << video << endl;
    }
};

// Subject
class Channel {
private:
    vector<Subscriber*> subscribers;

public:
    void subscribe(Subscriber* subscriber) {
        subscribers.push_back(subscriber);
    }

    void uploadVideo(string video) {

        cout << "New video: " << video << endl;

        for (auto subscriber : subscribers) {
            subscriber->update(video);
        }
    }
};

int main() {

    Channel channel;

    User user1("John");
    User user2("Jane");
    User user3("Bob");

    channel.subscribe(&user1);
    channel.subscribe(&user2);
    channel.subscribe(&user3);

    channel.uploadVideo("Design Patterns");

    return 0;
}