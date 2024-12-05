#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
     int arr[3][4]={{1,2,3,4},{30,40,50,60},{11,12,13,14}};

    // for(int row=0;row<3;row++)
    // {
    //     for(int col=0;col<4;col++)
    //     {
    //         cout<<arr[row][col]<<" ";
    //     }
    //     cout<<endl;
    // }

   #include<iostream>
using namespace std;



    // Using range-based for loop to iterate through the 2D array
    for (auto& row : arr) { // 'row' is a reference to each 1D array (row) in arr
        for (auto& col : row) { // 'col' refers to each element in the row
            cout << col << " ";
        }
        cout << endl;
    }


    return 0;
}