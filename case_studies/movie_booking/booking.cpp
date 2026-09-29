#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <mutex>

using namespace std;


// ================= USER =================

class User {
private:
    int id;
    string name;

public:
    User(int id, string name) {
        this->id = id;
        this->name = name;
    }

    string getName() {
        return name;
    }
};


// ================= MOVIE =================

class Movie {
private:
    int id;
    string name;
    string language;

public:
    Movie(int id, string name, string language) {
        this->id = id;
        this->name = name;
        this->language = language;
    }

    string getName() {
        return name;
    }
};


// ================= SEAT =================
// Seat contains only static information.
// Availability belongs to Show.

class Seat {
private:
    int id;
    string number;
    double price;

public:
    Seat(int id, string number, double price) {
        this->id = id;
        this->number = number;
        this->price = price;
    }

    int getId() {
        return id;
    }

    string getNumber() {
        return number;
    }

    double getPrice() {
        return price;
    }
};


// ================= SCREEN =================

class Screen {
private:
    int id;
    string name;

    vector<Seat*> seats;

public:
    Screen(int id, string name) {
        this->id = id;
        this->name = name;
    }

    void addSeat(Seat* seat) {
        seats.push_back(seat);
    }

    vector<Seat*>& getSeats() {
        return seats;
    }
};


// ================= SHOW =================

class Show {
private:
    int id;

    Movie* movie;
    Screen* screen;

    string startTime;

    // Availability is different for every show
    map<int, bool> seatAvailability;

    mutex mtx;

public:

    Show(int id,
         Movie* movie,
         Screen* screen,
         string startTime) {

        this->id = id;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        // Initially every seat is available
        for (Seat* seat : screen->getSeats()) {
            seatAvailability[seat->getId()] = true;
        }
    }


    string getMovieName() {
        return movie->getName();
    }


    string getStartTime() {
        return startTime;
    }


    // Get seat object from Screen

    Seat* getSeat(int seatId) {

        for (Seat* seat : screen->getSeats()) {

            if (seat->getId() == seatId) {
                return seat;
            }
        }

        return nullptr;
    }


    // ================= BOOK SEATS =================

    bool bookSeats(vector<int> seatIds) {

        lock_guard<mutex> lock(mtx);


        // ---------- CHECK ----------

        for (int seatId : seatIds) {

            if (seatAvailability.find(seatId)
                    == seatAvailability.end()) {

                return false;
            }

            if (!seatAvailability[seatId]) {

                return false;
            }
        }


        // ---------- BOOK ----------

        for (int seatId : seatIds) {
            seatAvailability[seatId] = false;
        }


        return true;
    }


    // ================= CANCEL SEATS =================

    void cancelSeats(vector<int> seatIds) {

        lock_guard<mutex> lock(mtx);

        for (int seatId : seatIds) {

            if (seatAvailability.find(seatId)
                    != seatAvailability.end()) {

                seatAvailability[seatId] = true;
            }
        }
    }
};


// ================= CINEMA =================

class Cinema {
private:
    int id;
    string name;

    vector<Screen*> screens;
    vector<Show*> shows;

public:

    Cinema(int id, string name) {
        this->id = id;
        this->name = name;
    }


    void addScreen(Screen* screen) {
        screens.push_back(screen);
    }


    void addShow(Show* show) {
        shows.push_back(show);
    }
};


// ================= BOOKING =================

class Booking {
private:
    int id;

    User* user;
    Show* show;

    vector<int> seatIds;

    double totalPrice;

    bool active;

public:

    Booking(int id,
            User* user,
            Show* show,
            vector<int> seatIds) {

        this->id = id;
        this->user = user;
        this->show = show;
        this->seatIds = seatIds;

        totalPrice = 0;

        // Calculate total price

        for (int seatId : seatIds) {

            Seat* seat = show->getSeat(seatId);

            if (seat != nullptr) {
                totalPrice += seat->getPrice();
            }
        }

        active = true;
    }


    // ================= CANCEL =================

    void cancel() {

        if (!active) {
            return;
        }

        show->cancelSeats(seatIds);

        active = false;

        cout << "Booking cancelled."
             << endl;
    }


    // ================= DISPLAY =================

