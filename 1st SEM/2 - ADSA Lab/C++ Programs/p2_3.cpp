
// (iii) Use  dictionary  ADT  to  count  the  number  of  occurrences  of  each  word  in  an online  book.

#include<iostream>
#include<map>
#include<vector>
#include<chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    map<string, int> mp;
    string book;
    cout << "Enter the book transcript: ";
    getline(cin, book);

    for(int i = 0; i < book.size(); i++) {
        string word;
        while(book[i] != ' ' && i < book.size()) {
            word.push_back(book[i]);
            i++;
        }
        // Incrementing the word count for each occurence
        mp[word]++;
    }

    for(pair p : mp) {
        cout << p.first << " : " << p.second << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
    return 0;
}