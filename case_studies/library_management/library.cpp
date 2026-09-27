#include <bits/stdc++.h>
using namespace std;

class Member;

// ============================================================
// BOOK
// ============================================================

class Book {

    int bookId;
    string title;
    string author;
    bool available;

    // Members waiting for this book
    vector<Member*> observers;

public:

    Book(int id, string title, string author) {

        this->bookId = id;
        this->title = title;
        this->author = author;
        this->available = true;
    }

    int getBookId() {
        return bookId;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    bool isAvailable() {
        return available;
    }

    void setAvailability(bool status) {
        available = status;
    }

    // Add member to notification list
    void addObserver(Member* member);

    // Notify waiting members
    void notifyObservers();
};


// ============================================================
// MEMBER
// ============================================================

class Member {

    int memberId;
    string name;

    // Books currently borrowed
    vector<Book*> books;

public:

    Member(int id, string name) {

        this->memberId = id;
        this->name = name;
    }

    int getMemberId() {
        return memberId;
    }

    string getName() {
        return name;
    }


    // --------------------------------------------------------
    // BORROW BOOK
    // --------------------------------------------------------

    void addBook(Book* book) {

        if (book == nullptr) {
            return;
        }

        books.push_back(book);
    }


    // --------------------------------------------------------
    // RETURN BOOK
    // --------------------------------------------------------

    bool removeBook(Book* book) {

        auto it = find(
            books.begin(),
            books.end(),
            book
        );

        if (it == books.end()) {
            return false;
        }

        books.erase(it);

        return true;
    }


    // --------------------------------------------------------
    // CHECK WHETHER MEMBER HAS BOOK
    // --------------------------------------------------------

    bool hasBook(Book* book) {

        return find(
            books.begin(),
            books.end(),
            book
        ) != books.end();
    }


    // --------------------------------------------------------
    // NOTIFICATION
    // --------------------------------------------------------

    void notify(Book* book) {

        cout << "Notification for "
             << name
             << ": \""
             << book->getTitle()
             << "\" is now available."
             << endl;
    }


    // --------------------------------------------------------
    // DISPLAY BORROWED BOOKS
    // --------------------------------------------------------

    void displayBooks() {

        cout << "\nBooks borrowed by "
             << name << ":\n";

        if (books.empty()) {

            cout << "No books borrowed.\n";
            return;
        }

        for (Book* book : books) {

            cout << "ID: "
                 << book->getBookId()
                 << " | Title: "
                 << book->getTitle()
                 << " | Author: "
                 << book->getAuthor()
                 << endl;
        }
    }
};


// ============================================================
// BOOK OBSERVER FUNCTIONS
// ============================================================

// Add member to waiting list
void Book::addObserver(Member* member) {

    if (member == nullptr) {
        return;
    }

    // Don't add duplicate member
    if (find(
            observers.begin(),
            observers.end(),
            member
        ) != observers.end()) {

        return;
    }

    observers.push_back(member);
}


// Notify all waiting members
void Book::notifyObservers() {

    for (Member* member : observers) {

        member->notify(this);
    }

    // One-time notification
    observers.clear();
}


// ============================================================
// STUDENT
// ============================================================

class Student : public Member {

public:

    Student(int id, string name)
        : Member(id, name) {
    }
};


// ============================================================
// FACULTY
// ============================================================

class Faculty : public Member {

public:

    Faculty(int id, string name)
        : Member(id, name) {
    }
};


// ============================================================
// MEMBER FACTORY
// ============================================================

class MemberFactory {

public:

    static Member* createStudent(
        int id,
        string name
    ) {

        return new Student(id, name);
    }

    static Member* createFaculty(
        int id,
        string name
    ) {

        return new Faculty(id, name);
    }
};


// ============================================================
// LIBRARY
// ============================================================

class Library {

    vector<Book*> books;
    vector<Member*> members;


    // --------------------------------------------------------
    // FIND BOOK
    // --------------------------------------------------------

    Book* findBook(int bookId) {

        for (Book* book : books) {

            if (book->getBookId() == bookId) {
                return book;
            }
        }

        return nullptr;
    }


    // --------------------------------------------------------
    // FIND MEMBER
    // --------------------------------------------------------

    Member* findMember(int memberId) {

        for (Member* member : members) {

            if (member->getMemberId() == memberId) {
                return member;
            }
        }

        return nullptr;
    }


public:

