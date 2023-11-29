#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

using namespace std;

int optimalPageFaults(const vector<int> &referenceString, int numFrames);

int main() {
    // Static values
    int numFrames = 3; // Set your desired number of frames
    vector<int> referenceString = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; // Set your desired reference string

    int pageFaults = optimalPageFaults(referenceString, numFrames);

    cout << "Number of page faults using Optimal: " << pageFaults << endl;

    return 0;
}

int optimalPageFaults(const vector<int> &referenceString, int numFrames) {
    int pageFaults = 0;
    unordered_map<int, int> pageMap; // Page to next occurrence index map
    vector<int> frames;

    for (int i = 0; i < referenceString.size(); i++) {
        int page = referenceString[i];

        // If the page is not in the frames
        if (pageMap.find(page) == pageMap.end()) {
            pageFaults++;

            // If frames are not full, add the page
            if (frames.size() < numFrames) {
                frames.push_back(page);
            } else {
                // Find the page in frames with the longest remaining distance to the next occurrence
                int farthest = -1, farthestIndex = numeric_limits<int>::max();
                for (int j = 0; j < frames.size(); j++) {
                    if (pageMap[frames[j]] > farthestIndex) {
                        farthest = j;
                        farthestIndex = pageMap[frames[j]];
                    }
                }

                // Replace the farthest page with the current page
                frames[farthest] = page;
            }
        }

        // Update the next occurrence index for the current page
        pageMap[page] = i;
    }

    return pageFaults;
}
