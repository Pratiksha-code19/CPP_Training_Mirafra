#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <ctime>
#include <iomanip>

using namespace std;

enum VehicleType { NORMAL, EMERGENCY, VIP };

struct Vehicle {
    int id;
    VehicleType type;
    time_t entryTime;
    time_t exitTime;

    Vehicle(int id, VehicleType type) : id(id), type(type), entryTime(0), exitTime(0) {}
};

class SmartParkingSystem {
private:
    stack<Vehicle*> parkingBay;  // Parking bay implemented as a stack (LIFO)
    queue<Vehicle*> waitingQueue;  // Waiting area implemented as a queue (FIFO)
    priority_queue<Vehicle*, vector<Vehicle*>, function<bool(Vehicle*, Vehicle*)>> priorityQueue;  // Priority Queue
    map<int, Vehicle*> parkedVehicles;  // Map to store parked vehicles
    double totalRevenue = 0.0;

    // Pricing logic
    double getParkingFee(Vehicle* vehicle) {
        double rate = 0.0;
        double duration = difftime(vehicle->exitTime, vehicle->entryTime) / 3600;  // in hours
        if (vehicle->type == NORMAL) {
            rate = 10.0;
        } else if (vehicle->type == EMERGENCY) {
            rate = 25.0;
        } else if (vehicle->type == VIP) {
            rate = 15.0;
        }
        return rate * duration;
    }

public:
    // Constructor to initialize priority queue comparison function
    SmartParkingSystem() : priorityQueue([](Vehicle* v1, Vehicle* v2) {
        return v1->type < v2->type;  // Emergency and VIP have higher precedence
    }) {}

    // Vehicle Entry function
    void vehicleEntry(int id, VehicleType type) {
        Vehicle* vehicle = new Vehicle(id, type);
        vehicle->entryTime = time(0);

        if (type == EMERGENCY || type == VIP) {
            priorityQueue.push(vehicle);
            cout << "Emergency/VIP vehicle " << id << " has entered the parking lot.\n";
        } else {
            if (parkingBay.size() < 5) {  // Assume parking bay has 5 spots
                parkingBay.push(vehicle);
                cout << "Normal vehicle " << id << " has entered the parking lot.\n";
            } else {
                waitingQueue.push(vehicle);
                cout << "Parking is full. Normal vehicle " << id << " is waiting.\n";
            }
        }
    }

    // Vehicle Exit function
    void vehicleExit(int id) {
        Vehicle* vehicle = nullptr;

        // Check if vehicle is in parking bay
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
        while (!tempStack.empty()) {
            parkingBay.push(tempStack.top());
            tempStack.pop();
        }

        // Check if vehicle is in priority queue
        if (!vehicle) {
            priority_queue<Vehicle*, vector<Vehicle*>, function<bool(Vehicle*, Vehicle*)>> tempPriorityQueue = priorityQueue;
            while (!tempPriorityQueue.empty()) {
                Vehicle* pqVehicle = tempPriorityQueue.top();
                tempPriorityQueue.pop();
                if (pqVehicle->id == id) {
                    vehicle = pqVehicle;
                    break;
                }
            }
        }

        // Check if vehicle is in waiting queue
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

        if (vehicle) {
            vehicle->exitTime = time(0);
            double fee = getParkingFee(vehicle);
            totalRevenue += fee;
            cout << "Vehicle " << id << " exited. Total fee: $" << fixed << setprecision(2) << fee << endl;
        } else {
            cout << "Vehicle " << id << " not found.\n";
        }
    }

    // Display the current status of the parking lot
    void displayStatus() {
        cout << "\n----- Parking System Status -----\n";
        cout << "Total parked vehicles: " << parkingBay.size() << endl;
        cout << "Waiting Queue: " << waitingQueue.size() << endl;
        cout << "Priority Queue: " << priorityQueue.size() << endl;
    }

    // Display total revenue
    void displayTotalRevenue() {
        cout << "Total revenue generated: $" << fixed << setprecision(2) << totalRevenue << endl;
    }
};

int main() {
    SmartParkingSystem parkingSystem;

    // Sample data
    parkingSystem.vehicleEntry(101, NORMAL);
    parkingSystem.vehicleEntry(102, EMERGENCY);
    parkingSystem.vehicleEntry(103, VIP);
    parkingSystem.vehicleEntry(104, NORMAL);
    parkingSystem.vehicleEntry(105, NORMAL);
    parkingSystem.vehicleEntry(106, NORMAL);  // Should go to waiting queue

    // Show status after parking entries
    parkingSystem.displayStatus();

    // Vehicles exiting
    parkingSystem.vehicleExit(102);
    parkingSystem.vehicleExit(103);
    parkingSystem.vehicleExit(104);

    // Show total revenue
    parkingSystem.displayTotalRevenue();

    return 0;
}
