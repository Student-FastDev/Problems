#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;

const int MAXN = 3001;
LL DP[MAXN][MAXN];
LL K;
LL answerScore = 0;
int bitArray[MAXN][MAXN], cityArray[MAXN][MAXN];
int rootBit, rootCity;
int postOrderBit[MAXN], postOrderCity[MAXN];
int directedBitArray[MAXN][MAXN], directedCityArray[MAXN][MAXN];
int bitArraySize[MAXN], cityArraySize[MAXN];
int postOrderBitSize = 0, postOrderCitySize = 0;
int directedBitArraySize[MAXN], directedCityArraySize[MAXN];

LL modulate(LL var) {
    return var % K;
}

LL add(LL a, LL b) {
    return modulate(a + b);
}

LL multiply(LL a, LL b) {
    return modulate(a * b);
}

void depthFirstSearch(int root, int adjacencyList[MAXN][MAXN], int adjacencyListSize[MAXN], int postOrder[MAXN], int& postOrderSize, int directedGraph[MAXN][MAXN], int directedGraphSize[MAXN]) {
    stack<pair<int, int>> dfsStack;
    dfsStack.push({root, -1});

    bool visited[MAXN] = {false};
    visited[root] = true;

    while (!dfsStack.empty()) {
        auto [currentNode, parentNode] = dfsStack.top();

        bool allNeighborsVisited = true;
        for (int i = 0; i < adjacencyListSize[currentNode]; ++i) {
            int neighbor = adjacencyList[currentNode][i];
            if (neighbor != parentNode && !visited[neighbor]) {
                dfsStack.push({neighbor, currentNode});
                visited[neighbor] = true;
                directedGraph[currentNode][directedGraphSize[currentNode]++] = neighbor;
                allNeighborsVisited = false;
                break;
            }
        }

        if (allNeighborsVisited) {
            dfsStack.pop();
            if (adjacencyListSize[currentNode] > 1 || currentNode == root) {
                postOrder[postOrderSize++] = currentNode;
            }
        }
    }
}

void calculateDP(int current, int target, int cityArray[MAXN][MAXN], int cityArraySize[MAXN], int bitArray[MAXN][MAXN], int bitArraySize[MAXN], int postOrder[MAXN], int postOrderSize) {
    for (int i = 0; i < postOrderSize; ++i) {
        int node = postOrder[i];
        if (bitArraySize[node] >= cityArraySize[current]) {
            DP[current][node] = 0;
        } else if (bitArraySize[node] == 1 && cityArraySize[current] == 2) {
            int firstVertex = bitArray[node][0];
            int secondVertex = (cityArray[current][0] == target ? cityArray[current][1] : cityArray[current][0]);

            DP[current][node] = modulate(DP[secondVertex][firstVertex]);
        } else if (bitArraySize[node] == 1 && cityArraySize[current] == 3) {
            int firstVertex = bitArray[node][0];
            int secondVertex = (cityArray[current][0] == target ? cityArray[current][2] : cityArray[current][0]);
            int thirdVertex = (cityArray[current][1] == target ? cityArray[current][2] : cityArray[current][1]);

            DP[current][node] = add(DP[secondVertex][firstVertex], DP[thirdVertex][firstVertex]);
        }
        else if (bitArraySize[node] == 2 && cityArraySize[current] == 3) {
            int firstVertex = bitArray[node][0];
            int secondVertex = bitArray[node][1];
            int thirdVertex = (cityArray[current][0] == target ? cityArray[current][2] : cityArray[current][0]);
            int fourthVertex = (cityArray[current][1] == target ? cityArray[current][2] : cityArray[current][1]);

            DP[current][node] = add(multiply(DP[thirdVertex][firstVertex], DP[fourthVertex][secondVertex]),
                                    multiply(DP[thirdVertex][secondVertex], DP[fourthVertex][firstVertex]));
        }
        DP[current][node] = modulate(DP[current][node]);
    }
}

