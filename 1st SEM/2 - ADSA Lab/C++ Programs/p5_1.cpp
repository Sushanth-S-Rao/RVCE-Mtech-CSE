
// Simple QUICK Sort

#include<iostream>
#include<vector>
#include<chrono>
using namespace std;

void quickSort(vector<int> &subArray, int low, int high);
int partition(vector<int> &subArray, int low, int high);

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<int> arr = {43, 55, 36, 12, 700, 5, 101};
    int low = 0, high = arr.size() - 1;
    cout << "Initial Array: \n";
    for(int a : arr)    cout << a << "\t";
    cout << "\n";

    // CALL for QUICK SORT
    quickSort(arr, low, high);

    cout << "\n\nFinal QUICK SORTED Array: \n";
    for(int b : arr)    cout << b << "\t";
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
    return 0;
}

void quickSort(vector<int> &subArray, int low, int high) {
    if(low < high) {
        int pivot = partition(subArray, low, high);

        // RECURSIVELY Sort LEFT side of PIVOT
        quickSort(subArray, low, pivot - 1);

        // RECURSIVELY Sort RIGHT side of PIVOT
        quickSort(subArray, pivot + 1, high);
    }
}

int partition(vector<int> &subArray, int low, int high) {
    int quickPivot = subArray[high];
    int index = low - 1;
    for(int i = low; i < high; i++) {
        if(subArray[i] < quickPivot) {
            index++;
            swap(subArray[i], subArray[index]);
        }
    }

    // Put PIVOT Element at its CORRECT Place
    int pivot = index + 1;
    swap(subArray[pivot], subArray[high]);

    cout << "\n";
    for(int j = 0; j < pivot; j++)  cout << subArray[j] << "\t";
    cout << "(" << subArray[pivot] << ")\t"; 
    for(int j = pivot + 1; j < subArray.size(); j++)  cout << subArray[j] << "\t";

    // RETURN the index of PIVOT Element
    return pivot;
}