#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Vehicle {
    string type;  // 'emergency' or 'normal'
    int entryTime;  // time of entry in minutes

    Vehicle(string t, int entry) : type(t), entryTime(entry) {}
};

class ParkingLot {
private:
    int totalSpaces;         // Total parking spaces
    stack<Vehicle> parkingLot;  // Parked vehicles in a stack (LIFO)
    queue<Vehicle> waitingQueue;  // Waiting vehicles in a queue
    int totalRevenue = 0;     // Total revenue from parking

public:
    ParkingLot(int spaces) : totalSpaces(spaces) {}

    // Simulate vehicle entering the parking lot
    void vehicleEnter(string type, int entryTime) {
        Vehicle newVehicle(type, entryTime);

        if (parkingLot.size() < totalSpaces) {
            // If parking lot has space, park the vehicle
            parkingLot.push(newVehicle);
            cout << type << " vehicle entered at time " << entryTime << " and parked." << endl;
        } else {
            // If parking lot is full, add to the waiting queue
            waitingQueue.push(newVehicle);
            cout << type << " vehicle entered at time " << entryTime << " and is waiting." << endl;
        }
    }

    // Simulate vehicle exiting the parking lot
    void vehicleExit(int exitTime) {
        if (!parkingLot.empty()) {
            // A vehicle exits the parking lot
            Vehicle parkedVehicle = parkingLot.top();
            parkingLot.pop();

            // Calculate parking duration
            int parkingDuration = exitTime - parkedVehicle.entryTime;

            // Revenue calculation: Normal vehicles pay $10/hour
            if (parkedVehicle.type == "normal") {
                totalRevenue += 10 * parkingDuration / 60;  // Convert minutes to hours
            }

            cout << parkedVehicle.type << " vehicle exited at time " << exitTime << ". Duration: "
                 << parkingDuration << " minutes. Revenue: $" << (parkedVehicle.type == "normal" ? 10 * parkingDuration / 60 : 0) << endl;

            // After a vehicle exits, check if there's a waiting vehicle to park
            if (!waitingQueue.empty()) {
                Vehicle nextVehicle = waitingQueue.front();
                waitingQueue.pop();
                vehicleEnter(nextVehicle.type, exitTime);
            }
        } else {
            cout << "No vehicle is currently parked." << endl;
        }
    }

    // Display total revenue
    void displayRevenue() {
        cout << "Total Revenue: $" << totalRevenue << endl;
    }
};

int main() {
    ParkingLot parkingLot(3);  // Parking lot with 3 spaces

    // Simulating vehicles entering the parking lot
    parkingLot.vehicleEnter("normal", 0);      // Normal vehicle enters at time 0
    parkingLot.vehicleEnter("emergency", 5);  // Emergency vehicle enters at time 5
    parkingLot.vehicleEnter("normal", 10);    // Normal vehicle enters at time 10
    parkingLot.vehicleEnter("normal", 15);    // Normal vehicle enters at time 15 (lot full)

    parkingLot.vehicleExit(30);  // A vehicle exits at time 30
    parkingLot.vehicleExit(45);  // A vehicle exits at time 45

    // Display total revenue
    parkingLot.displayRevenue();

    return 0;
}

if noraml vehicel and emergency vehicle entry time is same than give first piriority to the emergency vehical..
and same for waiting slot if the emergency and normal vehicel are waiting together than push first emergency vehical to the parking slot than normal vehicel 