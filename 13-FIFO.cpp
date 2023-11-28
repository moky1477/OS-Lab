#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int fifoPageFaults(const vector<int> &referenceString, int numFrames);

int main() {
    int numFrames, numReferences;

    cout << "Enter the number of frames: ";
    cin >> numFrames;

    cout << "Enter the number of reference string elements: ";
    cin >> numReferences;

    vector<int> referenceString(numReferences);

    cout << "Enter the reference string elements:\n";
    for (int i = 0; i < numReferences; i++) {
        cin >> referenceString[i];
    }

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
