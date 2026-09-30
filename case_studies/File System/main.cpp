#include <bits/stdc++.h>
using namespace std;


class fileSystem {
protected:
    string name;

public:
    fileSystem(string name) {
        this->name = name;
    }

    virtual int getSize() = 0;
    virtual void ls(int level = 0) = 0;

    string getName() {
        return name;
    }

    virtual ~fileSystem() {}
};


// ================= FILE =================

class File : public fileSystem {
private:
    int size;

public:
    File(string name, int size)
        : fileSystem(name) {
        this->size = size;
    }

    int getSize() override {
        return size;
    }

    void ls(int level = 0) override {

        cout << string(level * 2, ' ')
             << name
             << " (" << size << " KB)"
             << endl;
    }
};


// ================= DIRECTORY =================

class Directory : public fileSystem {
private:
    vector<fileSystem*> v;

public:
    Directory(string name)
        : fileSystem(name) {
    }

    void add(fileSystem* item) {
        v.push_back(item);
    }

    int getSize() override {

        int total = 0;

        for(auto child : v) {
            total += child->getSize();
        }

        return total;
    }

    void ls(int level = 0) override {

        cout << string(level * 2, ' ')
             << name << "/"
             << endl;

        for(auto child : v) {
            child->ls(level + 1);
        }
    }

    bool remove(string target) {

        for(auto it = v.begin(); it != v.end(); it++) {

            if((*it)->getName() == target) {

                delete *it;
                v.erase(it);

                return true;
            }

            Directory* dir =
                dynamic_cast<Directory*>(*it);

            if(dir && dir->remove(target)) {
                return true;
            }
        }

        return false;
    }

    ~Directory() {

        for(auto child : v) {
            delete child;
        }
    }
};


// ================= FILE SYSTEM =================

class FileSystem {
private:
    Directory* root;

public:

    FileSystem() {
        root = new Directory("root");
    }

    Directory* getRoot() {
        return root;
    }

    void ls() {
        root->ls();
    }

    int getSize() {
        return root->getSize();
    }

    bool remove(string name) {

        if(name == "root")
            return false;

        return root->remove(name);
    }

    ~FileSystem() {
        delete root;
    }
};


// ================= MAIN =================

int main() {

    FileSystem fs;

    Directory* root = fs.getRoot();


    Directory* documents =
        new Directory("documents");

    documents->add(
        new File("resume.pdf", 100)
    );

    documents->add(
        new File("notes.txt", 50)
    );


    Directory* photos =
        new Directory("photos");

    photos->add(
        new File("photo.jpg", 200)
    );


    root->add(documents);
    root->add(photos);

    root->add(
        new File("readme.txt", 20)
    );


    cout << "FILE SYSTEM\n";

    fs.ls();


    cout << "\nTotal Size: "
         << fs.getSize()
         << " KB\n";


    cout << "\nDeleting notes.txt\n";

    fs.remove("notes.txt");


    cout << "\nFILE SYSTEM AFTER DELETE\n";

    fs.ls();

    return 0;
}