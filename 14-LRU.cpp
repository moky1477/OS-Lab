#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

int lruPageFaults(const vector<int> &referenceString, int numFrames);

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

    int pageFaults = lruPageFaults(referenceString, numFrames);

    cout << "Number of page faults using LRU: " << pageFaults << endl;

    return 0;
}

int lruPageFaults(const vector<int> &referenceString, int numFrames) {
    int pageFaults = 0;
    unordered_map<int, list<int>::iterator> pageMap;
    list<int> lruList;

    for (int i = 0; i < referenceString.size(); i++) {
        int page = referenceString[i];

        if (pageMap.find(page) == pageMap.end()) {
            // Page fault
            pageFaults++;

            if (lruList.size() == numFrames) {
                int lruPage = lruList.back();
                lruList.pop_back();
                pageMap.erase(lruPage);
            }

            lruList.push_front(page);
            pageMap[page] = lruList.begin();
        } else {
            // Page hit
            lruList.erase(pageMap[page]);
            lruList.push_front(page);
            pageMap[page] = lruList.begin();
        }
    }

    return pageFaults;
}
