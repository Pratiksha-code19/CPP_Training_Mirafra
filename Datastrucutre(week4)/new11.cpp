#include <iostream>
#include <queue>
#include <stack>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class Vehicle {
public:
    string type;   // Type of vehicle (Normal or Emergency)
    time_point<steady_clock> entry_time;

    Vehicle(string t) : type(t), entry_time(steady_clock::now()) {}
};

class ParkingSystem {
private:
    stack<Vehicle> normalSlot;   // Stack for normal vehicle slot (LIFO)
    queue<Vehicle> emergencySlot; // Queue for emergency vehicle slot (FIFO)
    priority_queue<time_point<steady_clock>> pq; // Priority queue to handle vehicles based on priority

    double totalRevenue;

public:
    ParkingSystem() : totalRevenue(0.0) {}

    // Function to add a vehicle to its respective slot
    void addVehicle(Vehicle vehicle) {
        if (vehicle.type == "Emergency") {
            emergencySlot.push(vehicle);
        } else {
            normalSlot.push(vehicle);
        }
    }

    // Function to process vehicles (First emergency vehicles, then normal vehicles)
    void processParking() {
        // Process emergency vehicles first
        if (!emergencySlot.empty()) {
            Vehicle emergencyVehicle = emergencySlot.front();
            emergencySlot.pop();
            auto exit_time = steady_clock::now();
            auto duration = duration_cast<seconds>(exit_time - emergencyVehicle.entry_time).count();
            cout << "Emergency Vehicle parked for " << duration << " seconds. No charge." << endl;
        }

        // Then process normal vehicles
        if (!normalSlot.empty()) {
            Vehicle normalVehicle = normalSlot.top();
            normalSlot.pop();
            auto exit_time = steady_clock::now();
            auto duration = duration_cast<seconds>(exit_time - normalVehicle.entry_time).count();
            double fee = 10.0 * (duration / 3600.0);  // 10 dollars per hour
            totalRevenue += fee;
            cout << "Normal Vehicle parked for " << duration << " seconds. Fee: $" << fee << endl;
        }
    }

    // Function to get total revenue
    double getTotalRevenue() {
        return totalRevenue;
    }
};

int main() {
    ParkingSystem system;

    // Simulating vehicle arrivals
    system.addVehicle(Vehicle("Normal"));
    this_thread::sleep_for(seconds(5)); // Simulate time passing
    system.addVehicle(Vehicle("Emergency"));
    this_thread::sleep_for(seconds(3)); // Simulate more time passing
    system.addVehicle(Vehicle("Normal"));

    // Process the parking
    cout << "Processing Parking..." << endl;
    system.processParking();
    system.processParking();
    system.processParking();

    // Display the total revenue
    cout << "Total Revenue: $" << system.getTotalRevenue() << endl;

    return 0;
}
