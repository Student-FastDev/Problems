// Catling
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  (int)(x).size()

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OrderedSet;

const int MAX_FRIENDS = 100005;
const int MAX_NODES = 8000005; 

struct PersistentNode {
    ll sum;
    int leftChild, rightChild;
};

PersistentNode persistentTreeNodes[MAX_NODES];
int rootVersions[MAX_FRIENDS];
int nodeCounter = 0;

struct PersistentSegmentTree {
    int buildTree(int l, int r) {
        int uniqueNumber = ++nodeCounter;
        persistentTreeNodes[uniqueNumber].sum = 0;
        if (l == r) {
            persistentTreeNodes[uniqueNumber].leftChild = persistentTreeNodes[uniqueNumber].rightChild = 0;
            return uniqueNumber;
        }
        int middleValue = (l + r) / 2;
        persistentTreeNodes[uniqueNumber].leftChild = buildTree(l, middleValue);
        persistentTreeNodes[uniqueNumber].rightChild = buildTree(middleValue + 1, r);
        return uniqueNumber;
    }

    int updateTree(int previousNode, int l, int r, int index, ll value) {
        int uniqueNumber = ++nodeCounter;
        persistentTreeNodes[uniqueNumber] = persistentTreeNodes[previousNode];
        persistentTreeNodes[uniqueNumber].sum += value;
        
        if (l == r) return uniqueNumber;
        
        int middleValue = (l + r) / 2;
        if (index <= middleValue)
            persistentTreeNodes[uniqueNumber].leftChild = updateTree(persistentTreeNodes[previousNode].leftChild, l, middleValue, index, value);
        else
            persistentTreeNodes[uniqueNumber].rightChild = updateTree(persistentTreeNodes[previousNode].rightChild, middleValue + 1, r, index, value);
        return uniqueNumber;
    }

    ll queryTree(int node, int l, int r, int index) {
        if (index < l) return 0;
        if (r <= index) return persistentTreeNodes[node].sum;
        
        int middleValue = (l + r) / 2;
        ll finalResult = queryTree(persistentTreeNodes[node].leftChild, l, middleValue, index);
        
        if (index > middleValue) finalResult += queryTree(persistentTreeNodes[node].rightChild, middleValue + 1, r, index);
        return finalResult;
    }
} pst;

struct MergeSortTree {
    vector<int> treeData[4 * MAX_FRIENDS];
    int* friendLocations;

    void buildTree(int node, int l, int r, int* locations) {
        friendLocations = locations;
        if (l == r) {
            treeData[node].push_back(friendLocations[l]);
            return;
        }
        int middleValue = (l + r) / 2;
        buildTree(node * 2, l, middleValue, locations);
        buildTree(node * 2 + 1, middleValue + 1, r, locations);
        
        merge(all(treeData[node * 2]), all(treeData[node * 2 + 1]), back_inserter(treeData[node]));
    }

    int queryGreater(int node, int l, int r, int left, int right, int value) {
        if (left > r || right < l) return 2e9; 
        if (left <= l && r <= right) {
            auto iterator = upper_bound(all(treeData[node]), value);
            if (iterator == treeData[node].end()) return 2e9;
            return *iterator;
        }
        int middleValue = (l + r) / 2;
        return min(queryGreater(node * 2, l, middleValue, left, right, value), queryGreater(node * 2 + 1, middleValue + 1, r, left, right, value));
    }

    int queryLess(int node, int l, int r, int left, int right, int value) {
        if (left > r || right < l) return -1;
        if (left <= l && r <= right) {
            auto iterator = upper_bound(all(treeData[node]), value);
            if (iterator == treeData[node].begin()) return -1;
            return *prev(iterator);
        }
        int middleValue = (l + r) / 2;
        return max(queryLess(node * 2, l, middleValue, left, right, value), queryLess(node * 2 + 1, middleValue + 1, r, left, right, value));
    }
} mergeSortTree;

int N;
ll M;
int Q;
int friendLocations[MAX_FRIENDS];
ll baseDistances[MAX_FRIENDS];
vector<int> coordinateMap;

int getCoordinateIndex(int value) {
    return (int)(lower_bound(all(coordinateMap), value) - coordinateMap.begin());
}

ll safeModulo(ll x, ll m) {
    return (x % m + m) % m;
}

