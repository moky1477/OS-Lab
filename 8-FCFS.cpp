#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

void fcfs(vector<int> &arrival,vector<int> &burst,vector<int> &turn_around,vector<int> &finish,vector<int> &waiting){
    int n = arrival.size();
    finish[0] = arrival[0] + burst[0];
    turn_around[0] = finish[0] - arrival[0];
    waiting[0] = 0;

    for(int i=1; i<n; i++){
        finish[i] = max(finish[i-1], arrival[i])+burst[i];
        turn_around[i] = finish[i] - arrival[i];
        waiting[i] = turn_around[i]-burst[i];
    }
}

int main(){
    int n = 4;
    vector<int> arrival = {0, 1, 2, 4};
    vector<int> burst = {4, 3, 6, 2};
    vector<int> finish(n, 0);
    vector<int> turn_around(n, 0);
    vector<int> waiting(n, 0);

    fcfs(arrival, burst, turn_around, finish, waiting);
    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for(int i=0; i<n; i++){
        cout<<i+1<<"\t"<<arrival[i]<<"\t\t"<<burst[i]<<"\t\t"<<waiting[i]<<"\t\t"<<finish[i]<<"\t\t"<<turn_around[i]<<endl;
    }
    return 0;
}
