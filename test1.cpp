#include<iostream>
#include<algorithm>
using namespace std;


class Product {
protected:
    int productID;
    string name;
    double price;
    
public:
    Product(int id, string n, double p, int q) : productID(id), name(n), price(p) {}

    virtual void display() const {
        cout << "ID: " << productID << ", Name: " << name << ", Price: $" << price << endl;
    }

    // Getter methods for price and quantityInStock
    double getPrice() const { return price; }
    
};

int main()
{
    
    return 0;
}