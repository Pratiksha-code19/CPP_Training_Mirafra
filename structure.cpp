#include<iostream>
#include<algorithm>
using namespace std;

class BankAccount
{
    struct customerinfo
    {
        string name;
        int age;
        string address;
        
    };
    customerinfo customer;
    double balance;
    public:
    BankAccount(const string& name,int age,const string& address,double initlbal):balance(initlbal)
    {
        customer.name=name;
        customer.age=age;
        customer.address=address;
        
    }
    void deposit(double amount)
    {
        if(amount>0)
        {
            balance+=amount;
            cout<<"deposited:"<<amount<<"updated balnce"<<balance<<endl;
        }
        else{
            cout<<"invalid amount"<<endl;
        }
    }
    void withdraw(double amount)
    {
        if(amount>0 && amount<=balance)
        {
            balance-=amount;
        }
        else{
            cout<<"insufficient funds"<<endl;
        }
    }
    void display()
    {
        cout<<"name"<<customer.name<<endl;
        cout<<"age"<<customer.age<<endl;
        cout<<"balance"<<customer.address<<endl;
    }
    
};
int main()
{
    BankAccount account("pratiksha",23,"pune",50000);
    account.deposit(2000);
    account.withdraw(10000);
    account.display();
    
    return 0;
}