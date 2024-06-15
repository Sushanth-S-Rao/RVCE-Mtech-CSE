
// 1) Apply an appropriate algorithmic technique to sort the genome sequence

// Algorithm: RADIX SORT (MSD)

#include<iostream>
#include<vector>
#include<map>
#include<chrono>

using namespace std;

void radixSort(vector<string> &input, int exp, vector<string> &out);

int main() {
    auto start = chrono::high_resolution_clock::now();

    vector<string> genome = {"ACG", "TCA", "GAC", "CTA", "GTT", "ATG", "AAG", "TGT", "TCC", "AAA", "CTC", "TGA", "GCG", "ACT"};
    // vector<string> genome = {"cat", "rabbit", "bat", "wolves", "fox", "cow", "hyena", "lion", "dragon"};
    vector<string> output;
    
    radixSort(genome, -1, output);
    
    cout << "The Genome Sequence (before sorting): \n";
    for(string g : genome) 
        cout << g << "\t";
    
    cout << "\n\nThe Genome Sequence (after sorting): \n";
    for(string g : output)
        cout << g << "\t"; 

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;

    return 0;
}

void radixSort(vector<string> &input, int exp, vector<string> &out) {
    map<char, vector<string>> bucket;
    exp++;

    // Create buckets based on MSD 
    for(string s : input) {
        bucket[s.at(exp)].push_back(s);
    }

    for(pair p : bucket) {
        if(p.second.size() == 1) 
            // Push the sorted string to output
            out.push_back(p.second.front());
        else {
            // RECURSIVE call to sort moving a MSD place 
            radixSort(p.second, exp, out);
        }
    }
}

// MEASURING EXECUTION Speed in C++

// Import "chrono" header file
// At the start of the program, measure the clock time "chrono::high_resolution_clock::now()"
// Measure it after taking the INPUT if you get the input manually (i.e using cin >>)
// At the end of the program, measure the clock time "chrono::high_resolution_clock::now()"
// Subtracting end and start time gives the time it took for execution, "chrono::duration_cast<chrono::microseconds>(end - start);"


//-------------------------------------------------------------------------
// Logic to radix sort values of UNEVEN Length (NUMBERS)
// (32, 8, 4, 325)

// LSD to MSD 
// PAD with 0 => (032, 008, 004, 325)
// Sort LSD  => 032, 004, 325, 008
// Sort next => 004, 008, 325, 032 
// Sort MSD  => 004, 008, 032, 325

// MSD to LSD
// PAD with 0
// Same logic but apply from MSD to LSD


// Logic to radix sort values of UNEVEN Length (STRINGS)

// LSD to MSD
// PAD with A => (cut, Ain, cat, AAb)
// Same logic

// MSD to LSD
// No need to pad, but create BUCKETS for each radix, and recursively sort
// (cut, in, cat, can, b)
// Sort with MSD
// ({b}, {in}, {cut, cat, can})
// Sort the 3 BUCKETS by taking 2nd MSD
// {cut, cat, can} => {[cat, can], [cut]}
// Sort the 2 BUCKETS by taking 3rd MSD
// [cat, can] => {[can], [cat]}
// Concatenate the buckets to get final result
// (b, in can, cat, cut)

