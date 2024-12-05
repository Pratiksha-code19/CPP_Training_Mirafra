#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{

    vector<int>number;
    cout<<"capacity before"<<number.capacity()<<endl;
    cout<<"size before"<<number.size()<<endl;
    
    number.push_back(10);
    cout<<"capacity after adding"<<number.capacity()<<endl;
    cout<<"size after adding "<<number.size()<<endl;
    
    number.push_back(20);
    cout<<"capacity after adding"<<number.capacity()<<endl;
    cout<<"size after adding "<<number.size()<<endl;
    
    number.push_back(30);
    number.push_back(40);
    cout<<"capacity after adding "<<number.capacity()<<endl;
    cout<<"size"<<number.size()<<endl;
    
    number.push_back(50);
    cout<<"size"<<number.size()<<endl;
    cout<<"capacity after"<<number.capacity()<<endl;
   
    number.push_back(20);
    cout<<"capacity after "<<number.capacity()<<endl;
   
    number.push_back(10);
    number.push_back(20);
    number.push_back(30);
    cout<<"capacity after "<<number.capacity()<<endl;
    
    
    number.push_back(40);
    number.push_back(59);
    number.push_back(40);
    number.push_back(59);
    number.push_back(40);
    number.push_back(59);
    number.push_back(40);
     number.push_back(40);
    cout<<"size"<<number.size()<<endl;
     cout<<"capacity after "<<number.capacity()<<endl;



   // number.insert(number.begin()+4,150);
    //number.pop_back();
   // number.erase(number.begin()+3);

   // number.resize(10,50);
    //number.reserve(15);
    //cout<<"capacity:"<<number.capacity();
    
    //number.clear();

for(int i:number)
{
    cout<<i;
}

    return 0;
}
