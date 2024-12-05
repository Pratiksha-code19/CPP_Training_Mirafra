#include <iostream>
using namespace std;

int main() {
    // Create a jagged array of 3 classrooms, each with a different number of students
    int* classrooms[3];  // Array of pointers (3 classrooms)

    // Allocate memory for each classroom (row)
    classrooms[0] = new int[2];  // Classroom 1 has 2 students
    classrooms[1] = new int[3];  // Classroom 2 has 3 students
    classrooms[2] = new int[1];  // Classroom 3 has 1 student

    // Assign values to each classroom (number of students)
    classrooms[0][0] = 25; classrooms[0][1] = 30; // Classroom 1
    classrooms[1][0] = 28; classrooms[1][1] = 32; classrooms[1][2] = 35; // Classroom 2
    classrooms[2][0] = 18; // Classroom 3

    // Print the number of students in each classroom
    for (int i = 0; i < 3; ++i) {
        cout << "Classroom " << i + 1 << " has the following students: ";
        for (int j = 0; j < i + 2; ++j) { // Classroom 1 has 2, Classroom 2 has 3, etc.
            cout << classrooms[i][j] << " ";
        }
        cout << endl;
    }

    // Free allocated memory
    for (int i = 0; i < 3; ++i) {
        delete[] classrooms[i]; // Free each classroom's memory
    }

    return 0;
}