void rerootFunction(int current, int target, int cityArray[MAXN][MAXN], int cityArraySize[MAXN], int bitArray[MAXN][MAXN], int bitArraySize[MAXN], int postOrder[MAXN], int postOrderSize) {
    calculateDP(current, target, cityArray, cityArraySize, bitArray, bitArraySize, postOrder, postOrderSize);

    for (int i = 0; i < postOrderSize; ++i) {
        int node = postOrder[i];
        DP[target][node] = 0;
        if (bitArraySize[node] > cityArraySize[target]) {
            DP[target][node] = 0;
            continue;
        } else if (bitArraySize[node] == 1 && cityArraySize[target] == 1) {
            DP[target][node] = modulate(DP[cityArray[target][0]][bitArray[node][0]]);
        } else if (bitArraySize[node] == 1 && cityArraySize[target] == 2) {
                int firstVertex = bitArray[node][0];
                int city1 = cityArray[target][0];
                int city2 = cityArray[target][1];

                DP[target][node] = add(DP[city1][firstVertex], DP[city2][firstVertex]);
        } else if (bitArraySize[node] == 1 && cityArraySize[target] == 3) {
            int city1 = cityArray[target][0];
            int city2 = cityArray[target][1];
            int city3 = cityArray[target][2];
            int singleVertex = bitArray[node][0];

            DP[target][node] = add(add(DP[city1][singleVertex], DP[city2][singleVertex]), DP[city3][singleVertex]);
        } else if (bitArraySize[node] == 2 && cityArraySize[target] == 2) {
            int firstVertex = bitArray[node][0];
            int secondVertex = bitArray[node][1];
            int city1 = cityArray[target][0];
            int city2 = cityArray[target][1];

            DP[target][node] = add(multiply(DP[city1][firstVertex], DP[city2][secondVertex]),
                                   multiply(DP[city1][secondVertex], DP[city2][firstVertex]));
        } else if (bitArraySize[node] == 2 && cityArraySize[target] == 3) {
            int firstVertex = bitArray[node][0];
            int secondVertex = bitArray[node][1];
            int city1 = cityArray[target][0];
            int city2 = cityArray[target][1];
            int city3 = cityArray[target][2];

            DP[target][node] = add(multiply(DP[city1][firstVertex], DP[city2][secondVertex]),
                                   multiply(DP[city1][secondVertex], DP[city2][firstVertex]));

            DP[target][node] = add(DP[target][node], add(multiply(DP[city1][firstVertex], DP[city3][secondVertex]),
                                                         multiply(DP[city1][secondVertex], DP[city3][firstVertex])));

            DP[target][node] = add(DP[target][node], add(multiply(DP[city2][firstVertex], DP[city3][secondVertex]),
                                                         multiply(DP[city2][secondVertex], DP[city3][firstVertex])));
        }
        DP[target][node] = modulate(DP[target][node]);
    }
}

void calculateResult(int currentNode, int parentNode, int bitArray[MAXN][MAXN], int bitArraySize[MAXN], int cityArray[MAXN][MAXN], int cityArraySize[MAXN], int postOrderBit[MAXN], int postOrderBitSize, int rootBit) {
    for (int i = 0; i < cityArraySize[currentNode]; ++i) {
        int neighbor = cityArray[currentNode][i];
        if (neighbor == parentNode) continue;

        rerootFunction(currentNode, neighbor, cityArray, cityArraySize, bitArray, bitArraySize, postOrderBit, postOrderBitSize);
        calculateResult(neighbor, currentNode, bitArray, bitArraySize, cityArray, cityArraySize, postOrderBit, postOrderBitSize, rootBit);
        answerScore = add(answerScore, DP[neighbor][rootBit]);
        rerootFunction(neighbor, currentNode, cityArray, cityArraySize, bitArray, bitArraySize, postOrderBit, postOrderBitSize);
    }
}

void initializeDP(int N, int M) {
    memset(DP, 0, sizeof(DP));
}

void readInput(int& N, int& M, int bitArray[MAXN][MAXN], int bitArraySize[MAXN], int cityArray[MAXN][MAXN], int cityArraySize[MAXN]) {
    cin >> N >> M >> K;

    for (int i = 0; i < N - 1; ++i) {
        int firstVertex, secondVertex;
        cin >> firstVertex >> secondVertex;
        firstVertex--; secondVertex--;
        bitArray[firstVertex][bitArraySize[firstVertex]++] = secondVertex;
        bitArray[secondVertex][bitArraySize[secondVertex]++] = firstVertex;
    }
    for (int i = 0; i < M - 1; ++i) {
        int firstVertex, secondVertex;
        cin >> firstVertex >> secondVertex;
        firstVertex--; secondVertex--;
        cityArray[secondVertex][cityArraySize[secondVertex]++] = firstVertex;
        cityArray[firstVertex][cityArraySize[firstVertex]++] = secondVertex;
    }
}

