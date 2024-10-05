#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int processID;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
};

// Function to calculate waiting time for each process in FCFS
void calculateWaitingTime(queue<Process> &q, int n) {
    Process prevProcess = q.front();
    prevProcess.waitingTime = 0; // First process has no waiting time
    q.pop();
    queue<Process> tempQueue;
    tempQueue.push(prevProcess);

    while (!q.empty()) {
        Process currentProcess = q.front();
        q.pop();
        currentProcess.waitingTime = prevProcess.waitingTime + prevProcess.burstTime;
        prevProcess = currentProcess;
        tempQueue.push(currentProcess);
    }

    // Replace the original queue with the updated queue
    q = tempQueue;
}

// Function to calculate turnaround time for each process
void calculateTurnAroundTime(queue<Process> &q, int n) {
    queue<Process> tempQueue;
    while (!q.empty()) {
        Process currentProcess = q.front();
        q.pop();
        currentProcess.turnAroundTime = currentProcess.burstTime + currentProcess.waitingTime;
        tempQueue.push(currentProcess);
    }
    // Replace the original queue with the updated queue
    q = tempQueue;
}

// Function to display waiting time and turnaround time
void displayResults(queue<Process> q, int n) {
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    while (!q.empty()) {
        Process currentProcess = q.front();
        q.pop();
        totalWaitingTime += currentProcess.waitingTime;
        totalTurnAroundTime += currentProcess.turnAroundTime;

        cout << currentProcess.processID << "\t\t" << currentProcess.burstTime << "\t\t"
             << currentProcess.waitingTime << "\t\t" << currentProcess.turnAroundTime << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n;
    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
}

int main() {
    int n;

    // Input number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    queue<Process> processQueue;

    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        Process p;
        p.processID = i + 1;
        cout << "Enter burst time for process " << p.processID << ": ";
        cin >> p.burstTime;
        processQueue.push(p);
    }

    // Calculate waiting and turnaround times
    calculateWaitingTime(processQueue, n);
    calculateTurnAroundTime(processQueue, n);

    // Display the results
    displayResults(processQueue, n);

    return 0;
}
