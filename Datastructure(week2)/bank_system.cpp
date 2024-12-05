// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
//#include <bits/stdc++.h>

using namespace std;

class BankAccount {
protected:
    int accountNumber;         // Unique account number
    string accountHolder;       // Name of the account holder
    double balance;             // Account balance

public:
    // Constructor
    BankAccount(int accNum, string holder, double initialBalance)
        : accountNumber(accNum), accountHolder(holder), balance(initialBalance) {
        cout << "BankAccount created for " << accountHolder << " with initial balance $" << balance << endl;
    }

    // Method to deposit money into the account
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Deposit amount must be positive!" << endl;
        }
    }

    // Method to withdraw money from the account
    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds. Withdrawal of $" << amount << " failed." << endl;
        } else if (amount <= 0) {
            cout << "Withdrawal amount must be positive!" << endl;
        } else {
            balance -= amount;
            cout << "Withdrew: $" << amount << ". New balance: $" << balance << endl;
        }
    }

    // Method to display account information
    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: $" << balance << endl;
    }
    
    int getAccountNumber()const
    {
        return accountNumber;
    }

    // Virtual destructor
    /*virtual ~BankAccount() {
        cout << "BankAccount for " << accountHolder << " is being closed." << endl;
    }*/
};

class BankBranch
{
    private:
    string branchName;
    string branchAddress;
    vector<BankAccount> accounts;
    
    public:
    BankBranch(const string& name, const string& address) : 
        branchName(name), branchAddress(address){}
    
    void addAccount(int accountNum, const string& accountName, double balance)
    {
        BankAccount newAcc(accountNum, accountName, balance);
        accounts.push_back(newAcc);
        cout<<"Account created for "<<accountName <<" with account number: "<<accountNum <<endl;
    }
    
    //Find an account number 
    BankAccount* findAccount(int accountNum)
    {
        for(auto& account: accounts)
        {
            if(account.getAccountNumber() == accountNum)
            {
                return &account;
            }
        }
        cout<<"Account number: "<<accountNum<<endl;
        return nullptr;
    }
    
    //Display all accounts
    void displayAllAccs() const
    {
        cout<<"All bank accounts: "<<endl;
        for(const auto& account: accounts)
        {
            account.display();
        }
    }
    
    string getBranch()const
    {
        return branchName;
    }
};

class BankSystem
{
    private:
    vector<vector<BankAccount>> branches;
    
    public:
    //Initialize specific number of branches in the constructor
    BankSystem(int noOfBranches)
    {
        branches.resize(noOfBranches);
    }
    
    void addAccountToBranch(int branchIndex, const BankAccount account)
    {
        if(branchIndex < branches.size())
        {
            branches[branchIndex].push_back(account);
        }
        else
        {
            cout<<" Branch index out of range" << endl;
        }
    }
    
    //Display all branches
    void displayAllBranches() const
    {
        for(int i=0; i< branches.size(); i++)
        {
            for(const auto& account : branches[i])
            {
                account.display();
            }
        }
    }
    
    void depositToAccount(int branchIndex, int accountNum, double amount)
    {
        if(branchIndex < branches.size())
        {
            for(auto& account: branches[branchIndex])
            {
                if(account.getAccountNumber() == accountNum)
                {
                    account.deposit(amount);
                    cout<<"Deposited " <<amount<< " to account "<< accountNum<< " in branch "<< branchIndex<<endl;
                    return;
                }
            }
            cout<<"Account not found in branch"<<endl;
        }
        else
        {
            cout<<"Branch index out of range"<<endl;
        }
    }
    
    void withdrawFromAccount(int branchIndex, int accountNum, double amount)
    {
        if(branchIndex < branches.size())
        {
            for(auto& account: branches[branchIndex])
            {
                if(account.getAccountNumber() == accountNum)
                {
                    account.withdraw(amount);
                    return;
                }
            }
            cout<<"Account not found in branch "<< branchIndex << endl;
        }
        else
        {
            cout<<"Branch index out of range"<<endl;
        }
    }
    
    
};

int main() {
    BankSystem bank(2);
    bank.addAccountToBranch(0, BankAccount(10001, "User1", 10000.00));
    bank.addAccountToBranch(0, BankAccount(2001, "User2", 100.00));
    bank.addAccountToBranch(1, BankAccount(3001, "User21", 500.00));
    bank.addAccountToBranch(1, BankAccount(4001, "User22", 500000.00));
    bank.addAccountToBranch(1, BankAccount(50001, "User23", 40000.00));
    
    bank.displayAllBranches();
    cout<<"Deposit"<<endl;
    bank.depositToAccount(0, 2001, 300.0);
    bank.depositToAccount(1, 50001, 1000.0);
    
    bank.withdrawFromAccount(1, 50001, 30000.0);
    bank.withdrawFromAccount(0, 10001, 5000.0);
    

    return 0;
}