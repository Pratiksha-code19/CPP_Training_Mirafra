#include <iostream>
#include <queue>
#include <ctime>
#include <iomanip>
#include <stack>

using namespace std;

// Enum for Vehicle Type
enum VehicleType { NORMAL, EMERGENCY, VIP };

// Structure to store vehicle details
struct Vehicle {
    int id;
    VehicleType type;
    time_t entryTime;
    time_t exitTime;
    
    Vehicle(int id, VehicleType type) : id(id), type(type), entryTime(0), exitTime(0) {}
};

// Class for the Smart Parking System
class SmartParkingSystem {
private:
    // Parking Bay (LIFO stack) and Waiting Queue (FIFO queue)
    stack<Vehicle*> parkingBay;
    queue<Vehicle*> waitingQueue;

    // Total revenue from the system
    double totalRevenue = 0.0;

    // Parking Fee Calculation based on Vehicle Type
    double getParkingFee(Vehicle* vehicle) {
        double fee = 0.0;
        double duration = difftime(vehicle->exitTime, vehicle->entryTime) / 3600;  // Duration in hours
        if (vehicle->type == NORMAL) {
            fee = 10.0;
        } else if (vehicle->type == EMERGENCY) {
            fee = 25.0;
        } else if (vehicle->type == VIP) {
            fee = 15.0;
        }
        return fee * duration;
    }

public:
    // Function to handle vehicle entry
    void vehicleEntry(int id, VehicleType type) {
        Vehicle* vehicle = new Vehicle(id, type);
        vehicle->entryTime = time(0);  // Record the entry time

        if (type == EMERGENCY || type == VIP) {
            // Emergency and VIP vehicles get immediate parking
            parkingBay.push(vehicle);
            cout << "Emergency/VIP vehicle " << id << " has entered the parking lot.\n";
        } else {
            // Normal vehicle either parks or waits
            if (parkingBay.size() < 5) {  // Assume 5 spots available in parking bay
                parkingBay.push(vehicle);
                cout << "Normal vehicle " << id << " has entered the parking lot.\n";
            } else {
                waitingQueue.push(vehicle);
                cout << "Parking is full. Normal vehicle " << id << " is waiting.\n";
            }
        }
    }

    // Function to handle vehicle exit
    void vehicleExit(int id) {
        Vehicle* vehicle = nullptr;

        // Check if vehicle is in the parking bay
        stack<Vehicle*> tempStack;
        while (!parkingBay.empty()) {
            Vehicle* topVehicle = parkingBay.top();
            parkingBay.pop();
            if (topVehicle->id == id) {
                vehicle = topVehicle;
                break;
            }
            tempStack.push(topVehicle);
        }

        // Return other vehicles back to the parking bay stack
        while (!tempStack.empty()) {
            parkingBay.push(tempStack.top());
            tempStack.pop();
        }

        // If the vehicle was not found in the parking bay, check the waiting queue
        if (!vehicle) {
            queue<Vehicle*> tempQueue = waitingQueue;
            while (!tempQueue.empty()) {
                Vehicle* queueVehicle = tempQueue.front();
                tempQueue.pop();
                if (queueVehicle->id == id) {
                    vehicle = queueVehicle;
                    break;
                }
            }
        }

        // If vehicle found, calculate the fee
        if (vehicle) {
            vehicle->exitTime = time(0);  // Record exit time
            double fee = getParkingFee(vehicle);
            totalRevenue += fee;
            cout << "Vehicle " << id << " exited. Total fee: $" << fixed << setprecision(2) << fee << endl;
        } else {
            cout << "Vehicle " << id << " not found in the parking system.\n";
        }
    }

    // Function to display parking system status
    void displayStatus() {
        cout << "\n----- Parking System Status -----\n";
        cout << "Total parked vehicles: " << parkingBay.size() << endl;
        cout << "Waiting Queue: " << waitingQueue.size() << endl;
    }

    // Function to display total revenue
    void displayTotalRevenue() {
        cout << "Total revenue generated: $" << fixed << setprecision(2) << totalRevenue << endl;
    }
};

int main() {
    SmartParkingSystem parkingSystem;

    // Simulate vehicle entries
    parkingSystem.vehicleEntry(101, NORMAL);
    parkingSystem.vehicleEntry(102, EMERGENCY);
    parkingSystem.vehicleEntry(103, VIP);
    parkingSystem.vehicleEntry(104, NORMAL);
    parkingSystem.vehicleEntry(105, NORMAL);
    parkingSystem.vehicleEntry(106, NORMAL);  // This vehicle should go to waiting queue

    // Show status after entries
    parkingSystem.displayStatus();

    // Simulate vehicle exits
    parkingSystem.vehicleExit(102);  // Emergency vehicle
    parkingSystem.vehicleExit(103);  // VIP vehicle
    parkingSystem.vehicleExit(104);  // Normal vehicle

    // Show the total revenue
    parkingSystem.displayTotalRevenue();

    return 0;
}
