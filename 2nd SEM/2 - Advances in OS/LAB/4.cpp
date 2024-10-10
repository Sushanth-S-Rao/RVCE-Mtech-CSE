// 4. Simulate a Multilevel Feedback Queue scheduler and analyse the performance using different scheduling metrics.
// MULTI LEVEL FEEDBACK QUEUE

#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
using namespace std;

#define SWAP_INTERVAL 20
#define TIME_QUANTUM 5

// Process Information
struct process {
    string pname;
    int burstTime;      // Amount of CPU time required by the process
    int arrivalTime;    // When the process arrives in the system
};

// Multiple Priority Queue
queue<process> q1;  // Contains highest priority processes 
queue<process> q2;
queue<process> q3;  // Contains lowest priority processes

// Function Declaration
void mlfq(process p[], int total_process);

// MAIN Function
int main() {
    int total_process;
    cout << "What is the NUMBER of PROCESSES: ";
    cin >> total_process;

    process p[total_process];

    cout << "Enter the following information, \n";
    cout << "PROCESS name, burst time, arrival time:\n";

    for(int i = 0; i < total_process; i++) {
        cout << "\nFor Process " << i << ", enter the information: " << endl;
        cin >> p[i].pname;
        cin >> p[i].burstTime;
        cin >> p[i].arrivalTime;
    }

    // Call MLFQ and pass the PROCESSES
    mlfq(p, total_process);

    return 0;
}


// Multi Level Feedback Queue
void mlfq(process p[], int total_process) {
    map<int, vector<process>> m;
    // Store the PROCESSES based on arrival time
    for(int i = 0; i < total_process; i++) {
        int arrival = p[i].arrivalTime;
        m[arrival].push_back(p[i]);
    }

    int globalTime = 0;
    int elapsedTime = 0;
    do{
        int fromTime = globalTime;
        globalTime += TIME_QUANTUM;
        elapsedTime += TIME_QUANTUM;
        cout << "\n~~~~~ At TIME = " << globalTime << " ~~~~~\n";

        for(int i = fromTime; i < globalTime; i++) {
            if(m.find(i) != m.end()) {
                for(auto v : m[i]) {
                    cout << "Processes arriving are: " << v.pid << ", ";
                    q1.push(v);
                }
            }
        }

        if(!q1.empty()) {
            process curr = q1.front();
            q1.pop();
            curr.burstTime -= TIME_QUANTUM;
            if(curr.burstTime > 0)
                q2.push(curr);
        }

        else if(!q2.empty()) {
            process curr = q2.front();
            q2.pop();
            curr.burstTime -= TIME_QUANTUM;
            if(curr.burstTime > 0)
                q3.push(curr);
        }

        else if(!q3.empty()) {
            process curr = q3.front();
            q3.pop();
            curr.burstTime -= TIME_QUANTUM;
            if(curr.burstTime > 0)
                q3.push(curr);
        }

        cout << "\nMulti Queues Snaps\t";
        printQueue(q1);
        printQueue(q2);
        printQueue(q3); 

        // Handling STARVATION
        if(elapsedTime == SWAP_INTERVAL) {
            elapsedTime = 0;

            while(!q2.empty()) {
                process c = q2.front();
                q2.pop();
                q1.push(c);
            }
            
            while(!q3.empty()) {
                process c = q3.front();
                q3.pop();
                q2.push(c);
            }
            
            
            cout << "\n ~~~~~~~~~~~~~~~~~~~~ TIMING ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "Priority of lower level queue is boosted to avoid starvation. New QUEUE SNAP:\n\n";
            printQueue(q1);
            printQueue(q2);
            printQueue(q3);
            cout << "\n";
        }

    }while(!q1.empty() || !q2.empty() || !q3.empty());

}

void printQueue(queue<process> q) {
    cout << "Q: "; 
    while(q.size() > 0) {
        cout << q.front().pid << "(" << q.front().burstTime << ") || ";
        q.pop();
    }
    cout << endl;
}


/*
11 word   7 4
12 vscode 5 3
13 chrome 9 4
14 vlc    3 6
15 calc   2 5
*/