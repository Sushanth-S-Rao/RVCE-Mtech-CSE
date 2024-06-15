
// Using  suitable  Abstract  Data  Types  (ADTs)  perform  the  following  tasks:

// (i)  Checking  if  the  parentheses  are  well  formed  i.e.  [  (  )  (  )  ]  is  well-formed,  but  [  (  (  ]  )  ) is  not.

#include<iostream>
#include<bits\stdc++.h>
#include<chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now();
    string parentheses;
    cout << "Enter the Parentheses: ";
    cin >> parentheses;

    stack<char> s;
    for(char c : parentheses) {
        // Handling Exceptional Cases
        if(c != '(' && c != ')' && c != '{' && c != '}' && c != '[' && c != ']') {
            cout << "Please enter only the parentheses. No WHITE space or other characters allowed. Exiting...";
            exit;
        }

        if(c == '(' || c == '{' || c == '[') {
            s.push(c);
        }
        else {
            if(s.empty()) {
                cout << "Parentheses is not Balanced, since there's no opening for " << c;
                return 1;
            }
            char t = s.top();
            s.pop();
            
            if(c == ')' && t!= '(') {
                cout << "Parentheses is Not Balanced for ) \n";
                return 1;
            }

            else if(c == '}' && t!= '{') {
                cout << "Parentheses is Not Balanced for } \n";
                return 1;
            }

            else if(c == ']' && t != '[') {
                cout << "Parentheses is Not Balanced for ] \n";
                return 1;
            }
        }

        
    }
    if(s.empty())
        cout << "Parentheses is Balanced --";
    else 
        cout << "Parentheses is not Balanced, since there's no closing for " << s.top();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\n\nExecution time: " << duration.count() << " ms" << endl;
    return 0;
}