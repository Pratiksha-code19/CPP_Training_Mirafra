#include<iostream>
#include<algorithm>
using namespace std;

class Product{
    private:
    int product_id;
    string product_name;
    double price;
    int quantity;
    
    Product(int product_id,string product_name,double price,int quantity)
    {
        this->product_id=product_id;
        this->product_name=product_name;
        this->price=price;
        this->quantity=quantity;
    }

};
class Electronics:public Product{
   
   private:
    int warranty;
   public:
     Electronics(int warranty)
     {
        this->warranty=warranty;
     }
};

class Clothing:public Product{
    private:
     int size_of_cloths;
     public:
     Clothing(int size_of_cloths)
     {
        this->size_of_cloths=size_of_cloths;
     }

};

class Food:public Product{
    private:
      int type_of_food;
};

class Customer{
    private:
    int cust_id;
    string name;
    string email_id;

    public:
    Customer(int cust_id,string name,string email_id)
    {
        this->cust_id=cust_id;
        this->name=name;
        this->email_id=email_id;
    }

};
class Order{
    private:
    int order_id;
    public:
    Order(int order_id)
    {
        this->order_id=order_id;
    }

};
class Cart{
  

};
class Payment()
{

};



int main()
{
    
    return 0;
}