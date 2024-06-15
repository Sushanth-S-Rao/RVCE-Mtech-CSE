// Hot Potato

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<chrono>
using namespace std;

void hotPotato(vector<string> &list, int num);

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<string> nameList = {"Bill","David","Susan","Jane","Kent","Brad"};
    int num = 7;
    
    hotPotato(nameList, num);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
    return 0;
}

void hotPotato(vector<string> &list, int num) {
    queue<string> q;
    for(string names : list) {
        q.push(names);
    }

    while(q.front() != q.back()) {
        // Pass the BALL num times
        for(int i = 0; i < num; i++) {
            string hasBall = q.front();
            q.pop();
            q.push(hasBall);
        }
        // Eliminate the user with the ball
        q.pop();
    }
    
    cout << "The winner is: " << q.front() << endl;
}