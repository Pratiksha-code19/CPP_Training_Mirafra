#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class Cart;
class Product{
    public:
       int  product_id;
       string product_name;
       double price;
       int quantity;

       Product() : product_id(0), product_name(""), price(0.0), quantity(0) {}

       Product(int id ,  string name, double price , int q){
        this->product_id = id;
        this->product_name = name;
        this->price = price;
        quantity = q;
       }

        void display_product(){
        cout << "Product ID : " << product_id << endl;
        cout << "Product Name : " << product_name << endl;
        cout << "Price : " << price << endl;
        cout << "Quantity : " << quantity << endl;
       }

       int  get_product_id() const{
        return product_id;
       }

       double getPrice() const{
        return price;
       }

       int getQuantity() const {
        return quantity;
       }


};

class Electronics : public Product{
    protected:
        int warranty;
    
    public:
        Electronics(int id, string name, double price, int quantity, int warranty) : Product(id, name,price,quantity) , warranty(warranty){

        }
        
};

class Clothing : public Product{
    protected:
        int sizeofcloth;
    public:
        Clothing(int id, string name, double price, int quantity, int size) : Product(id, name,price,quantity) , sizeofcloth(size){

        }
};

class Food : public Product{
    protected:
        string typeofFood;
    public:
        Food(int id, string name, double price, int quantity, string food) : Product(id, name,price,quantity) , typeofFood(food){

        }
};

class Customer{
    public:
        int customer_id;
        string customer_name;
        string customer_address;
        string customer_email;

    
        Customer(int id , string name , string address,string email){
            customer_id = id;
            customer_name = name;
            customer_address = address;
            customer_email=email;
        }

        void displayCustomer(){
            cout << "Customer ID : " << customer_id << endl;
            cout << "Customer Name : " << customer_name << endl;
            cout << "Customer Address : " << customer_address << endl;
            cout<<"Customer Email:"<<customer_email<<endl;
        }

        //friend void addProduct(Product& p , Customer& c);

};

class Inventory{
    public:
        map<int,Product> mp;
    
        void AddInInventory(const Product& p){
            mp[p.product_id] = p;
        }

        void RemoveFromInventory(const Product& p){
            mp.erase(p.product_id);
        }
};

class Order {
private:
    int orderID;
    vector<Product> plist;
    int totalCost = 0;
    Inventory& inventory; 

public:
    Order(int orderID, Inventory& inv) : orderID(orderID), inventory(inv) {
    }

    void addProduct(const Product& p, const Customer& c) {
        plist.push_back(p);
        cout << "Order placed for Customer with customer id " << c.customer_id << endl;

        totalCost += (p.getPrice() * p.getQuantity());

        inventory.RemoveFromInventory(p);
    }

    void displayOrder() {
        for (int i = 0; i < plist.size(); i++) {
            cout << "Product ID : " << plist[i].product_id << endl;
            cout << "Product Name : " << plist[i].product_name << endl;
            cout << "Product Price : " << plist[i].price << endl;
            cout << "Product Quantity : " << plist[i].quantity << endl;
            
        }
    }
};

class Cart{
    private:
        vector<Product> tempCart;
    public:
        void AddToCart(const Product& p){
            tempCart.push_back(p);
        }

void RemoveFromCart(int product_id) {
    for (auto it = tempCart.begin(); it != tempCart.end(); ++it) {
        if (it->get_product_id() == product_id) {
            tempCart.erase(it);
            break; 
        }
    }
}

};

class Payment{
    string Payment_type;
    public:
      Payment(int Payment_type)
      {
        this->Payment_type=Payment_type;
      }
      virtual void paypal()=0;
      virtual void upi()=0;
      virtual void credit()=0;
};

int main(){
    
    
    Electronics e(101 , "light bulb" , 200 , 2 , 5);
    Clothing c(201 , "cotton " , 12000, 3 , 12);

    Cart cart;
    cart.AddToCart(e);
    cart.AddToCart(c);

    Customer cust(10 , "Pratiksha ", "alandi,Pune","kalepathu19@gmail.com");
    Inventory inv;
    cust.displayCustomer();
    Order o(1,inv);

    o.addProduct(e,cust) ;
    o.addProduct(c,cust);

    o.displayOrder();

    
}