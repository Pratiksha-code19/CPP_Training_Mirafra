#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Base class for Product
class Product {
protected:
    int productID;
    string name;
    double price;
    int quantityInStock;
public:
    Product(int id, string n, double p, int q) : productID(id), name(n), price(p), quantityInStock(q) {}

    virtual void display() const {
        cout << "ID: " << productID << ", Name: " << name << ", Price: $" << price << ", Stock: " << quantityInStock << endl;
    }

    // Getter methods for price and quantityInStock
    double getPrice() const { return price; }
    int getQuantityInStock() const { return quantityInStock; }

    friend void applyDiscount(class Order &order, double discount);
};

// Derived class for Grocery products
class Grocery : public Product {
public:
    Grocery(int id, string n, double p, int q) : Product(id, n, p, q) {}

    void display() const override {
        cout << "Grocery - ID: " << productID 
             << ", Name: " << name 
             << ", Price: $" << price 
             << ", Stock: " << quantityInStock << endl;
    }
};

// Derived class for Beverage products
class Beverage : public Product {
public:
    Beverage(int id, string n, double p, int q) : Product(id, n, p, q) {}

    void display() const override {
        cout << "Beverage - ID: " << productID 
             << ", Name: " << name 
             << ", Price: $" << price 
             << ", Stock: " << quantityInStock << endl;
    }
};

// Order class to manage orders
class Order {
private:
    int orderID;
    vector<Product> productList;
    double totalCost = 0.0;
public:
    Order(int id) : orderID(id) {}

    void addProduct(const Product &product) {
        productList.push_back(product);
        totalCost += product.getPrice() * product.getQuantityInStock();  // Using getter methods
    }

    friend void applyDiscount(Order &order, double discount) {
        if (order.totalCost > 100) {
            order.totalCost -= order.totalCost * (discount / 100);
        }
    }

    void displayOrder() const {
        cout << "Order ID: " << orderID << ", Total Cost: $" << totalCost << endl;
    }
};

int main() {
    vector<Product*> inventory;
    vector<Order> orders;

    // Creating products and adding them to inventory
    Grocery apple(101, "Apple", 1.5, 50);
    Beverage juice(201, "Orange Juice", 2.0, 20);
    inventory.push_back(&apple);
    inventory.push_back(&juice);

    // Displaying all products in inventory
    cout << "Inventory:\n";
    for (const auto& product : inventory) {
        product->display();
    }

    // Creating an order and adding products to it
    Order order1(1);
    order1.addProduct(apple);
    order1.addProduct(juice);

    // Displaying order details before and after applying discount
    cout << "\nOrder Details (Before Discount):\n";
    order1.displayOrder();
    applyDiscount(order1, 10.0);  // Apply 10% discount
    cout << "Order Details (After Discount):\n";
    order1.displayOrder();

    return 0;
}