// 5. Implement a lottery scheduler with random seeds. 
// LOTTERY SCHEDULER

#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<bits/stdc++.h>
using namespace std;

#define TIME_QUANTUM 20

// Process Information
struct process {
    string name;
    int burstTime;      // Amount of CPU time required by the process
    int ticket_start;   // TICKETS
    int ticket_end;
    bool completed;
};

// Function Declaration
void lotteryScheduler(int total_process, int totalTickets, process P[]);

// MAIN Function
int main() {
    int total_process;
    cout << "What is the NUMBER of PROCESSES: ";
    cin >> total_process;
    process P[total_process];

    int t = 0;
    int gstart = 0;
    int gend = 0;
    int totalTickets = 0;    
    cout << "Enter name, burst time and tickets:\n";
    for(int i = 0; i < total_process; i++) {
        cin >> P[i].name >> P[i].burstTime;
        cin >> t;
        totalTickets += t;
        gstart = gend;
        gend += t;
        P[i].ticket_start = gstart;
        P[i].ticket_end = gend;
        P[i].completed = false;
    }

    // Call LS and pass the PROCESSES
    lotteryScheduler(total_process, totalTickets, P);

    return 0;
}


// Lottery Scheduler
void lotteryScheduler(int total_process, int totalTickets, process P[]) {
    bool cond = false;
    while(!cond) {
        int won = rand() % totalTickets;
        for(int i = 0; i < total_process; i++) {
            if(P[i].ticket_start < won && P[i].ticket_end > won && !P[i].completed) {
                cout << "\nLottery Number: " << won << " out of totalTickets: " << totalTickets << endl;
                cout << "Process " << P[i].name << " WON" << endl;
                P[i].burstTime -= TIME_QUANTUM;
                if(P[i].burstTime <= 0) {
                    cout << "Process " << P[i].name << " completed execution\n";
                    P[i].completed = true;
                }
            }
        }
        cond = true;
        for(int j = 0; j < total_process; j++) {
            if(P[j].completed == false)
                cond = false;
        }
    }
}
