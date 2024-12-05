#include <bits/stdc++.h>
using namespace std;

// Inventory Management System

class Items {
public:
    int itemId;
    string name;
    int quantity;
    double price;

public:
    Items() {
        itemId = 0;
        name = "";
        quantity = 0;
        price = 0.0;
    }

    Items(int itemId, string name, int quantity, double price) {
        this->itemId = itemId;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
    }

    friend ostream& operator<<(ostream& os, const Items& item);
};

class Inventory {
private:
    vector<vector<vector<Items>>> inventory;
    int warehouse;
    int aisle;
    int bins;

public:
    Inventory() {}

    Inventory(int warehouse, int aisle, int bins) {
        this->warehouse = warehouse;
        this->aisle = aisle;
        this->bins = bins;

        // Initialize inventory with empty items
        for (int i = 0; i <= warehouse; i++) {
            vector<vector<Items>> layer;
            for (int j = 0; j <= aisle; j++) {
                vector<Items> row;
                for (int k = 0; k <= bins; k++) {
                    row.push_back(Items());
                }
                layer.push_back(row);
            }
            inventory.push_back(layer);
        }
    }

    void addItem(int warehouseIndex, int aisleIndex, int binIndex, Items item) {
        if (item.quantity > 0) {
            inventory[warehouseIndex][aisleIndex][binIndex] = item;
        } else {
            cout << "Item quantity is zero. Not adding to inventory." << endl;
        }
    }

    void removeItemById(int itemId) {
        bool found = false;
        for (int i = 0; i < inventory.size(); i++) {
            for (int j = 0; j < inventory[i].size(); j++) {
                for (int k = 0; k < inventory[i][j].size(); k++) {
                    if (inventory[i][j][k].itemId == itemId) {
                        inventory[i][j][k] = Items();  // Reset to empty item
                        cout << "Item with ID " << itemId << " removed from location (Warehouse: " << i << ", Aisle: " << j << ", Bin: " << k << ")." << endl;
                        found = true;
                        return;
                    }
                }
            }
        }
        if (!found) {
            cout << "Item with ID " << itemId << " not found in inventory." << endl;
        }
    }

    void checkStockById(int itemId) {
        bool found = false;
        for (int i = 0; i < inventory.size(); i++) {
            for (int j = 0; j < inventory[i].size(); j++) {
                for (int k = 0; k < inventory[i][j].size(); k++) {
                    if (inventory[i][j][k].itemId == itemId) {
                        cout << "Stock for item ID " << itemId << " found at location (Warehouse: " << i << ", Aisle: " << j << ", Bin: " << k << "):" << endl;
                        cout << inventory[i][j][k] << endl;
                        found = true;
                        return;
                    }
                }
            }
        }
        if (!found) {
            cout << "Item with ID " << itemId << " not found in inventory." << endl;
        }
    }

    void lowStockAlert(int threshold) {
        bool alertFlag = false;
        cout << "Low Stock Alert (below threshold of " << threshold << "):" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            for (int j = 0; j < inventory[i].size(); j++) {
                for (int k = 0; k < inventory[i][j].size(); k++) {
                    if (inventory[i][j][k].quantity > 0 && inventory[i][j][k].quantity < threshold) {
                        cout << "Location: (Warehouse: " << i << ", Aisle: " << j << ", Bin: " << k << ")" << endl;
                        cout << inventory[i][j][k] << endl;
                        alertFlag = true;
                    }
                }
            }
        }
        if (!alertFlag) {
            cout << "No items with low stock." << endl;
        }
    }

    void display() {
        for (int i = 0; i < inventory.size(); i++) {
            for (int j = 0; j < inventory[i].size(); j++) {
                for (int k = 0; k < inventory[i][j].size(); k++) {
                    if (inventory[i][j][k].name != "" || inventory[i][j][k].quantity > 0) {
                        cout << "Location: (Warehouse: " << i << ", Aisle: " << j << ", Bin: " << k << ")" << endl;
                        cout << inventory[i][j][k] << endl;
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
    }
};

ostream& operator<<(ostream& os, const Items& item) {
    os << "Item ID: " << item.itemId << "\nName: " << item.name << "\nQuantity: " << item.quantity << "\nPrice: " << item.price << "\n";
    return os;
}

int main() {
    Inventory I(3, 3, 3);
    I.addItem(0, 0, 0, Items(101, "TV", 9, 90000));
    I.addItem(0, 0, 2, Items(102, "AC", 9, 45000));
    I.addItem(0, 0, 1, Items(103, "Watch", 11, 45000));

    cout << "Current Inventory:" << endl;
    I.display();

    
    cout << "\nRemoving item with ID 101:" << endl;
    I.removeItemById(101);
    I.display();




    // Checking stock by ID
    cout << "\nChecking stock for item ID 102:" << endl;
    I.checkStockById(102);

    // Low stock alert
    cout << "\nLow Stock Alert with threshold 10:" << endl;
    I.lowStockAlert(10);

    return 0;
}
