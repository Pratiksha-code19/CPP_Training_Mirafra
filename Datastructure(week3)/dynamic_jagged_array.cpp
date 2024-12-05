#include <iostream>
using namespace std;

int main() {
    int rows;

    // Ask for the number of rows
    cout << "Enter the number of rows (classrooms): ";
    cin >> rows;

    // Dynamically allocate an array of pointers (for rows)
    int** jaggedArray = new int*[rows];

    // For each row, dynamically allocate the number of columns
    for (int i = 0; i < rows; ++i) {
        int cols;

        // Ask for the number of columns (students in each classroom)
        cout << "Enter the number of students in classroom " << i + 1 << ": ";
        cin >> cols;

        // Allocate memory for the current row (classroom)
        jaggedArray[i] = new int[cols];

        // Input values for each classroom
        cout << "Enter " << cols << " student ages for classroom " << i + 1 << ": ";
        for (int j = 0; j < cols; ++j) {
            cin >> jaggedArray[i][j];
        }
    }

    // Print the jagged array (student ages)
    cout << "\nStudent ages in each classroom:\n";
    for (int i = 0; i < rows; ++i) {
        cout << "Classroom " << i + 1 << ": ";
        for (int j = 0; jaggedArray[i][j]; ++j) {  // Print only if valid data
            cout << jaggedArray[i][j] << " ";
        }
        cout << endl;
    }

    // Free memory for each row
    for (int i = 0; i < rows; ++i) {
        delete[] jaggedArray[i];  // Delete memory allocated for each row
    }
    delete[] jaggedArray;  // Delete the array of pointers

    return 0;
}
