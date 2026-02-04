// Catling
#include <bits/stdc++.h>
#include "caplib.h"
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define size(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define endl '\n'

const ll MOD = 1e9 + 7;
const int MAX_N = 5e3 + 67;
const ll INF = 1e9 + 67;

vector<int> neighbourList[MAX_N];
int parentArray[MAX_N];
int timeIn[MAX_N];
int timeOut[MAX_N];
int timeCounter;
int subtreeWeight[MAX_N];

void initializeDFS(int node, int parent) {
    timeIn[node] = ++timeCounter;
    parentArray[node] = parent;

    for(auto u : neighbourList[node]) {
        if(u != parent) initializeDFS(u, node);
    }
    timeOut[node] = timeCounter;
}

bool isAncestor(int u, int v) {
    return timeIn[u] <= timeIn[v] && timeOut[v] <= timeOut[u];
}

void calculateDFS(int node, vector<bool>& isCandidate) {
    subtreeWeight[node] = (isCandidate[node] ? 1 : 0);
    for(auto u : neighbourList[node]) {
        if(u != parentArray[node]) {
            calculateDFS(u, isCandidate); 
            subtreeWeight[node] += subtreeWeight[u];
        }
    }
}

int znajdz_capka(int n, vector<pii> galezie) {
    for(int i = 0; i <= n; i++) neighbourList[i].clear();
    for(auto edge : galezie) {
        neighbourList[edge.first].push_back(edge.second);
        neighbourList[edge.second].push_back(edge.first);
    }

    timeCounter = 0;
    initializeDFS(1, 0);
    
    vector<int> candidatesArray; 
    for(int i = 1; i <= n; i++) candidatesArray.push_back(i);
    
    vector<bool> isCandidate(n + 1);

    while(size(candidatesArray) > 1) {
        fill(all(isCandidate), 0);
        for(auto c : candidatesArray) isCandidate[c] = 1;
        
        calculateDFS(1, isCandidate);

        int totalCandidates = size(candidatesArray);
        int bestVertex = -1;
        int minimumDifference = INF;

        for(int v = 2; v <= n; v++) {
            if(subtreeWeight[v] == 0) continue;
            int differenceValue = abs(totalCandidates - 2 * subtreeWeight[v]);
            if(differenceValue < minimumDifference) {
                minimumDifference = differenceValue;
                bestVertex = v;
            }
        }

        if(bestVertex == -1) {
            return candidatesArray[0];
        }

        int queryResponse = zapytaj(bestVertex);
        
        vector<int> nextCandidates; 
        
        if(queryResponse == 1) {
            for(auto c : candidatesArray) {
                if(isAncestor(bestVertex, c)) {
                    nextCandidates.push_back(c);
                }
            }
        } else {
            for(auto c : candidatesArray) {
                if(!isAncestor(bestVertex, c)) {
                    int nextPosition = (c == 1 ? 1 : parentArray[c]);
                    nextCandidates.push_back(nextPosition);
                }
            }
            sort(all(nextCandidates));
            nextCandidates.erase(unique(all(nextCandidates)), nextCandidates.end());
        }
        candidatesArray = nextCandidates;
    }

    return candidatesArray.empty() ? 1 : candidatesArray[0];
}
