#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

int lruPageFaults(const vector<int> &referenceString, int numFrames);

int main() {
    // Static values
    int numFrames = 3; // Set your desired number of frames
    vector<int> referenceString = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; // Set your desired reference string

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
