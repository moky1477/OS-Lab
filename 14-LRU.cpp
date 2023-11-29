#include<bits/stdc++.h>

using namespace std;

// Function to implement Least Recently Used (LRU) page replacement algorithm
int lru(vector<int> referenceString, int frames) {
    int faults = 0; // Variable to count page faults
    unordered_set<int> pageSet; // Set to store unique pages in memory
    list<int> lruList; // List to maintain the order of pages based on recent use
    int n = referenceString.size(); // Size of the reference string

    // Iterate through the reference string
    for(int i=0; i<n; i++) {
        int page = referenceString[i];

        // Check if the page is not in the page set (page fault)
        if(pageSet.find(page) == pageSet.end()) {
            faults++; // Increment page fault count

            // Check if the list is already at its maximum capacity (frames)
            if(lruList.size() == frames) {
                int lruPage = lruList.back(); // Get the least recently used page
                lruList.pop_back(); // Remove the least recently used page from the list
                pageSet.erase(lruPage); // Remove the least recently used page from the set
            }

            lruList.push_front(page); // Add the current page to the front of the list (most recently used)
            pageSet.insert(page); // Add the current page to the set
        } else {
            // If the page is already in memory, update its position in the list (move to the front)
            lruList.remove(page);
            lruList.push_front(page);
        }
    }

    return faults; // Return the total number of page faults
}

// Main function
int main() {
    int frames = 3; // Number of frames in the memory
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0}; // Reference string
    int pageFaults = lru(referenceString, frames); // Call the LRU function
    cout << "Page Faults using LRU: " << pageFaults << endl; // Display the total number of page faults

    return 0; // Return 0 to indicate successful program execution
}
