/**********************************************
 * Last Name:   Situ
 * First Name:  Dennis
 * Student ID:  #30052675
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  4
 * Question:    Q6
 *
 * File name: deadlock.cpp
 *********************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

#define MAX 200000

string strlist[3];
vector<int> plocked;
vector<int> adj[MAX]; 

void addEdge(vector<int> adj[], int u, int v) { 
    adj[u].push_back(v); 
}

void splitSequence(string str) { 
    int i = 0;
    string symbol = "";
    for (auto x : str) { 
        if (x == ' ') { 
            strlist[i] = symbol;
            symbol = ""; 
            i++;
        } else { 
            symbol = symbol + x; 
        } 
    }
    strlist[2] = symbol;
} 

bool findCycle(int v, bool visited[], bool *recStack) { 
    if (visited[v] == false) { 
        visited[v] = true; 
        recStack[v] = true; 
  
        vector<int>::iterator i; 
        for (i = adj[v].begin(); i != adj[v].end(); i++) {
            if (!visited[*i] && findCycle(*i, visited, recStack) ) {
                if (v < 100000) {
                    plocked.push_back(v);
                }
                return true; 
            } else if (recStack[*i]) {
                if (v < 100000) {
                    plocked.push_back(v);
                }
                return true; 
            }
        } 
    } 
    recStack[v] = false;
    return false; 
} 

bool hasCycle() { 
    bool *visited = new bool[MAX]; 
    bool *recStack = new bool[MAX]; 
    for (int i = 0; i < MAX; i++) { 
        visited[i] = false; 
        recStack[i] = false; 
    } 
  
    for (int i = 0; i < MAX; i++) 
        if (findCycle(i, visited, recStack)) {
            return true; 
        }
    return false; 
} 

void checkDeadlock() {
    cout << "Deadlocked processes: ";
    if (!hasCycle()) {
        cout << "none";
    } else {
        std::sort(plocked.begin(), plocked.end()); 
        for (int i = 0; i < plocked.size(); i++) {
            cout << plocked[i] << " ";
        }
    }
    printf("\n");
    plocked.clear();
}

int main() {
    bool endOfFile = false;
    while (1) {
        // set graph to empty
        for (int i = 0; i < MAX; i++) {
            adj[i].clear();
        }
        string str;
        while (1) {
            getline(cin, str);
            if (str == "#" || cin.fail()) {
                if (cin.fail()) {
                    endOfFile = true;
                }
                checkDeadlock();
                break;
            } else {
                splitSequence(str);

                int arg1 = stoi(strlist[0]);
                int arg2 = stoi(strlist[2]) + 100000;

                if (strlist[1] == "->") {
                    addEdge(adj, arg1, arg2);
                } else {
                    addEdge(adj, arg2, arg1);
                }
            }
        }
        // if EOF was encountered
        if (endOfFile) {
            break;
        }
    }    
    return 0; 
}