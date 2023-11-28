#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function prototype
void sjf(const vector<int> &arrival_time, const vector<int> &burst_time, vector<int> &finish_time, vector<int> &turnaround_time, vector<int> &waiting_time);

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> arrival_time(n);
    vector<int> burst_time(n);
    vector<int> finish_time(n, 0);
    vector<int> turnaround_time(n, 0);
    vector<int> waiting_time(n, 0);

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> arrival_time[i];

        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> burst_time[i];
    }

    // Calculate finish time, turnaround time, and waiting time using SJF
    sjf(arrival_time, burst_time, finish_time, turnaround_time, waiting_time);

    // Display results
    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << turnaround_time[i] << "\t\t" << waiting_time[i] << endl;
    }

    return 0;
}

// SJF function definition
void sjf(const vector<int> &arrival_time, const vector<int> &burst_time, vector<int> &finish_time, vector<int> &turnaround_time, vector<int> &waiting_time) {
    int n = arrival_time.size();
    vector<pair<int, pair<int, int>>> process; // {burst_time, {arrival_time, process_index}}

    // Initialize the process vector
    for (int i = 0; i < n; i++) {
        process.push_back({burst_time[i], {arrival_time[i], i}});
    }

    // Sort processes based on burst time
    sort(process.begin(), process.end());

    finish_time[0] = process[0].second.first + process[0].first;
    turnaround_time[0] = finish_time[0] - process[0].second.first;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        finish_time[i] = finish_time[i - 1] + process[i].first;
        turnaround_time[i] = finish_time[i] - process[i].second.first;
        waiting_time[i] = turnaround_time[i] - process[i].first;
    }
}