    void showBooking() {

        cout << endl;

        cout << "Booking ID : "
             << id << endl;

        cout << "User       : "
             << user->getName() << endl;

        cout << "Movie      : "
             << show->getMovieName() << endl;

        cout << "Show Time  : "
             << show->getStartTime() << endl;


        cout << "Seats      : ";

        for (int seatId : seatIds) {

            Seat* seat = show->getSeat(seatId);

            if (seat != nullptr) {
                cout << seat->getNumber() << " ";
            }
        }

        cout << endl;


        cout << "Total Price: "
             << totalPrice << endl;


        cout << "Status     : ";

        if (active) {
            cout << "CONFIRMED";
        }
        else {
            cout << "CANCELLED";
        }

        cout << endl;
    }
};


// ================= BOOKING SYSTEM =================

class BookingSystem {
private:

    vector<Movie*> movies;
    vector<Cinema*> cinemas;
    vector<Booking*> bookings;

    int bookingCounter;

public:

    BookingSystem() {
        bookingCounter = 1;
    }


    void addMovie(Movie* movie) {
        movies.push_back(movie);
    }


    void addCinema(Cinema* cinema) {
        cinemas.push_back(cinema);
    }


    // ================= BOOK TICKETS =================

    Booking* bookTickets(User* user,
                          Show* show,
                          vector<int> seatIds) {


        // Show handles concurrency
        bool success =
            show->bookSeats(seatIds);


        if (!success) {

            cout << "Booking failed."
                 << " Seat already booked or invalid."
                 << endl;

            return nullptr;
        }


        // Create booking

        Booking* booking =
            new Booking(
                bookingCounter++,
                user,
                show,
                seatIds
            );


        bookings.push_back(booking);


        cout << "Booking successful."
             << endl;


        return booking;
    }
};


// ================= MAIN =================

int main() {

    // ---------- USERS ----------

    User ravi(1, "Ravi");

    User kumar(2, "Kumar");


    // ---------- MOVIE ----------

    Movie movie(
        101,
        "Avengers",
        "English"
    );


    // ---------- SCREEN ----------

    Screen screen(
        1,
        "Screen 1"
    );


    // ---------- SEATS ----------

    Seat a1(1, "A1", 200);

    Seat a2(2, "A2", 200);

    Seat a3(3, "A3", 200);

    Seat a4(4, "A4", 200);


    screen.addSeat(&a1);
    screen.addSeat(&a2);
    screen.addSeat(&a3);
    screen.addSeat(&a4);


    // ---------- SHOW 1 ----------

    Show show1(
        501,
        &movie,
        &screen,
        "7:00 PM"
    );


    // ---------- SHOW 2 ----------

    Show show2(
        502,
        &movie,
        &screen,
        "10:00 PM"
    );


    // ---------- CINEMA ----------

    Cinema cinema(
        1,
        "PVR Hyderabad"
    );

    cinema.addScreen(&screen);

    cinema.addShow(&show1);

    cinema.addShow(&show2);


    // ---------- BOOKING SYSTEM ----------

    BookingSystem system;

    system.addMovie(&movie);

    system.addCinema(&cinema);


    // ========================================
    // RAVI BOOKS A1 AND A2 FOR 7 PM SHOW
    // ========================================

    vector<int> seats1 = {
        1,
        2
    };


    Booking* booking1 =
        system.bookTickets(
            &ravi,
            &show1,
            seats1
        );


    if (booking1) {
        booking1->showBooking();
    }


    // ========================================
    // KUMAR TRIES A2 FOR SAME SHOW
    // ========================================

    vector<int> seats2 = {
        2
    };


    Booking* booking2 =
        system.bookTickets(
            &kumar,
            &show1,
            seats2
        );


    if (booking2) {
        booking2->showBooking();
    }


    // ========================================
    // KUMAR BOOKS A2 FOR 10 PM SHOW
    // ========================================

    Booking* booking3 =
        system.bookTickets(
            &kumar,
            &show2,
            seats2
        );


    if (booking3) {
        booking3->showBooking();
    }


    // ========================================
    // CANCEL RAVI'S BOOKING
    // ========================================

    if (booking1) {

        booking1->cancel();

    }


    // ========================================
    // KUMAR CAN NOW BOOK A1 FOR 7 PM
    // ========================================

    vector<int> seats3 = {
        1
    };


    Booking* booking4 =
        system.bookTickets(
            &kumar,
            &show1,
            seats3
        );


    if (booking4) {
        booking4->showBooking();
    }


    return 0;
}