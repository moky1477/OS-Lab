#include<bits/stdc++.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;

void priority(vector<int> &arrival, vector<int> &burst, vector<int> &priority_list, vector<int> &finish, vector<int> &turn_around, vector<int> &waiting){
    int n = arrival.size();

    vector<pair<int, pair<int, int>>> process;
    for(int i=0; i<n; i++){
        process.push_back({priority_list[i], {arrival[i], i}});
    }

    sort(process.begin(), process.end());

    finish[0] = process[0].second.first + burst[process[0].second.second];
    turn_around[0] = finish[0] - arrival[process[0].second.second];
    waiting[0] = 0;

    for(int i=1; i<n; i++){
        finish[i] = max(finish[i-1], process[i].second.first) + burst[process[i].second.second];
        turn_around[i] = finish[i] - arrival[process[i].second.second];
        waiting[i] = turn_around[i] - burst[process[i].second.second];
    }
}

int main(){
    int n=4;
    vector<int> arrival = {0, 2, 4, 6};
    vector<int> burst = {3, 6, 2, 5};
    vector<int> priority_list = {2, 1, 3, 4};
    vector<int> finish(n, 0);
    vector<int> waiting(n, 0);
    vector<int> turn_around(n, 0);

    priority(arrival, burst, priority_list, finish, turn_around, waiting);

    cout<<"Process\tArrival Time\tBurst Time\tPriority\tFinish Time\tTurn Around Time\tWaiting Time"<<endl;
    for(int i=0; i<n; i++){
        cout<<i+1<<"\t\t"<<arrival[i]<<"\t\t"<<burst[i]<<"\t\t"<<priority_list[i]<<"\t\t"<<finish[i]<<"\t\t"<<turn_around[i]<<"\t\t"<<waiting[i]<<endl;
    }

    return 0;
}

