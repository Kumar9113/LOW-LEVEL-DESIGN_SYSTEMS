#include <iostream>
#include <vector>
using namespace std;

// Iterator
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual string next() = 0;
    virtual ~Iterator() {}
};

// Collection
class StudentCollection {
private:
    vector<string> students;

public:
    void add(string student) {
        students.push_back(student);
    }

    vector<string>& getStudents() {
        return students;
    }
};

// Concrete Iterator
class StudentIterator : public Iterator {
private:
    vector<string>& students;
    int index = 0;

public:
    StudentIterator(vector<string>& students)
        : students(students) {}

    bool hasNext() override {
        return index < students.size();
    }

    string next() override {
        return students[index++];
    }
};

int main() {

    StudentCollection collection;

    collection.add("John");
    collection.add("Jane");
    collection.add("Bob");
    collection.add("Alice");

    StudentIterator iterator(collection.getStudents());

    while (iterator.hasNext()) {
        cout << iterator.next() << endl;
    }

    return 0;
}