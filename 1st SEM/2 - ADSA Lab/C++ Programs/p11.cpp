
/* Open Ended Lab Program 1: 
You are given the integer array and you have to count the frequency of each element in the array. 
This problem can be solved by using the brute force approach the time complexity will be O(N2).
Think of an appropriate data structure to solve the above problem.                                                                                 */ 

// Appropriate Data Structure: Dictionary

#include<iostream>
#include<bits/stdc++.h>
#include<chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    map<int, int> mp;
    vector<int> inpArr = {2, 3, 2, 5, 65, 23, 11, 11, 2, 5, 2, 65, 65, 65, 65, 4};
    
    // Traverse the array
    // For each element encountered, increase its count

    for(int a : inpArr) {
        if(mp.find(a) == mp.end())
            mp[a] = 1;
        else 
            mp[a]++;
    }

    // Print the number of occurences
    cout << "Element    Occurences" << endl;
    for(pair p : mp) {
        cout << p.first << " \t     " << p.second << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
    return 0;
}

