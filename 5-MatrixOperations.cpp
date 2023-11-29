#include <iostream>
#include <pthread.h>
#include <cstdlib>

#define MAX_SIZE 100
#define ROWS 3
#define COLS 3

int matrixA[ROWS][COLS];
int matrixB[ROWS][COLS];
int resultMatrix[ROWS][COLS];

void *matrixMultiplication(void *arg) {
    int row = *((int *)arg);  // Extract row index
    int col = *((int *)(arg + sizeof(int)));  // Extract column index

    resultMatrix[row][col] = 0;
    for (int k = 0; k < COLS; ++k) {
        resultMatrix[row][col] += matrixA[row][k] * matrixB[k][col];
    }

    pthread_exit(nullptr);
}

int main() {
    // Initialize matrices with random values
    srand(time(nullptr));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            matrixA[i][j] = rand() % MAX_SIZE;
            matrixB[i][j] = rand() % MAX_SIZE;
        }
    }

    // Display matrices A and B
    std::cout << "Matrix A:\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << matrixA[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix B:\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << matrixB[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Create threads for matrix multiplication
    pthread_t threads[ROWS][COLS];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int *indices = new int[2]{i, j};
            pthread_create(&threads[i][j], nullptr, matrixMultiplication, static_cast<void *>(indices));
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            pthread_join(threads[i][j], nullptr);
        }
    }

    // Display the result matrix
    std::cout << "\nResult Matrix:\n";
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << resultMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
