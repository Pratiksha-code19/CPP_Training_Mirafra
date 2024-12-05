#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//Excpetion Handling

class CannotRemoveOrder
{
private:
    string message;

public:
    CannotRemoveOrder(string message)
    {
        this->message = message;
    }

    const char *what() noexcept
    {
        return message.c_str();
    }
};

class Cart;
class Product
{
public:
    int product_id;
    string product_name;
    double price;
    int quantity;

    Product() : product_id(0), product_name(""), price(0.0), quantity(0) {}

    Product(int id, string name, double price, int q)
    {
        this->product_id = id;
        this->product_name = name;
        this->price = price;
        quantity = q;
    }

    void display_product()
    {
        cout << "Product ID : " << product_id << endl;
        cout << "Product Name : " << product_name << endl;
        cout << "Price : " << price << endl;
        cout << "Quantity : " << quantity << endl;
    }

    int get_product_id() const 
    {
        return product_id;
    }

    double getPrice() const
    {
        return price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    void setQuantity(int q)
    {
        quantity = q;
    }

    friend ostream &operator<<(ostream &os, const Product &p)
    {
        os << "Product ID: " << p.product_id << endl
           << "Product Name: " << p.product_name << endl
           << "Price: " << p.price << endl
           << "Quantity: " << p.quantity;
        return os;
    }
};

class Electronics : public Product
{
protected:
    int warranty;

public:
    Electronics(int id, string name, double price, int quantity, int warranty) : Product(id, name, price, quantity), warranty(warranty)
    {
    }
};

class Clothing : public Product
{
protected:
    int sizeofcloth;

public:
    Clothing(int id, string name, double price, int quantity, int size) : Product(id, name, price, quantity), sizeofcloth(size)
    {
    }
};

class Food : public Product
{
protected:
    string typeofFood;

public:
    Food(int id, string name, double price, int quantity, string food) : Product(id, name, price, quantity), typeofFood(food)
    {
    }
};

class Customer
{
public:
    int customer_id;
    string customer_name;
    string customer_address;

    Customer(int id, string name, string address)
    {
        customer_id = id;
        customer_name = name;
        customer_address = address;
    }

    void displayCustomer()
    {
        cout << "Customer ID : " << customer_id << endl;
        cout << "Customer Name : " << customer_name << endl;
        cout << "Customer Address : " << customer_address << endl;
    }

    // friend void addProduct(Product& p , Customer& c);
};

class Inventory
{
public:
    map<int, Product> InventoryMap;
    int quant;

    void AddInInventory(map<int, Product> mp)
    {
        InventoryMap = mp;
    }

    void RemoveFromInventory( int id , int quantity)
    {
        // for (auto x : InventoryMap)
        // {
        //     if (x.second.product_id == id)
        //     {
        //         quant = x.second.getQuantity() - quantity;
        //         if (quant == 0)
        //         {
                     InventoryMap.erase(id);
        //         }
        //         else
        //         {
        //             x.second.quantity = quant ;
        //         }
        //     }
        // }
    }

    void DisplayInventory()
    {
        cout << "Product in Inventory : " << endl;
        for (auto x : InventoryMap)
        {
            cout << "Product ID : " << x.first << ": " << x.second << endl;
            cout << endl;
        }
    }
};

class Order
{
private:
    int orderID;
    vector<Product> plist;
    Inventory &inventory;

public:
    int totalCost = 0;

    Order(int orderID, Inventory &inv) : orderID(orderID), inventory(inv)
    {
    }

    void addProduct(  Product &p, const Customer &c)
    {
        plist.push_back(p);
        cout << "Order placed for Customer with customer id " << c.customer_id << endl;

        totalCost = totalCost + (p.getPrice() * p.getQuantity());

        inventory.RemoveFromInventory(p.get_product_id(), p.getQuantity());
    }

    // void AddPaymentMethod(string str){
    //     if(string == "UPI"){

    //     }
    // }

    void removeFromOrder(int id)
    {
        for (auto i = plist.begin(); i != plist.end(); i++)
        {
            if (id == i->get_product_id())
            {
                totalCost = totalCost - i->getPrice();
                plist.erase(i);
            }
            else
            {
                throw CannotRemoveOrder("Sorry Cannot Remove this Product from the Order");
            }
        }
    }

    void displayOrder()
    {
        for (int i = 0; i < plist.size(); i++)
        {
            cout << "Product ID : " << plist[i].product_id << endl;
            cout << "Product Name : " << plist[i].product_name << endl;
            cout << "Product Price : " << plist[i].price << endl;
            cout << "Product Quantity : " << plist[i].quantity << endl;
            cout << endl;
        }
    }
};

class Cart
{
private:
    vector<Product> tempCart;

public:
    void AddToCart(const Product &p)
    {
        tempCart.push_back(p);
    }

    void RemoveFromCart(int product_id)
    {
        for (auto it = tempCart.begin(); it != tempCart.end(); ++it)
        {
            if (it->get_product_id() == product_id)
            {
                tempCart.erase(it);
                break;
            }
        }
    }
};

class Payment
{
    string paymentMethod;

public:
    Payment(string payment)
    {
        paymentMethod = payment;
    }

    virtual int UPI() = 0;
    virtual int COD() = 0;
    virtual int CreditCard() = 0;
    virtual int DebitCard() = 0;
    virtual int NetBanking() = 0;
};

int main()
{

    Inventory inv;
    Product p(101, "Fan", 1000, 1000);
    Product p2(102, "Laptop", 50000, 500);
    Product p3(103, "Mouse", 500, 1400);
    Product p4(201, "Slik", 1200, 100);
    map<int, Product> productMap;
    vector<Product> tempv = {p, p2, p3,p4};

    for (auto x : tempv)
    {
        productMap[x.product_id] = x;
    }

    inv.AddInInventory(productMap);
    inv.DisplayInventory();

    // I will give customer details
    Customer cust(1001, "Honour ", "Baner ,Pune");
    cout << endl;

    // then I will give order
    Electronics e(101, "Fan", 1000, 1, 5);
    Clothing c(201, "Slik", 1200, 3, 120);

    // then it will go to cart
    Cart cart;
    cart.AddToCart(e);
    cart.AddToCart(c);

    cout << endl;

    // my details will  be visible
    cust.displayCustomer();
    cout << endl;

    // i will order now
    Order o(1, inv);

    o.addProduct(e, cust);
    o.addProduct(c, cust);
    cout << "GRAND PRICE : " << o.totalCost << endl;
    cout << endl;

    // the display the order
    cout << "Order Details After payment: " << endl;
    o.displayOrder();

    cout << "Trying to remove Order: " << endl;
    o.removeFromOrder(e.product_id);
    o.displayOrder();
    cout << "GRAND PRICE AFTER REmoving some Item : " << o.totalCost << endl;

    // finally
    //  I will see the invnetory
    inv.DisplayInventory();
}