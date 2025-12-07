// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  (int)(x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 400005;
const ll MOD = 1e9+7;

struct TreeStructure {
    int vertexCount;
    vector<vector<int>> neighbourList;
    int unrootedHash;
};

vector<TreeStructure> allTrees;
map<vector<int>, int> shapeMap;
vector<int> globalNodeMapping(MAX_N, 0);

int getShapeId(vector<int>& childrenHashes) {
    sort(all(childrenHashes));
    auto iterator = shapeMap.find(childrenHashes);
    if (iterator != shapeMap.end()) return iterator->second;
    int newId = size(shapeMap);
    return shapeMap[childrenHashes] = newId;
}

int getRootedHash(int nodeIndex, int parentIndex, const vector<vector<int>>& neighbourList) {
    vector<int> childrenHashes;
    for (int neighbor : neighbourList[nodeIndex]) {
        if (neighbor != parentIndex) {
            childrenHashes.push_back(getRootedHash(neighbor, nodeIndex, neighbourList));
        }
    }
    return getShapeId(childrenHashes);
}

void calculateSubtreeSizes(int nodeIndex, int parentIndex, vector<int>& subtreeSizes, const vector<vector<int>>& neighbourList) {
    subtreeSizes[nodeIndex] = 1;
    for (int neighbor : neighbourList[nodeIndex]) {
        if (neighbor != parentIndex) {
            calculateSubtreeSizes(neighbor, nodeIndex, subtreeSizes, neighbourList);
            subtreeSizes[nodeIndex] += subtreeSizes[neighbor];
        }
    }
}

void findCentroids(int nodeIndex, int parentIndex, int totalVertices, const vector<int>& subtreeSizes, const vector<vector<int>>& neighbourList, vector<int>& centroids) {
    bool isCentroid = true;
    for (int neighbor : neighbourList[nodeIndex]) {
        if (neighbor != parentIndex) {
            findCentroids(neighbor, nodeIndex, totalVertices, subtreeSizes, neighbourList, centroids);
            if (subtreeSizes[neighbor] > totalVertices / 2) isCentroid = false;
        }
    }
    if (totalVertices - subtreeSizes[nodeIndex] > totalVertices / 2) isCentroid = false;
    if (isCentroid) centroids.push_back(nodeIndex);
}

int getUnrootedHash(const vector<vector<int>>& neighbourList) {
    int vertexCount = size(neighbourList) - 1;
    if (vertexCount <= 0) return -1;
    if (vertexCount == 1) {
        vector<int> emptyVector;
        return getShapeId(emptyVector);
    }
    vector<int> subtreeSizes(vertexCount + 1);
    calculateSubtreeSizes(1, 0, subtreeSizes, neighbourList);
    vector<int> centroids;
    findCentroids(1, 0, vertexCount, subtreeSizes, neighbourList, centroids);
    int minHash = INT_MAX / 2;
    for (int centroid : centroids) {
        minHash = min(minHash, getRootedHash(centroid, 0, neighbourList));
    }
    return minHash;
}

int dfsPartition(int nodeIndex, int parentIndex, int targetSize, const vector<vector<int>>& neighbourList, vector<bool>& isChunkRoot, vector<int>& parentArray) {
    parentArray[nodeIndex] = parentIndex;
    int currentSize = 1;
    for (int neighbor : neighbourList[nodeIndex]) {
        if (neighbor != parentIndex) {
            int childResult = dfsPartition(neighbor, nodeIndex, targetSize, neighbourList, isChunkRoot, parentArray);
            if (childResult == -1) return -1;
            currentSize += childResult;
            if (currentSize > targetSize) return -1;
        }
    }
    if (currentSize == targetSize) {
        isChunkRoot[nodeIndex] = true;
        return 0;
    }
    return currentSize;
}

void collectChunkNodes(int nodeIndex, int parentIndex, const vector<vector<int>>& neighbourList, const vector<bool>& isChunkRoot, vector<int>& chunkNodes) {
    chunkNodes.push_back(nodeIndex);
    for (int neighbor : neighbourList[nodeIndex]) {
        if (neighbor != parentIndex && !isChunkRoot[neighbor]) {
            collectChunkNodes(neighbor, nodeIndex, neighbourList, isChunkRoot, chunkNodes);
        }
    }
}

void solveTestCase() {
    int vertexCount;
    cin >> vertexCount;
    TreeStructure currentTree;
    currentTree.vertexCount = vertexCount;
    currentTree.neighbourList.resize(vertexCount + 1);
    for (int i = 0; i < vertexCount - 1; ++i) {
        int uNode, vNode;
        cin >> uNode >> vNode;
        currentTree.neighbourList[uNode].push_back(vNode);
        currentTree.neighbourList[vNode].push_back(uNode);
    }
    currentTree.unrootedHash = getUnrootedHash(currentTree.neighbourList);
    allTrees.push_back(move(currentTree));
}

void solveAll() {
    map<int, map<int, int>> database;
    for (const auto& tree : allTrees) {
        database[tree.vertexCount][tree.unrootedHash]++;
    }
    vector<int> finalAnswers;
    vector<int> parentArray(MAX_N);
    vector<bool> isChunkRoot(MAX_N);

    for (const auto& tree : allTrees) {
        int vertexCount = tree.vertexCount;
        int currentAnswer = 0;
        vector<int> divisors;
        for (int i = 1; i * i <= vertexCount; ++i) {
            if (vertexCount % i == 0) {
                divisors.push_back(i);
                if (i * i != vertexCount) divisors.push_back(vertexCount / i);
            }
        }
        for (int divisor : divisors) {
            if (database.find(divisor) == database.end()) continue;
            
            fill(isChunkRoot.begin(), isChunkRoot.begin() + vertexCount + 1, false);
            
            int partitionResult = dfsPartition(1, 0, divisor, tree.neighbourList, isChunkRoot, parentArray);
            
            if (partitionResult == 0) {
                int commonHash = -1;
                bool isPossible = true;
                for (int i = 1; i <= vertexCount; ++i) {
                    if (isChunkRoot[i]) {
                        vector<int> chunkNodes;
                        collectChunkNodes(i, parentArray[i], tree.neighbourList, isChunkRoot, chunkNodes);
                        int m = size(chunkNodes);
                        for(int j = 0; j < m; ++j) globalNodeMapping[chunkNodes[j]] = j + 1;
                        vector<vector<int>> chunkAdjacency(m + 1);
                        for (int originalNode : chunkNodes) {
                            for (int neighbor : tree.neighbourList[originalNode]) {
                                if (globalNodeMapping[neighbor] != 0) {
                                    chunkAdjacency[globalNodeMapping[originalNode]].push_back(globalNodeMapping[neighbor]);
                                }
                            }
                        }
                        for(int j = 0; j < m; ++j) globalNodeMapping[chunkNodes[j]] = 0;
                        int chunkHash = getUnrootedHash(chunkAdjacency);
                        if (commonHash == -1) commonHash = chunkHash;
                        else if (commonHash != chunkHash) {
                            isPossible = false;
                            break;
                        }
                    }
                }
                if (isPossible) {
                     if (database[divisor].count(commonHash)) {
                        int count = database[divisor][commonHash];
                        if (divisor == vertexCount) count--;
                        currentAnswer += count;
                     }
                }
            }
        }
        finalAnswers.push_back(currentAnswer);
    }
    for (int i = 0; i < size(finalAnswers); ++i) {
        cout << finalAnswers[i] << (i == size(finalAnswers) - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    solveAll();
    return 0;
}