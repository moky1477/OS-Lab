#include <iostream>
#include <vector>

using namespace std;

// FCFS function definition
void fcfs(const vector<int> &arrival_time, const vector<int> &burst_time, vector<int> &finish_time, vector<int> &turnaround_time, vector<int> &waiting_time) {
    int n = arrival_time.size();
    finish_time[0] = arrival_time[0] + burst_time[0];
    turnaround_time[0] = finish_time[0] - arrival_time[0];
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        finish_time[i] = max(finish_time[i - 1], arrival_time[i]) + burst_time[i];
        turnaround_time[i] = finish_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }
}

int main() {
    // Set the number of processes
    int n = 4; // You can change this value as needed

    // Static input for arrival time and burst time for each process
    vector<int> arrival_time = {0, 2, 4, 7};
    vector<int> burst_time = {4, 3, 6, 2};
    vector<int> finish_time(n, 0);
    vector<int> turnaround_time(n, 0);
    vector<int> waiting_time(n, 0);

    // Calculate finish time, turnaround time, and waiting time using FCFS
    fcfs(arrival_time, burst_time, finish_time, turnaround_time, waiting_time);

    // Display results
    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << turnaround_time[i] << "\t\t" << waiting_time[i] << endl;
    }

    return 0;
}
