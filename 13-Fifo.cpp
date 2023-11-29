#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

int fifo(vector<int> referenceString, int frames){
    int n = referenceString.size();
    int page_faults = 0;
    queue<int> fifo_q;
    unordered_set<int> frameSet;

    for(int i=0; i<n; i++){
        int page = referenceString[i];
        if(frameSet.find(page)==frameSet.end()){
            page_faults++;

            if(fifo_q.size()==frames){
                int front = fifo_q.front();
                fifo_q.pop();
                frameSet.erase(front);
            }
            fifo_q.push(page);
            frameSet.insert(page);
        }
    }

    return page_faults;
}

int main(){
    int frames = 3;
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 1, 2, 0};
    int faults = fifo(referenceString, frames);

    cout<<"Page faults using FIFO: "<<faults<<endl;
}
