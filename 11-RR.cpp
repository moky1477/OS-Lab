#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Function prototype
void roundRobin(const vector<int> &arrival_time, const vector<int> &burst_time, int time_quantum, vector<int> &finish_time, vector<int> &turnaround_time, vector<int> &waiting_time);

int main() {
    int n, time_quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter time quantum for Round Robin: ";
    cin >> time_quantum;

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

    // Calculate finish time, turnaround time, and waiting time using Round Robin
    roundRobin(arrival_time, burst_time, time_quantum, finish_time, turnaround_time, waiting_time);

    // Display results
    cout << "\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << arrival_time[i] << "\t\t" << burst_time[i] << "\t\t" << finish_time[i] << "\t\t"
             << turnaround_time[i] << "\t\t" << waiting_time[i] << endl;
    }

    return 0;
}

// Round Robin function definition
void roundRobin(const vector<int> &arrival_time, const vector<int> &burst_time, int time_quantum, vector<int> &finish_time, vector<int> &turnaround_time, vector<int> &waiting_time) {
    int n = arrival_time.size();
    queue<int> process_queue; // Queue to store the indices of the processes

    int current_time = 0;
    int remaining_time[n]; // Remaining burst time for each process

    // Initialize remaining_time array
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    // Process the queue using Round Robin
    while (true) {
        bool all_processes_completed = true;

        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                all_processes_completed = false;

                if (remaining_time[i] > time_quantum) {
                    // Process for time quantum
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                    process_queue.push(i);
                } else {
                    // Process for remaining burst time
                    current_time += remaining_time[i];
                    finish_time[i] = current_time;
                    turnaround_time[i] = finish_time[i] - arrival_time[i];
                    waiting_time[i] = turnaround_time[i] - burst_time[i];
                    remaining_time[i] = 0;
                }
            }
        }

        if (all_processes_completed) {
            break;
        }
    }
}
