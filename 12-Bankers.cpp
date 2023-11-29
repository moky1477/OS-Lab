#include <iostream>
#include <vector>

using namespace std;

// Function prototype
bool isSafe(const vector<vector<int>> &allocation, const vector<vector<int>> &maxDemand, const vector<int> &available, vector<int> &work, vector<bool> &finish);

int main() {
    // Static values
    int numProcesses = 3;
    int numResources = 4;

    // Initialize the allocation matrix
    vector<vector<int>> allocation = {
        {0, 1, 0, 2},
        {1, 0, 3, 3},
        {1, 2, 5, 0}
    };

    // Initialize the maximum demand matrix
    vector<vector<int>> maxDemand = {
        {7, 5, 3, 2},
        {3, 2, 2, 2},
        {9, 0, 2, 2}
    };

    // Initialize the available resources vector
    vector<int> available = {3, 3, 2, 1};

    // Initialize work vector and finish vector
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);

    // Check if the system is in a safe state
    if (isSafe(allocation, maxDemand, available, work, finish)) {
        cout << "The system is in a safe state.\n";
    } else {
        cout << "The system is NOT in a safe state.\n";
    }

    return 0;
}

// Banker's algorithm to check for safe state
bool isSafe(const vector<vector<int>> &allocation, const vector<vector<int>> &maxDemand, const vector<int> &available, vector<int> &work, vector<bool> &finish) {
    int numProcesses = allocation.size();
    int numResources = allocation[0].size();

    vector<vector<int>> need(numProcesses, vector<int>(numResources));

    // Calculate the need matrix
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
        }
    }

    int count = 0;
    while (count < numProcesses) {
        bool found = false;

        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == numResources) {
                    // Process i can finish
                    for (int k = 0; k < numResources; k++) {
                        work[k] += allocation[i][k];
                    }

                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            // If no process can finish, the system is not in a safe state
            return false;
        }
    }

    // If all processes finish, the system is in a safe state
    return true;
}
