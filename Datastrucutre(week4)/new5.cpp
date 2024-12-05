#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <ctime>

using namespace std;

// Vehicle types
enum VehicleType { NORMAL, EMERGENCY };

// Vehicle structure
struct Vehicle {
    string plateNumber;
    VehicleType type;
    time_t entryTime;
    
    Vehicle(string plate, VehicleType t) : plateNumber(plate), type(t) {
        entryTime = time(0); // record current time when vehicle enters
    }
    
    // Function to calculate parking duration in hours
    double getParkingDuration() {
        return difftime(time(0), entryTime) / 3600.0;
    }
};

// Comparison function for priority queue
struct VehicleComparator {
    bool operator()(const Vehicle& v1, const Vehicle& v2) {
        // Emergency vehicles should have higher priority (sorted by type)
        if (v1.type == EMERGENCY && v2.type == NORMAL) return true;
        if (v1.type == NORMAL && v2.type == EMERGENCY) return false;
        
        // If both are the same type, compare entry times (first come first serve)
        return v1.entryTime > v2.entryTime; // earlier entry time has higher priority
    }
};

class ParkingLot {
private:
    stack<Vehicle> parkingSlot;    // To simulate parking slots (stack - LIFO)
    queue<Vehicle> waitingQueue;   // To hold waiting vehicles (queue)
    priority_queue<Vehicle, vector<Vehicle>, VehicleComparator> parkingQueue; // To prioritize emergency vehicles
    int maxCapacity;

public:
    // Constructor
    ParkingLot(int capacity) : maxCapacity(capacity) {}

    // Function to enter the parking lot
    void enterParking(Vehicle vehicle) {
        if (parkingSlot.size() < maxCapacity) {
            // If there's space in the parking lot, park the vehicle
            parkingSlot.push(vehicle);
            cout << vehicle.plateNumber << " parked." << endl;
        } else {
            // If parking is full, add to the waiting queue
            waitingQueue.push(vehicle);
            cout << vehicle.plateNumber << " is waiting for a parking slot." << endl;
        }
    }

    // Function to exit the parking lot and calculate the fee
    void exitParking() {
        if (!parkingSlot.empty()) {
            Vehicle vehicle = parkingSlot.top();
            parkingSlot.pop();
            
            // Calculate the parking fee
            double parkingDuration = vehicle.getParkingDuration();
            double fee = (vehicle.type == NORMAL) ? 10.0 * parkingDuration : 0.0;
            cout << vehicle.plateNumber << " exited. Duration: " << parkingDuration << " hours, Fee: $" << fee << endl;
            
            // After a vehicle exits, check if there are waiting vehicles
            if (!waitingQueue.empty()) {
                // Give priority to emergency vehicles first
                Vehicle nextVehicle = waitingQueue.front();
                waitingQueue.pop();
                
                // Add the next waiting vehicle to parking
                enterParking(nextVehicle);
            }
        } else {
            cout << "No vehicle in the parking lot." << endl;
        }
    }

    // Function to handle parking lot status and revenue
    void displayStatus() {
        cout << "Parking lot status: " << parkingSlot.size() << "/" << maxCapacity << " vehicles parked." << endl;
        cout << "Waiting queue size: " << waitingQueue.size() << endl;
    }
};

// Main function
int main() {
    ParkingLot parking(2); // Create a parking lot with a capacity of 2 vehicles
    
    // Create some vehicles (emergency and normal)
    Vehicle v1("ABC123", NORMAL);
    Vehicle v2("DEF456", EMERGENCY);
    Vehicle v3("GHI789", NORMAL);
    
    // Vehicles entering the parking lot
    parking.enterParking(v1);
    parking.enterParking(v2);
    parking.enterParking(v3); // This vehicle will have to wait
    
    // Display the current status
    parking.displayStatus();
    
    // Simulate vehicles exiting the parking lot
    parking.exitParking(); // Emergency vehicle exits
    parking.displayStatus();
    
    parking.exitParking(); // Normal vehicle exits
    parking.displayStatus();
    
    return 0;
}
