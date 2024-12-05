#include <iostream>
using namespace std;

int main() {
    int x, y, z;

    // Get dimensions for the 3D array
    cout << "Enter the size for dimension x: ";
    cin >> x;
    cout << "Enter the size for dimension y: ";
    cin >> y;
    cout << "Enter the size for dimension z: ";
    cin >> z;

    // Allocate memory for 3D array
    int*** array = new int**[x];
    for (int i = 0; i < x; ++i) {
        array[i] = new int*[y];
        for (int j = 0; j < y; ++j) {
            array[i][j] = new int[z];
        }
    }

    // Fill the 3D array with values
    cout << "Enter values for the 3D array:" << endl;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                cout << "Enter value for array[" << i << "][" << j << "][" << k << "]: ";
                cin >> array[i][j][k];
            }
        }
    }

    // Print the 3D array
    cout << "The 3D array is:" << endl;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                cout << array[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Deallocate memory for the 3D array
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            delete[] array[i][j];  // Free columns
        }
        delete[] array[i];  // Free rows
    }
    delete[] array;  // Free the array of pointers

    return 0;
}
