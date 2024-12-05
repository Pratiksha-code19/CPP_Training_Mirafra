#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
class multiply{
    int factor;
    public:
    multiply(int fac):factor(fac){}
    int operator()(int x)const
    {
        return x*factor;
    }
};
int main()
{
    vector<int> vec={10,20,30};
    multiply mul(10);
    cout<<"vector before transform";
    for(int val:vec)
    {
        cout<<val<<"";
    }
    cout<<endl;
    transform(vec.begin(),vec.end(),vec.begin(),mul);
    for(int val:vec)
    {
        
    }
    return 0;
}