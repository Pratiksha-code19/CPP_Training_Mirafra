#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    // int row=3;
    // int col=4;
    
    // //allocate the memory
    // int **arr=new int *[row];  //pointer to array of pointer
    // for(int i=0;i<row;i++)
    // {
    //     arr[i]=new int[col];
    // }

    // //initialize array
    // for(int i=0;i<row;i++)
    // {
    //     for(int j=0;j<col;j++)
    //     {
    //         arr[i][j]=i*col+j;
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }




    int rows, cols;

    // Get the number of rows and columns from the user
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    // Create a dynamic 2D array using pointers
    int** arr = new int*[rows]; // Allocate memory for rows
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols]; // Allocate memory for columns in each row
    }

    // Fill the array with values
    cout << "Enter values for the matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Enter value for matrix[" << i << "][" << j << "]: ";
            cin >> arr[i][j];
        }
    }

    // Print the matrix
    cout << "The matrix is:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocate the memory
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i]; // Free each row's memory
    }
    delete[] arr; // Free the array of pointers

    return 0;
}

















