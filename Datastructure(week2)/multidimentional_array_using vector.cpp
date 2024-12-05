#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
matrix (std::vector<vector<int>>)
 |
 +--> [0] --> [1, 2, 3, 4]  // Row 0 (std::vector<int>) - 4 integers with values 1 to 4
 |
 +--> [1] --> [5, 6, 7, 8]  // Row 1 (std::vector<int>) - 4 integers with values 5 to 8

*/

int main()
{
    int row=3;
    int col=4;

    //create a 2d vector
    vector<vector<int>>vec(row,vector<int>(col));
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            vec[i][j]=i*col+j;
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}