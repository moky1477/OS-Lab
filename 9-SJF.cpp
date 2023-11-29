#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

void sjf(vector<int> &arrival, vector<int> &burst, vector<int> &waiting, vector<int> &turn_around, vector<int> &finish){
    int n = arrival.size();
    vector<pair<int, pair<int, int>>> process;
    for(int i=0; i<n; i++){
        process.push_back({burst[i], {arrival[i], i}});
    }

    sort(process.begin(), process.end());

    finish[0] = process[0].second.first+process[0].first;
    turn_around[0] = finish[0]-process[0].second.first;
    waiting[0]=0;

    for(int i=1; i<n; i++){
        finish[i] = finish[i-1]+process[i].first;
        turn_around[i]=finish[i]-process[i].second.first;
        waiting[i]=turn_around[i]-process[i].first;
    }
}

int main(){
    int n=4;
    vector<int> arrival = {1, 2, 3, 6};
    vector<int> burst = {3, 5, 4, 2};

    vector<int> finish(n, 0);
    vector<int> waiting(n, 0);
    vector<int> turn_around(n, 0);

    sjf(arrival, burst, waiting, turn_around, finish);

    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for(int i=0; i<n; i++){
        cout<<i+1<<"\t\t"<<arrival[i]<<"\t\t"<<burst[i]<<"\t\t"<<finish[i]<<"\t\t"<<turn_around[i]<<"\t\t"<<waiting[i]<<endl;
    }

    return 0;

}
