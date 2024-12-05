#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
#include <chrono>
#include<unistd.h>

using namespace std;

// Vehicle Types
enum VehicleType { NORMAL, EMERGENCY };

// Vehicle class
class Vehicle {
public:
    string licensePlate;
    VehicleType type;
    time_t entryTime;

    Vehicle(string plate, VehicleType t) : licensePlate(plate), type(t) {
        entryTime = time(0); // Record entry time
    }

    double getParkingDuration() {
        return difftime(time(0), entryTime) ; // Returns hours
    }
};

// Parking System class
class ParkingSystem {
private:
    stack<Vehicle*> parkingSlot;
    queue<Vehicle*> normalQueue;
    priority_queue<Vehicle*> emergencyQueue;
    double totalRevenue;

public:
    ParkingSystem() : totalRevenue(0) {}

    // Function to calculate parking fee
    double calculateFee(Vehicle* vehicle) {
        if (vehicle->type == NORMAL) {
            return 10 * vehicle->getParkingDuration(); // $10/hour for normal vehicles
        }
        return 0; // Emergency vehicles are free
    }

    // Function to park a normal vehicle
    void parkNormalVehicle(Vehicle* vehicle) {
        normalQueue.push(vehicle);
    }

    // Function to park an emergency vehicle
    void parkEmergencyVehicle(Vehicle* vehicle) {
        emergencyQueue.push(vehicle);
    }

    // Function to park vehicles into the parking slot
    void allocateParkingSlot() {
        if (!emergencyQueue.empty()) {
            Vehicle* vehicle = emergencyQueue.top(); // Get the highest priority emergency vehicle
            emergencyQueue.pop();
            parkingSlot.push(vehicle);
            cout << "Emergency vehicle " << vehicle->licensePlate << " parked." << endl;
        }

        if (!normalQueue.empty()) {
            Vehicle* vehicle = normalQueue.front(); // Get the first normal vehicle
            normalQueue.pop();
            parkingSlot.push(vehicle);
            cout << "Normal vehicle " << vehicle->licensePlate << " parked." << endl;
        }
    }

    // Function to process a vehicle exiting the parking slot
    void vehicleExit() {
        if (!parkingSlot.empty()) {
            Vehicle* vehicle = parkingSlot.top();
            parkingSlot.pop();
            double fee = calculateFee(vehicle);
            totalRevenue += fee;
            cout << "Vehicle " << vehicle->licensePlate << " exited. Fee: $" << fee << endl;
            delete vehicle; // Free the memory of the vehicle
        } else {
            cout << "No vehicles to exit." << endl;
        }
    }

    // Function to get total revenue
    double getTotalRevenue() {
        return totalRevenue;
    }

    // Function to show the current status of the system
    void showStatus() {
        cout << "Total revenue: $" << totalRevenue << endl;
        cout << "Emergency Vehicles in queue: " << emergencyQueue.size() << endl;
        cout << "Normal Vehicles in queue: " << normalQueue.size() << endl;
        cout << "Vehicles in parking slot: " << parkingSlot.size() << endl;
    }
};

int main() {
    ParkingSystem parking;

    // Example: Add vehicles
    parking.parkNormalVehicle(new Vehicle("MH123", NORMAL));
    parking.parkNormalVehicle(new Vehicle("TS456", NORMAL));
    parking.parkEmergencyVehicle(new Vehicle("KA001", EMERGENCY));
    parking.parkNormalVehicle(new Vehicle("AP789", NORMAL));

    // Allocate parking slots
    parking.allocateParkingSlot(); // First emergency vehicle, then normal vehicles
    parking.allocateParkingSlot(); // Continue allocation

    // Show system status
    parking.showStatus();
    sleep(5);

    // Process vehicles exiting
    parking.vehicleExit(); // Exit first vehicle
    sleep(5);
    parking.vehicleExit(); // Exit second vehicle

    // Show system status again
    parking.showStatus();

    return 0;
}
