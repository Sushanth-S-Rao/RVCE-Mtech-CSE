#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<chrono>

using namespace std;

void hashFn(vector<string> &list);

int main() {
    auto start = chrono::high_resolution_clock::now();
    vector<string> listOfWords = {"computer",  "science",  "in",  "birmingham",  "dates",  "back",  "to",  "the",  "sixties"};

    hashFn(listOfWords); 
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
}

void hashFn(vector<string> &list) {
    map<char, int> lookupTable;
    char k = 'a';

    // Lookup table that maps ALPHABETS to VALUES
    for(int i = 0; i < 26; i++) {
        lookupTable[k] = i;
        k = char(int(k) + 1);
    }

    int noOfCollisions = 0;
    map<int, string> hashTable;

    for(string word : list) {
        int num = 0;
        
        // Calcute the WEIGHT of word
        for(char letter : word) {
            num = num + lookupTable[letter];
        }
        
        // Hash Function
        num = num % 13;
    
        if(hashTable.find(num) == hashTable.end())
            hashTable[num] = word;

        // LINEAR PROBING 
        else {
            while(hashTable[num] != word) {
                num = (num - 1) % 13;
                noOfCollisions++;
                if(hashTable.find(num) == hashTable.end())
                    hashTable[num] = word;
            }
        }
    }
    cout << "No of Collisons: " << noOfCollisions << endl;

    for(pair p : hashTable) {
        cout << p.first << " : " << p.second << endl;
    }
}