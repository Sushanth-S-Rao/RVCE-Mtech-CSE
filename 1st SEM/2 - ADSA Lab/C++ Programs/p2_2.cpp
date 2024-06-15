
// (ii)  Reverse  the  contents  of  a  List  using  List  ADT

#include<iostream>
#include<list>
#include<chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    list<int> l;
    int n, value;
    cout << "Enter the total elements that are in the list: ";
    cin >> n;

    cout << "\nEnter the elements: ";
    while(n) {
        cin >> value;
        l.push_back(value);
        n--;
    }
    
    
    cout << "\nOriginal List: ";
    for(int n : l)
        cout << n << "\t";

    // REVERSING using reverse() method on List ADT
    l.reverse();

    cout << "\nReversed List: ";
    for(int n : l)
        cout << n << "\t";
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
    
    return 0;
}