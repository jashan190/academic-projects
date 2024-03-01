#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

using namespace std;

// Function to multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    size_t rowsA = A.size();
    size_t colsA = A[0].size();
    size_t colsB = B[0].size();

    // Initialize the composition matrix with 0s
    vector<vector<int>> composition(rowsA, vector<int>(colsB, 0));

    for (size_t i = 0; i < rowsA; ++i) {
        for (size_t j = 0; j < colsB; ++j) {
            for (size_t k = 0; k < colsA; ++k) {
                composition[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return composition;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Define the binary relation matrix from Task 1
    vector<vector<int>> binaryMatrix = {
        {1, 0, 0},
        {0, 0, 1},
        {0, 1, 0}
    };

    // Generate a second 3x3 matrix with random values between 0 and 9
    vector<vector<int>> randomMatrix(3, vector<int>(3));
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            randomMatrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }

    // Display the matrices
    cout << "Binary Relation Matrix:" << endl;
    printMatrix(binaryMatrix);
    cout << "Random Matrix:" << endl;
    printMatrix(randomMatrix);

    // Perform matrix multiplication
    vector<vector<int>> result = multiplyMatrices(binaryMatrix, randomMatrix);
    cout << "Resultant Matrix after multiplication:" << endl;
    printMatrix(result);
    
    return 0;
}

