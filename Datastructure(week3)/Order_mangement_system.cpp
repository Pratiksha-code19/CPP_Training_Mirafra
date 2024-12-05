#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// MenuItem class representing a menu item in a restaurant
class MenuItem {
public:
    string name;
    double price;

    MenuItem(string name, double price) {
        this->name = name;
        this->price = price;
    }

    void display() const {
        cout << "  - " << name << " - $" << price << endl;
    }
};

// Restaurant class representing a restaurant that contains a menu
class Restaurant {
public:
    string name;
    vector<MenuItem> menu;  // Dynamic array to store menu items

    Restaurant(string name) {
        this->name = name;
    }

    // Add a menu item to the restaurant's menu
    void addMenuItem(string name, double price) {
        menu.push_back(MenuItem(name, price));
    }

    // Display the restaurant and its menu
    void display() const {
        cout << "\nRestaurant: " << name << endl;
        cout << "Menu:\n";
        for (const auto& item : menu) {
            item.display();
        }
    }
};

// Order class representing a customer's order
class Order {
public:
    string customerName;
    Restaurant* restaurant;
    vector<MenuItem> items;  // List of items in the order

    Order(string customerName, Restaurant* restaurant) {
        this->customerName = customerName;
        this->restaurant = restaurant;
    }

    // Add an item to the order
    void addItem(const MenuItem& item) {
        items.push_back(item);
    }

    // Calculate total price of the order
    double totalPrice() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.price;
        }
        return total;
    }

    // Display order details
    void display() const {
        cout << "\nOrder for: " << customerName << " from " << restaurant->name << endl;
        cout << "Items ordered:\n";
        for (const auto& item : items) {
            item.display();
        }
        cout << "Total price: $" << totalPrice() << endl;
    }
};

// FoodOrderingSystem class managing restaurants and orders
class FoodOrderingSystem {
private:
    unordered_map<string, Restaurant*> restaurantMap;  // Store restaurants by name
    queue<Order> orderQueue;  // Queue for managing orders for delivery

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
        Order order(customerName, restaurant);

        for (const auto& itemName : itemNames) {
            bool itemFound = false;
            for (const auto& menuItem : restaurant->menu) {
                if (menuItem.name == itemName) {
                    order.addItem(menuItem);
                    itemFound = true;
                    break;
                }
            }
            if (!itemFound) {
                cout << "Item " << itemName << " not found in menu!" << endl;
            }
        }

        orderQueue.push(order);
        cout << "Order placed successfully!" << endl;
    }

    // Process and deliver the next order in the queue
    void processOrder() {
        if (orderQueue.empty()) {
            cout << "No orders to process!" << endl;
            return;
        }

        Order order = orderQueue.front();
        orderQueue.pop();
        order.display();
    }
};

// Main function to run the system
int main() {
    FoodOrderingSystem system;

    // Add restaurants
    system.addRestaurant("Pizza Hut");
    system.addRestaurant("Burger King");

    // Add menu items to Pizza Hut
    system.addMenuItemToRestaurant("Pizza Hut", "Pepperoni Pizza", 12.99);
    system.addMenuItemToRestaurant("Pizza Hut", "Veggie Pizza", 10.99);
    system.addMenuItemToRestaurant("Pizza Hut", "Garlic Bread", 4.99);

    // Add menu items to Burger King
    system.addMenuItemToRestaurant("Burger King", "Cheeseburger", 5.99);
    system.addMenuItemToRestaurant("Burger King", "Whopper", 6.99);
    system.addMenuItemToRestaurant("Burger King", "French Fries", 2.99);

    // Display all restaurants and menus
    system.displayRestaurants();

    // Place some orders
    vector<string> order1Items = {"Pepperoni Pizza", "Garlic Bread"};
    system.placeOrder("John Doe", "Pizza Hut", order1Items);

    vector<string> order2Items = {"Cheeseburger", "French Fries"};
    system.placeOrder("Jane Smith", "Burger King", order2Items);

    // Process orders
    system.processOrder();
    system.processOrder();

    return 0;
}
