#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int fifoPageFaults(const vector<int> &referenceString, int numFrames);

int main() {
    // Static values
    int numFrames = 3; // Set your desired number of frames
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0}; // Set your desired reference string

    int pageFaults = fifoPageFaults(referenceString, numFrames);

    cout << "Number of page faults using FIFO: " << pageFaults << endl;

    return 0;
}

int fifoPageFaults(const vector<int> &referenceString, int numFrames) {
    int pageFaults = 0;
    queue<int> fifoQueue;
    unordered_set<int> frameSet;

    for (int i = 0; i < referenceString.size(); i++) {
        int page = referenceString[i];

        if (frameSet.find(page) == frameSet.end()) {
            // Page fault
            pageFaults++;

            if (fifoQueue.size() == numFrames) {
                int frontPage = fifoQueue.front();
                fifoQueue.pop();
                frameSet.erase(frontPage);
            }

            fifoQueue.push(page);
            frameSet.insert(page);
        }
    }

    return pageFaults;
}
