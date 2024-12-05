#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int rows=3;
    int *jaggedArr[rows];

    //allocate memory
    jaggedArr[0]=new int[2];
    jaggedArr[1]=new int[3];

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<(i==0 ? 2:(i==1?5:3));j++)
        {
            jaggedArr[i][j]=i+j;
        }
    }

    cout<<"jagged array"<<endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<(i==0?2:(i==1?5:3));j++)
        {
            cout<<jaggedArr[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<rows;i++)
    {
        delete[]jaggedArr[i];
    }
    return 0;
}