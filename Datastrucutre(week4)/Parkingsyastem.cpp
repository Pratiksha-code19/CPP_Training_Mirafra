#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
#include <chrono>

using namespace std;

// Vehicle Types
enum VehicleType { NORMAL, EMERGENCY, VIP };

// Vehicle class
class Vehicle {
public:
    string licensePlate;
    VehicleType type;
    time_t entryTime;
    time_t exitTime; // Added exitTime

    Vehicle(string plate, VehicleType t) : licensePlate(plate), type(t) {
        entryTime = time(0); // Record entry time
        exitTime = 0; // Exit time will be set when the vehicle exits
    }

    // Function to set the exit time
    void setExitTime() {
        exitTime = time(0); // Set exit time when vehicle exits
    }

    // Function to get parking duration
    double getParkingDuration() {
        if (exitTime == 0) {
            return difftime(time(0), entryTime) / 3600; // Still parked, calculate time until now
        }
        return difftime(exitTime, entryTime) / 3600; // If exited, use exit time
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

    // Pricing logic for parking fee
    double getParkingFee(Vehicle* vehicle) {
        double rate = 0.0;
        double duration = vehicle->getParkingDuration();  // in hours
        if (vehicle->type == NORMAL) {
            rate = 10.0; // $10 per hour for normal vehicles
        } else if (vehicle->type == EMERGENCY) {
            rate = 0.0;  // Free for emergency vehicles
        } else if (vehicle->type == VIP) {
            rate = 15.0; // $15 per hour for VIP vehicles
        }
        return rate * duration;
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
            vehicle->setExitTime(); // Set the exit time when the vehicle exits
            double fee = getParkingFee(vehicle); // Calculate the parking fee
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
    parking.parkNormalVehicle(new Vehicle("DL1000", VIP)); // Adding a VIP vehicle

    // Allocate parking slots
    parking.allocateParkingSlot(); // First emergency vehicle, then normal vehicles
    parking.allocateParkingSlot(); // Continue allocation

    // Show system status
    parking.showStatus();

    // Process vehicles exiting
    parking.vehicleExit(); // Exit first vehicle
    parking.vehicleExit(); // Exit second vehicle
    parking.vehicleExit(); // Exit third vehicle
    parking.vehicleExit(); // Exit fourth vehicle

    // Show system status again
    parking.showStatus();

    return 0;
}