void solveTestCase() {
    cin >> N >> M >> Q;

    coordinateMap.clear();
    for (int i = 0; i < N; ++i) {
        cin >> friendLocations[i];
        coordinateMap.push_back(friendLocations[i]);
    }
    coordinateMap.push_back(0);
    sort(all(coordinateMap));
    coordinateMap.erase(unique(all(coordinateMap)), coordinateMap.end());
    
    int coordinateMapSize = size(coordinateMap);

    rootVersions[0] = pst.buildTree(0, coordinateMapSize - 1);
    baseDistances[0] = 0;
    
    int currentRoot = rootVersions[0];

    for (int i = 0; i < N - 1; ++i) {
        int U = friendLocations[i];
        int V = friendLocations[i+1];
        
        ll directDistance = abs((ll)U - (ll)V);
        ll shortestDistance = min(directDistance, M - directDistance);
        baseDistances[i+1] = baseDistances[i] + shortestDistance;
        
        ll penaltyWeight = M - 2 * shortestDistance;
        
        bool directIsShortest = (directDistance <= M - directDistance);
        int minCity = min(U, V);
        int maxCity = max(U, V);
        
        int nextRoot = currentRoot;
        
        if (directIsShortest) {
            int indexLeft = getCoordinateIndex(minCity);
            int indexRight = getCoordinateIndex(maxCity);
            
            nextRoot = pst.updateTree(nextRoot, 0, coordinateMapSize - 1, indexLeft, penaltyWeight);
            if (indexRight < coordinateMapSize) nextRoot = pst.updateTree(nextRoot, 0, coordinateMapSize - 1, indexRight, -penaltyWeight);
        } else {
            int indexMaximum = getCoordinateIndex(maxCity);
            nextRoot = pst.updateTree(nextRoot, 0, coordinateMapSize - 1, indexMaximum, penaltyWeight);
            
            int indexZero = getCoordinateIndex(0);
            int indexMinimum = getCoordinateIndex(minCity);
            nextRoot = pst.updateTree(nextRoot, 0, coordinateMapSize - 1, indexZero, penaltyWeight);
            if (indexMinimum < coordinateMapSize) nextRoot = pst.updateTree(nextRoot, 0, coordinateMapSize - 1, indexMinimum, -penaltyWeight);
        }
        rootVersions[i+1] = nextRoot;
        currentRoot = nextRoot;
    }

    mergeSortTree.buildTree(1, 0, N - 1, friendLocations);

    OrderedSet blockedEdges;
    ll lastResultX = 0;

    for (int k = 0; k < Q; ++k) {
        int type;
        cin >> type;
        if (type == 1) {
            ll Y;
            cin >> Y;
            int blockedEdgeIndex = (int)safeModulo(lastResultX + Y, M);
            
            if (blockedEdges.find(blockedEdgeIndex) != blockedEdges.end()) blockedEdges.erase(blockedEdgeIndex);
            else blockedEdges.insert(blockedEdgeIndex);
        } else {
            ll Y, Z;
            cin >> Y >> Z;
            int friendA = (int)safeModulo(lastResultX + Y, N);
            int friendB = (int)safeModulo(lastResultX + Z, N);
            
            if (friendA > friendB) swap(friendA, friendB);
            
            if (blockedEdges.empty()) {
                lastResultX = baseDistances[friendB] - baseDistances[friendA];
            } else {
                int edgeCut = *blockedEdges.begin();
                
                int firstMinimum = mergeSortTree.queryGreater(1, 0, N - 1, friendA, friendB, edgeCut);
                int firstMaximum = mergeSortTree.queryLess(1, 0, N - 1, friendA, friendB, 2e9);
                
                int secondMinimum = mergeSortTree.queryGreater(1, 0, N - 1, friendA, friendB, -1);
                int secondMaximum = mergeSortTree.queryLess(1, 0, N - 1, friendA, friendB, edgeCut);
                
                bool g1Exists = (firstMinimum != 2e9);
                bool g2Exists = (secondMaximum != -1);
                
                bool isPossible = true;
                
                if (g1Exists && g2Exists) {
                    int firstC = (int)(size(blockedEdges) - blockedEdges.order_of_key(firstMinimum));
                    int secondC = (int)blockedEdges.order_of_key(secondMaximum);
                    
                    if (firstC + secondC > 0) isPossible = false;
                } else if (g1Exists) {
                    int currentLimit = firstMaximum; 
                    int C = (int)(blockedEdges.order_of_key(currentLimit) - blockedEdges.order_of_key(firstMinimum));
                    if (C > 0) isPossible = false;
                } else {
                    int currentStart = secondMinimum;
                    int C = (int)(blockedEdges.order_of_key(secondMaximum) - blockedEdges.order_of_key(currentStart));
                    if (C > 0) isPossible = false;
                }
                
                if (!isPossible) {
                    lastResultX = -1;
                } else {
                    ll baseCost = baseDistances[friendB] - baseDistances[friendA];
                    
                    auto iterator = upper_bound(all(coordinateMap), edgeCut);
                    int queryIndex = (int)(iterator - coordinateMap.begin()) - 1;
                    
                    ll penaltyCorrection = 0;
                    if (queryIndex >= 0) {
                        ll valueB = pst.queryTree(rootVersions[friendB], 0, coordinateMapSize - 1, queryIndex);
                        ll valueA = pst.queryTree(rootVersions[friendA], 0, coordinateMapSize - 1, queryIndex);
                        penaltyCorrection = valueB - valueA;
                    }
                    
                    lastResultX = baseCost + penaltyCorrection;
                }
            }
            cout << lastResultX << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
