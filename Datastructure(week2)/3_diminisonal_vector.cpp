#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;



int main() {
    int x = 2, y = 3, z = 4;  // Dimensions of the 3D vector (2x3x4)

    // Create a 3D vector: 2 matrices, each having 3 rows and 4 columns
    vector<vector<vector<int>>> matrix(x, vector<vector<int>>(y, vector<int>(z, 0)));

    // Fill the 3D matrix with values
    int value = 1;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                matrix[i][j][k] = value++;  // Assign a unique value to each element
            }
        }
    }

    // Print the 3D matrix
    cout << "The 3D matrix is:" << endl;
    for (int i = 0; i < x; ++i) {
        cout << "Matrix " << i + 1 << ":\n";
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                cout << matrix[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

    