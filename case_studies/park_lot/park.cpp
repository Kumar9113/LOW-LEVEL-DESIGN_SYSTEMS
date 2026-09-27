#include <bits/stdc++.h>
using namespace std;

// ================= VEHICLE =================

class Vehicle {
    string vehicleNo;
    string type;

public:
    Vehicle(string vehicleNo, string type) {
        this->vehicleNo = vehicleNo;
        this->type = type;
    }

    string getVehicleNo() {
        return vehicleNo;
    }

    string getType() {
        return type;
    }
};

class Bike : public Vehicle {
public:
    Bike(string vehicleNo)
        : Vehicle(vehicleNo, "BIKE") {}
};

class Car : public Vehicle {
public:
    Car(string vehicleNo)
        : Vehicle(vehicleNo, "CAR") {}
};

class Truck : public Vehicle {
public:
    Truck(string vehicleNo)
        : Vehicle(vehicleNo, "TRUCK") {}
};


// ================= PARKING SPOT =================

class ParkingSpot {
    int spotId;
    string type;
    Vehicle* vehicle;

public:
    ParkingSpot(int spotId, string type) {
        this->spotId = spotId;
        this->type = type;
        this->vehicle = nullptr;
    }

    int getSpotId() {
        return spotId;
    }

    string getType() {
        return type;
    }

    Vehicle* getVehicle() {
        return vehicle;
    }

    bool isAvailable() {
        return vehicle == nullptr;
    }

    bool canPark(Vehicle* vehicle) {
        return type == vehicle->getType();
    }

    void park(Vehicle* vehicle) {
        this->vehicle = vehicle;
    }

    void leave() {
        vehicle = nullptr;
    }
};


// ================= PARKING LOT =================

class ParkingLot {
    vector<ParkingSpot*> spots;

public:

    void addSpot(ParkingSpot* spot) {
        spots.push_back(spot);
    }

    bool parkVehicle(Vehicle* vehicle) {

        if (vehicle == nullptr)
            return false;

        for (auto spot : spots) {

            if (spot->isAvailable() &&
                spot->canPark(vehicle)) {

                spot->park(vehicle);

                cout << "Vehicle "
                     << vehicle->getVehicleNo()
                     << " parked at spot "
                     << spot->getSpotId()
                     << endl;

                return true;
            }
        }

        cout << "No suitable parking spot available\n";
        return false;
    }

    bool leaveVehicle(string vehicleNo) {

        for (auto spot : spots) {

            Vehicle* vehicle = spot->getVehicle();

            if (vehicle != nullptr &&
                vehicle->getVehicleNo() == vehicleNo) {

                spot->leave();

                cout << "Vehicle "
                     << vehicleNo
                     << " left spot "
                     << spot->getSpotId()
                     << endl;

                return true;
            }
        }

        cout << "Vehicle not found\n";
        return false;
    }
};


// ================= MAIN =================

int main() {

    // Create Parking Lot
    ParkingLot parkingLot;

    // Create Parking Spots
    ParkingSpot* bikeSpot1 = new ParkingSpot(1, "BIKE");
    ParkingSpot* bikeSpot2 = new ParkingSpot(2, "BIKE");

    ParkingSpot* carSpot1 = new ParkingSpot(3, "CAR");
    ParkingSpot* carSpot2 = new ParkingSpot(4, "CAR");

    ParkingSpot* truckSpot1 = new ParkingSpot(5, "TRUCK");


    // Add spots to Parking Lot
    parkingLot.addSpot(bikeSpot1);
    parkingLot.addSpot(bikeSpot2);

    parkingLot.addSpot(carSpot1);
    parkingLot.addSpot(carSpot2);

    parkingLot.addSpot(truckSpot1);


    // Create Vehicles
    Vehicle* bike1 = new Bike("TS01AB1234");
    Vehicle* bike2 = new Bike("TS01AB5678");

    Vehicle* car1 = new Car("TS09CD1111");
    Vehicle* car2 = new Car("TS09CD2222");

    Vehicle* truck1 = new Truck("TS10EF9999");


    // ================= PARK =================

    parkingLot.parkVehicle(bike1);
    parkingLot.parkVehicle(bike2);

    parkingLot.parkVehicle(car1);
    parkingLot.parkVehicle(car2);

    parkingLot.parkVehicle(truck1);


    // Try parking another car
    Vehicle* car3 = new Car("TS09CD3333");

    parkingLot.parkVehicle(car3);


    // ================= LEAVE =================

    parkingLot.leaveVehicle("TS09CD1111");

    // Now another car can use the freed spot
    parkingLot.parkVehicle(car3);


    // Vehicle doesn't exist
    parkingLot.leaveVehicle("TS99XX9999");

    return 0;
}