    // --------------------------------------------------------
    // ADD BOOK
    // --------------------------------------------------------

    void addBook(Book* book) {

        if (book == nullptr) {
            return;
        }

        books.push_back(book);
    }


    // --------------------------------------------------------
    // ADD MEMBER
    // --------------------------------------------------------

    void addMember(Member* member) {

        if (member == nullptr) {
            return;
        }

        members.push_back(member);
    }


    // --------------------------------------------------------
    // ISSUE BOOK
    // --------------------------------------------------------

    bool issueBook(
        int bookId,
        int memberId
    ) {

        Book* book = findBook(bookId);

        if (book == nullptr) {

            cout << "Book not found!\n";
            return false;
        }


        Member* member = findMember(memberId);

        if (member == nullptr) {

            cout << "Member not found!\n";
            return false;
        }


        if (!book->isAvailable()) {

            cout << "Book is already borrowed!\n";
            return false;
        }


        // Give book to member
        member->addBook(book);

        // Book becomes unavailable
        book->setAvailability(false);


        cout << "Book \""
             << book->getTitle()
             << "\" issued to "
             << member->getName()
             << endl;

        return true;
    }


    // --------------------------------------------------------
    // SUBSCRIBE FOR NOTIFICATION
    // --------------------------------------------------------

    bool subscribe(
        int bookId,
        int memberId
    ) {

        Book* book = findBook(bookId);

        if (book == nullptr) {

            cout << "Book not found!\n";
            return false;
        }


        Member* member = findMember(memberId);

        if (member == nullptr) {

            cout << "Member not found!\n";
            return false;
        }


        // If book is available,
        // member should borrow it instead.
        if (book->isAvailable()) {

            cout << "Book is available. "
                 << "You can borrow it directly.\n";

            return false;
        }


        // Add member to waiting list
        book->addObserver(member);


        cout << member->getName()
             << " will be notified when \""
             << book->getTitle()
             << "\" becomes available.\n";

        return true;
    }


    // --------------------------------------------------------
    // RETURN BOOK
    // --------------------------------------------------------

    bool returnBook(
        int bookId,
        int memberId
    ) {

        Book* book = findBook(bookId);

        if (book == nullptr) {

            cout << "Book not found!\n";
            return false;
        }


        Member* member = findMember(memberId);

        if (member == nullptr) {

            cout << "Member not found!\n";
            return false;
        }


        // Verify that this member actually has the book
        if (!member->hasBook(book)) {

            cout << "Member does not have this book!\n";
            return false;
        }


        // Remove book from member
        member->removeBook(book);


        // Make book available
        book->setAvailability(true);


        cout << "Book \""
             << book->getTitle()
             << "\" returned by "
             << member->getName()
             << endl;


        // Notify waiting members
        book->notifyObservers();


        return true;
    }
};


// ============================================================
// MAIN
// ============================================================

int main() {

    Library library;


    // --------------------------------------------------------
    // BOOKS
    // --------------------------------------------------------

    Book* book1 =
        new Book(
            101,
            "Clean Code",
            "Robert Martin"
        );

    Book* book2 =
        new Book(
            102,
            "Design Patterns",
            "Gang of Four"
        );


    library.addBook(book1);
    library.addBook(book2);


    // --------------------------------------------------------
    // MEMBERS
    // --------------------------------------------------------

    Member* kumar =
        MemberFactory::createStudent(
            1,
            "Kumar"
        );

    Member* ravi =
        MemberFactory::createFaculty(
            2,
            "Ravi"
        );


    library.addMember(kumar);
    library.addMember(ravi);


    // --------------------------------------------------------
    // KUMAR BORROWS BOOK
    // --------------------------------------------------------

    cout << "\n========== ISSUE ==========\n";

    library.issueBook(101, 1);


    // --------------------------------------------------------
    // RAVI WANTS SAME BOOK
    // --------------------------------------------------------

    cout << "\n========== SUBSCRIBE ==========\n";

    library.subscribe(101, 2);


    // --------------------------------------------------------
    // KUMAR RETURNS BOOK
    // --------------------------------------------------------

    cout << "\n========== RETURN ==========\n";

    library.returnBook(101, 1);


    // --------------------------------------------------------
    // MEMBER BOOKS
    // --------------------------------------------------------

    cout << "\n========== KUMAR'S BOOKS ==========\n";

    kumar->displayBooks();


    return 0;
}