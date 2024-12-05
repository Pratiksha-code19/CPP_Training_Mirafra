#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
#include <map>

using namespace std;

// Enum to define vehicle types
enum VehicleType {
    NORMAL,
    EMERGENCY
};

// Vehicle class to store vehicle information
class Vehicle {
public:
    string plateNumber;
    VehicleType type;
    time_t entryTime;
    time_t exitTime;
    Vehicle(string plate, VehicleType t) : plateNumber(plate), type(t) {
        entryTime = time(0); // record entry time at the moment of instantiation
    }
};

// Parking System class
class SmartParkingSystem {
private:
    stack<Vehicle> parkingBay;        // Simulate parking bay with stack
    queue<Vehicle> normalQueue;       // General vehicles queue
    queue<Vehicle> emergencyQueue;    // Emergency vehicles queue
    double totalRevenue;              // Track total revenue

public:
    SmartParkingSystem() : totalRevenue(0.0) {}

    // Function to park a vehicle
    void parkVehicle(Vehicle vehicle) {
        if (vehicle.type == EMERGENCY) {
            emergencyQueue.push(vehicle);
            cout << "Emergency vehicle " << vehicle.plateNumber << " added to priority queue." << endl;
        } else {
            normalQueue.push(vehicle);
            cout << "Normal vehicle " << vehicle.plateNumber << " added to waiting queue." << endl;
        }
    }

    // Function to park the next available vehicle from the priority queue or waiting area
    void parkNextVehicle() {
        Vehicle vehicle("", NORMAL);
        
        if (!emergencyQueue.empty()) {
            vehicle = emergencyQueue.front();
            emergencyQueue.pop();
        } else if (!normalQueue.empty()) {
            vehicle = normalQueue.front();
            normalQueue.pop();
        } else {
            cout << "No vehicles to park!" << endl;
            return;
        }

        parkingBay.push(vehicle);
        cout << "Vehicle " << vehicle.plateNumber << " parked!" << endl;
    }

    // Function to calculate the parking fee for a vehicle
    double calculateFee(Vehicle vehicle) {
        double feePerHour = 0.0;
        switch (vehicle.type) {
            case NORMAL:
                feePerHour = 10.0;
                break;
            case EMERGENCY:
                feePerHour = 25.0;
                break;
        }
        
        double duration = difftime(vehicle.exitTime, vehicle.entryTime) / 3600; // in hours
        return duration * feePerHour;
    }

    // Function to simulate vehicle exit and calculate revenue
    void vehicleExit() {
        if (parkingBay.empty()) {
            cout << "No vehicles to exit!" << endl;
            return;
        }

        Vehicle vehicle = parkingBay.top();
        parkingBay.pop();
        vehicle.exitTime = time(0); // record exit time at the moment of departure

        double fee = calculateFee(vehicle);
        totalRevenue += fee;

        cout << "Vehicle " << vehicle.plateNumber << " exited." << endl;
        cout << "Parking fee: $" << fee << endl;
    }

    // Function to display system status
    void displayStatus() {
        cout << "\n=== Parking System Status ===\n";
        cout << "Total Revenue: $" << totalRevenue << endl;
        cout << "Vehicles parked in parking bay: " << parkingBay.size() << endl;
        cout << "Vehicles in emergency queue: " << emergencyQueue.size() << endl;
        cout << "Vehicles in normal queue: " << normalQueue.size() << endl;
        cout << "=============================\n";
    }
};

// Main function
int main() {
    SmartParkingSystem parkingSystem;

    // Simulate vehicles entering the system
    Vehicle car1("ABC123", NORMAL);
    Vehicle car2("EMR999", EMERGENCY);
    Vehicle car3("XYZ456", NORMAL);
    
    parkingSystem.parkVehicle(car1);
    parkingSystem.parkVehicle(car2);
    parkingSystem.parkVehicle(car3);

    // Park vehicles
    parkingSystem.parkNextVehicle(); // Emergency vehicles will be parked first
    parkingSystem.parkNextVehicle();
    parkingSystem.parkNextVehicle();

    // Simulate vehicles exiting and calculate fees
    parkingSystem.vehicleExit();
    parkingSystem.vehicleExit();

    // Display system status
    parkingSystem.displayStatus();

    return 0;
}
