#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5+1;
const ll INF = 1e18;
const int MOD = 1e9+7;

vector<pair<int, int>> neighbourList[MAX_N];

void addEdge(int A, int B, int W) {
    neighbourList[A].push_back({B, W});
    neighbourList[B].push_back({A, W});
}

void restorePath(int S, int T, vector<int> const& predecessorArray) {
    vector<int> pathArray;

    for (int i = T; i != S; i = predecessorArray[i]) {
        pathArray.push_back(i);
    }
    pathArray.push_back(S);

    reverse(pathArray.begin(), pathArray.end());
    
    cout << pathArray.size() << endl;
    for (auto i : pathArray) {
        cout << i << " ";
    }
    cout << endl;
}

void dijkstraAlgorithm(int S, vector<ll>& distanceArray, vector<int>& predecessorArray, int E) {
    distanceArray.assign(MAX_N, INF);
    predecessorArray.assign(MAX_N, -1);
    
    distanceArray[S] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pQueue;
    pQueue.push({0, S});
    
    while (!pQueue.empty()) {
        int vertexNumber = pQueue.top().second;
        ll vertexDistance = pQueue.top().first;
        pQueue.pop();
        
        if (vertexDistance != distanceArray[vertexNumber]) {
            continue;
        }
        
        for (auto edgeVariable : neighbourList[vertexNumber]) {
            int toVariable = edgeVariable.first;
            int lenVariable = edgeVariable.second;
            
            if (distanceArray[vertexNumber] + lenVariable < distanceArray[toVariable]) {
                distanceArray[toVariable] = distanceArray[vertexNumber] + lenVariable;
                predecessorArray[toVariable] = vertexNumber;
                pQueue.push({distanceArray[toVariable], toVariable});
            }
        }
    }
    
    if (distanceArray[E] == INF) {
        cout << "-1" << endl;
        return;
    } else {
        cout << distanceArray[E] << " ";
        restorePath(S, E, predecessorArray);
    }
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    
    int N, M, S, T;
    cin >> N >> M >> S >> T;
    
    vector<ll> distanceArray;
    vector<int> predecessorArray;

    for (int i = 0; i < M; i++) {
        int A, B, W;
        cin >> A >> B >> W;
        
        addEdge(A, B, W);
    }
    
    dijkstraAlgorithm(S, distanceArray, predecessorArray, T);

    return 0;
}
