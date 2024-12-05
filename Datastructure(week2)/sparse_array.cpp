#include <iostream>
#include <map>

/*Why sparse array is required over simple arrays to store the elements:

    Storage: When there is the maximum number of zero elements and the minimum number of non-zero elements then we use a sparse array over a simple array as it requires less memory to store the elements. In the sparse array, we only store the non-zero elements. 
    Computation Time: In the sparse array we only store non-zero elements and hence, traversing only non-zero elements takes less computation time.


Recommendation Systems

    Application: Systems like Netflix, Amazon, and YouTube recommend products, movies, or videos based on users’ interactions. The interaction matrix (users vs items) is sparse because each user interacts with only a small subset of all available items.
    Example: If there are 10 million users and 1 million products, most of the entries in the user-item matrix are zero, meaning a user hasn’t rated or interacted with a product. Using a sparse array (or similar data structures), you can store only the non-zero ratings, saving significant memory and improving efficiency when building recommendation algorithms.
*/

class SparseArray {
private:
    // Map to store non-zero values and their indices
    std::map<int, int> elements;
    int size;

public:
    // Constructor to initialize the size
    SparseArray(int n) : size(n) {}

    // Set an element at index `index` to `value`
    void set(int index, int value) {
        if (index >= size) {
            std::cout << "Index out of bounds\n";
            return;
        }
        if (value != 0)
            elements[index] = value; // Store non-zero value
        else
            elements.erase(index);    // Remove if the value is zero
    }

    // Get an element at a given index
    int get(int index) const {
        if (index >= size) {
            std::cout << "Index out of bounds\n";
            return 0;
        }
        auto it = elements.find(index);
        if (it != elements.end())
            return it->second;
        return 0; // Return 0 if the element is not in the map
    }

    // Print all non-zero elements
    void print() const {
        for (const auto &pair : elements) {
            std::cout << "Index: " << pair.first << ", Value: " << pair.second << "\n";
        }
    }
};

int main() {
    SparseArray sparseArray(10); // Create a sparse array of size 10

    // Setting some values
    sparseArray.set(2, 10);
    sparseArray.set(5, 20);
    sparseArray.set(8, 30);

    // Accessing elements
    std::cout << "Element at index 1: " << sparseArray.get(1) << "\n"; //output:0
    std::cout << "Element at index 2: " << sparseArray.get(2) << "\n"; // Output: 10
    std::cout << "Element at index 3: " << sparseArray.get(3) << "\n"; // Output: 0 (default)
    std::cout << "Element at index 9: " << sparseArray.get(9) << "\n"; 

    

    // Printing all non-zero elements
    std::cout << "Non-zero elements in the sparse array:\n";
    sparseArray.print();

    return 0;
}