void findRoots(int N, int M, int bitArray[MAXN][MAXN], int bitArraySize[MAXN], int cityArray[MAXN][MAXN], int cityArraySize[MAXN], int& rootBit, int& rootCity) {
    bool foundRoot = true;
    for (int i = 0; i < N; ++i) {
        if (bitArraySize[i] < 3 && foundRoot) {
            rootBit = i;
            foundRoot = false;
            continue;
        }
        if (bitArraySize[i] == 1) {
            for (int j = 0; j < M; ++j) {
                DP[j][i] = 1;
            }
        }
    }

    for (int i = 0; i < M; ++i) {
        if (cityArraySize[i] < 3) {
            rootCity = i;
            break;
        }
    }
}

void processNodes(int rootBit, int rootCity, int postOrderBit[MAXN], int postOrderBitSize, int postOrderCity[MAXN], int postOrderCitySize, int directedBitArray[MAXN][MAXN], int directedBitArraySize[MAXN], int directedCityArray[MAXN][MAXN], int directedCityArraySize[MAXN]) {
    for (int i = 0; i < postOrderBitSize; ++i) {
        int bitNode = postOrderBit[i];
        for (int j = 0; j < postOrderCitySize; ++j) {
            int cityNode = postOrderCity[j];
            if (directedBitArraySize[bitNode] > directedCityArraySize[cityNode]) continue;

            if (directedBitArraySize[bitNode] == 2 && directedCityArraySize[cityNode] == 2) {
                int firstVertex = directedBitArray[bitNode][0];
                int secondVertex = directedBitArray[bitNode][1];
                int city1 = directedCityArray[cityNode][0];
                int city2 = directedCityArray[cityNode][1];

                DP[cityNode][bitNode] = add(multiply(DP[city1][firstVertex], DP[city2][secondVertex]),
                                            multiply(DP[city1][secondVertex], DP[city2][firstVertex]));
            } else if (directedBitArraySize[bitNode] == 1 && directedCityArraySize[cityNode] == 2) {
                DP[cityNode][bitNode] = add(DP[directedCityArray[cityNode][0]][directedBitArray[bitNode][0]],
                                            DP[directedCityArray[cityNode][1]][directedBitArray[bitNode][0]]);
            } else if (directedBitArraySize[bitNode] == 1 && directedCityArraySize[cityNode] == 1) {
                DP[cityNode][bitNode] = modulate(DP[directedCityArray[cityNode][0]][directedBitArray[bitNode][0]]);
            }

            if (bitNode == rootBit && cityNode == rootCity) {
                answerScore = add(answerScore, DP[cityNode][bitNode]);
            }
        }
    }
}

bool handleEdgeCases(int N, int M) {
    if (N == 0 || M == 0) {
        cout << 0 << endl;
        return true;
    }
    if (N == 1) {
        cout << modulate(M) << endl;
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    readInput(N, M, bitArray, bitArraySize, cityArray, cityArraySize);
    initializeDP(N, M);
    if (handleEdgeCases(N, M)) return 0;

    findRoots(N, M, bitArray, bitArraySize, cityArray, cityArraySize, rootBit, rootCity);
    depthFirstSearch(rootBit, bitArray, bitArraySize, postOrderBit, postOrderBitSize, directedBitArray, directedBitArraySize);
    depthFirstSearch(rootCity, cityArray, cityArraySize, postOrderCity, postOrderCitySize, directedCityArray, directedCityArraySize);
    processNodes(rootBit, rootCity, postOrderBit, postOrderBitSize, postOrderCity, postOrderCitySize, directedBitArray, directedBitArraySize, directedCityArray, directedCityArraySize);
    calculateResult(rootCity, rootCity, directedBitArray, directedBitArraySize, cityArray, cityArraySize, postOrderBit, postOrderBitSize, rootBit);

    cout << modulate(answerScore) << endl;
}
