// Levenshtein distance

#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

// Returns the Levenshtein distance between word1 and word2.
int levenshteinDist(string word1, string word2) {
    int size1 = word1.size();
    int size2 = word2.size();
    int verif[size1 + 1][size2 + 1]; // Verification matrix i.e. 2D array which will store the calculated distance.

    // If one of the words has zero length, the distance is equal to the size of the other word.
    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;

    // Sets the first row and the first column of the verification matrix with the numerical order from 0 to the length of each word.
    for (int i = 0; i <= size1; i++)
        verif[i][0] = i;
    for (int j = 0; j <= size2; j++)
        verif[0][j] = j;

    // Verification step / matrix filling.
    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            // Sets the modification cost.
            // 0 means no modification (i.e. equal letters) and 1 means that a modification is needed (i.e. unequal letters).
            int cost = (word2[j - 1] == word1[i - 1]) ? 0 : 1;

            // Sets the current position of the matrix as the minimum value between a (deletion), b (insertion) and c (substitution).
            // a = the upper adjacent value plus 1: verif[i - 1][j] + 1
            // b = the left adjacent value plus 1: verif[i][j - 1] + 1
            // c = the upper left adjacent value plus the modification cost: verif[i - 1][j - 1] + cost
            verif[i][j] = min(
                                min(verif[i - 1][j] + 1, verif[i][j - 1] + 1),
                                    verif[i - 1][j - 1] + cost
                             );
        }
    }

    // The last position of the matrix will contain the Levenshtein distance.
    return verif[size1][size2];
}

int main() {
    string word1, word2;
    vector<string> listA = {"Accenture", "Adobe", "Akamai", "Alexandria  Real  Estates", "Biotech", "Catamarine", "Cisco  Systems"};
    vector<string> listB = {"Accent lluxre", "Addobbe", ".", "Alexandira Reel Estates", "Biotec", "Catamaine", "Cisc  Systm"};
    /*
    cout << "Please input the first word: " << endl; cin >> word1;
    cout << "Please input the second word: " << endl; cin >> word2;
    */
    for(int i = 0; i < listA.size(); i++) {
        cout << "The no of modifications needed for: " << listA[i] << " to make it: " << listB[i] << "is (Levenshtein distance) = " << levenshteinDist(listA[i], listB[i]) << endl;
    }
    system("pause");
    return 0;
}