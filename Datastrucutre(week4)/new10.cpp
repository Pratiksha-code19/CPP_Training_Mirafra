#include <iostream>
#include <stack>
#include <queue>
#include <ctime>
#include <iomanip>

using namespace std;

// Vehicle types
enum VehicleType { NORMAL, EMERGENCY };

// Vehicle structure to store information about the vehicle
struct Vehicle {
    string plateNumber;
    VehicleType type;
    time_t entryTime;

    // Constructor to initialize a new vehicle
    Vehicle(string plate, VehicleType t) : plateNumber(plate), type(t) {
        entryTime = time(0);  // Record the time the vehicle enters the parking
    }

    // Function to calculate the parking duration in hours
    double getParkingDuration() const {
        return difftime(time(0), entryTime) / 3600.0;
    }
};

// Comparison function for priority queue (emergency vehicles have higher priority)
struct VehicleComparator {
    bool operator()(const Vehicle& v1, const Vehicle& v2) {
        // Emergency vehicles have higher priority
        if (v1.type == EMERGENCY && v2.type == NORMAL) return true;
        if (v1.type == NORMAL && v2.type == EMERGENCY) return false;

        // If both are the same type, compare entry times (earliest enters first)
        return v1.entryTime > v2.entryTime;
    }
};

class ParkingLot {
private:
    stack<Vehicle> normalSlot;   // Stack for normal vehicles
    stack<Vehicle> emergencySlot; // Stack for emergency vehicles
   // queue<Vehicle> waitingQueue;  // Queue for waiting vehicles
    double totalRevenue;          // Total revenue from normal vehicles

public:
    // Constructor
    ParkingLot() : totalRevenue(0.0) {}

    // Function to enter the parking lot (based on vehicle type)
    void enterParking(Vehicle vehicle) {
        if (vehicle.type == EMERGENCY) {
            emergencySlot.push(vehicle);
            cout << "Emergency vehicle " << vehicle.plateNumber << " is waiting in the emergency slot." << endl;
        } else {
            normalSlot.push(vehicle);
            cout << "Normal vehicle " << vehicle.plateNumber << " is waiting in the normal slot." << endl;
        }
    }

    // Function to manage the parking of vehicles
    void parkVehicle() {
        if (!emergencySlot.empty()) {
            // Park the emergency vehicle first (if available)
            Vehicle vehicle = emergencySlot.top();
            emergencySlot.pop();
            double parkingDuration = vehicle.getParkingDuration();
            cout << vehicle.plateNumber << " parked. Duration: " << parkingDuration << " hours.";
            cout << " Fee: $" << (vehicle.type == NORMAL ? 10.0 * parkingDuration : 0.0) << endl;

            // Calculate the fee for normal vehicles and accumulate the revenue
            if (vehicle.type == NORMAL) {
                totalRevenue += 10.0 * parkingDuration;
            }
        } else if (!normalSlot.empty()) {
            // If no emergency vehicle, park the normal vehicle
            Vehicle vehicle = normalSlot.top();
            normalSlot.pop();
            double parkingDuration = vehicle.getParkingDuration();
            cout << vehicle.plateNumber << " parked. Duration: " << parkingDuration << " hours.";
            cout << " Fee: $" << (vehicle.type == NORMAL ? 10.0 * parkingDuration : 0.0) << endl;

            // Calculate the fee for normal vehicles and accumulate the revenue
            if (vehicle.type == NORMAL) {
                totalRevenue += 10.0 * parkingDuration;
            }
        } else {
            cout << "Parking lot is full. Vehicles are waiting..." << endl;
        }
    }

    // Function to handle vehicles exiting and calculate their fees
    void exitParking() {
        if (!emergencySlot.empty()) {
            // Emergency vehicle exits
            Vehicle vehicle = emergencySlot.top();
            emergencySlot.pop();
            double parkingDuration = vehicle.getParkingDuration();
            cout << vehicle.plateNumber << " exited. Duration: " << parkingDuration << " hours.";
            cout << " Fee: $" << (vehicle.type == NORMAL ? 10.0 * parkingDuration : 0.0) << endl;
        } else if (!normalSlot.empty()) {
            // Normal vehicle exits
            Vehicle vehicle = normalSlot.top();
            normalSlot.pop();
            double parkingDuration = vehicle.getParkingDuration();
            cout << vehicle.plateNumber << " exited. Duration: " << parkingDuration << " hours.";
            cout << " Fee: $" << (vehicle.type == NORMAL ? 10.0 * parkingDuration : 0.0) << endl;
        } else {
            cout << "No vehicles to exit." << endl;
        }
    }

    // Function to display the total revenue
    void displayRevenue() {
        cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
    }

    // Function to display parking status (slots and waiting queue)
    void displayStatus() {
        cout << "Normal Slot: " << normalSlot.size() << " vehicles." << endl;
        cout << "Emergency Slot: " << emergencySlot.size() << " vehicles." << endl;
       // cout << "Waiting Queue: " << waitingQueue.size() << " vehicles." << endl;
    }
};

// Main function
int main() {
    ParkingLot parking;  // Create the parking lot

    // Create some vehicles (emergency and normal)
    Vehicle v1("MH123", NORMAL);
    Vehicle v2("TS456", EMERGENCY);
    Vehicle v3("AP789", NORMAL);
    Vehicle v4("KA012", EMERGENCY);

    // Vehicles enter the parking lot
    parking.enterParking(v1);
    parking.enterParking(v2);
    parking.enterParking(v3);
    parking.enterParking(v4);

    // Display the current parking status
    parking.displayStatus();

    // Park vehicles based on priority
    parking.parkVehicle(); // First, emergency vehicle (TS456) will be parked
    parking.parkVehicle(); // Next, normal vehicle (MH123) will be parked
    parking.parkVehicle();
    parking.parkVehicle();

    // Display the status again
    parking.displayStatus();

    // Simulate vehicle exits
    parking.exitParking(); // First, emergency vehicle (DEF456) exits
    parking.exitParking(); // Then, normal vehicle (ABC123) exits

    // Display the revenue after some vehicles exit
    parking.displayRevenue();

    return 0;
}
