#include<bits/stdc++.h>

using namespace std;

int optimal(vector<int> referenceString, int numFrames){
    int faults = 0;
    int n = referenceString.size();
    vector<int> frames;
    unordered_set<int> pageSet;

    for(int i=0; i<n; i++){
        int page = referenceString[i];

        // If the page is not in the frames
        if(pageSet.find(page)==pageSet.end()){
            faults++;

            // If frames are not full, add the page
            if(frames.size()<numFrames){
                frames.push_back(page);
                pageSet.insert(page);
            }
            else{
                // Find the page in frames with the longest remaining distance to the next occurrence
                int farthest = -1, farthestIndex = INT_MAX;
                for(int j=0; j<frames.size(); j++){
                    if(pageSet.find(frames[j])!=pageSet.end() && i-j>farthestIndex){
                        farthest = j;
                        farthestIndex = i-j;
                    }
                }
                // Replace the farthest page with the current page
                pageSet.erase(frames[farthest]);
                pageSet.insert(page);
                frames[farthest] = page;
            }
        }
    }

    return faults;
}

int main(){
    int numFrames = 3;
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7}; // Set your desired reference string
    int ans = optimal(referenceString, numFrames);

    cout<<"Page Faults: "<<ans<<endl;

    return 0;
}
