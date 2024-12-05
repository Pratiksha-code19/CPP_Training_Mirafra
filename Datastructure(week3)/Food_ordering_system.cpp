#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// Linked List Node for MenuItem
class MenuItemNode {
public:
    string name;
    double price;
    MenuItemNode* next;

    MenuItemNode(string name, double price) {
        this->name = name;
        this->price = price;
        this->next = nullptr;
    }
};

// Restaurant class representing a restaurant that contains a menu
class Restaurant {
public:
    string name;
    MenuItemNode* menuHead;  // Linked list of menu items

    Restaurant(string name) {
        this->name = name;
        menuHead = nullptr;
    }

    // Add a menu item to the restaurant's menu
    void addMenuItem(string name, double price) {
        MenuItemNode* newItem = new MenuItemNode(name, price);
        newItem->next = menuHead;
        menuHead = newItem;
    }

    // Display the restaurant and its menu (linked list traversal)
    void display() const {
        cout << "\nRestaurant: " << name << endl;
        cout << "Menu:\n";
        MenuItemNode* temp = menuHead;
        while (temp) {
            cout << "  - " << temp->name << " - $" << temp->price << endl;
            temp = temp->next;
        }
    }
};

// Order class representing a customer's order
class Order {
public:
    string customerName;
    Restaurant* restaurant;
    vector<MenuItemNode*> items;  // Vector of items in the order (using dynamic array)

    Order(string customerName, Restaurant* restaurant) {
        this->customerName = customerName;
        this->restaurant = restaurant;
    }

    // Add an item to the order
    void addItem(MenuItemNode* item) {
        items.push_back(item);
    }

    // Calculate total price of the order
    double totalPrice() const {
        double total = 0;
        for (const auto& item : items) {
            total += item->price;
        }
        return total;
    }

    // Display order details
    void display() const {
        cout << "\nOrder for: " << customerName << " from " << restaurant->name << endl;
        cout << "Items ordered:\n";
        for (const auto& item : items) {
            cout << "  - " << item->name << " - $" << item->price << endl;
        }
        cout << "Total price: $" << totalPrice() << endl;
    }
};

// Circular Linked List for Order Queue
class CircularOrderQueue {
public:
    struct Node {
        Order* order;
        Node* next;
        Node(Order* order) : order(order), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    CircularOrderQueue() : head(nullptr), tail(nullptr) {}

    // Add an order to the circular queue
    void enqueue(Order* order) {
        Node* newNode = new Node(order);
        if (tail) {
            tail->next = newNode;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        tail->next = head;  // Making it circular
    }

    // Process and remove the next order from the queue
    void processOrder() {
        if (!head) {
            cout << "No orders to process!" << endl;
            return;
        }
        Order* order = head->order;
        head = head->next;
        tail->next = head;  // Maintain circular structure

        order->display();
        delete order;  // Clean up the order after processing
    }
};

// FoodOrderingSystem class managing restaurants and orders
class FoodOrderingSystem {
private:
    unordered_map<string, Restaurant*> restaurantMap;  // Store restaurants by name
    CircularOrderQueue orderQueue;  // Circular linked list for orders

public:
    // Add a new restaurant to the system
    void addRestaurant(string name) {
        if (restaurantMap.find(name) == restaurantMap.end()) {
            restaurantMap[name] = new Restaurant(name);
            cout << "Restaurant " << name << " added successfully!" << endl;
        } else {
            cout << "Restaurant " << name << " already exists!" << endl;
        }
    }

    // Add a menu item to a restaurant
    void addMenuItemToRestaurant(string restaurantName, string itemName, double price) {
        auto it = restaurantMap.find(restaurantName);
        if (it != restaurantMap.end()) {
            it->second->addMenuItem(itemName, price);
            cout << "Menu item " << itemName << " added to " << restaurantName << "!" << endl;
        } else {
            cout << "Restaurant " << restaurantName << " not found!" << endl;
        }
    }

    // Display all restaurants and their menus
    void displayRestaurants() const {
        if (restaurantMap.empty()) {
            cout << "No restaurants available!" << endl;
            return;
        }
        for (const auto& pair : restaurantMap) {
            pair.second->display();
        }
    }

    // Place an order from a specific restaurant
    void placeOrder(string customerName, string restaurantName, vector<string> itemNames) {
        auto it = restaurantMap.find(restaurantName);
        if (it == restaurantMap.end()) {
            cout << "Restaurant " << restaurantName << " not found!" << endl;
            return;
        }

        Restaurant* restaurant = it->second;
        Order* order = new Order(customerName, restaurant);

        // Traverse the linked list of menu items to find the ordered items
        MenuItemNode* temp = restaurant->menuHead;
        while (temp) {
            for (const auto& itemName : itemNames) {
                if (temp->name == itemName) {
                    order->addItem(temp);
                }
            }
            temp = temp->next;
        }

        orderQueue.enqueue(order);  // Add the order to the queue
        cout << "Order placed successfully!" << endl;
    }

    // Process orders from the circular queue
    void processOrder() {
        orderQueue.processOrder();
    }
};

// Main function to run the system
int main() {
    FoodOrderingSystem system;

    // Add restaurants
    system.addRestaurant("Sai Sagar");
    system.addRestaurant("Rupali");

    // Add menu items to Sai Sagar
    system.addMenuItemToRestaurant("Sai Sagar", "Chilly Paneer Dry", 120);
    system.addMenuItemToRestaurant("Sai Sagar", "Veg. Manchurian Dry", 190);
   

    // Add menu items to Rupali
    system.addMenuItemToRestaurant("Rupali", "Dum birayani", 250);
    
    system.addMenuItemToRestaurant("Rupali", "French Fries", 666);

    // Display all restaurants and menus
    system.displayRestaurants();

    // Place some orders
    vector<string> order1Items = {"Chilly Paneer Dry","Veg. Manchurian Dry" };
    system.placeOrder("Pratiksha", "Sai Sagar", order1Items);

    vector<string> order2Items = {"Dum birayani", "French Fries"};
    system.placeOrder("Nihal", "Rupali", order2Items);

    // Process orders
    system.processOrder();
    system.processOrder();

    return 0;
}
