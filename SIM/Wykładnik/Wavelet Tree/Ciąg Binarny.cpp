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
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const int MAX_NODES = 25000000;
const int MAX_N = 1000005;

struct Node {
    int leftChild, rightChild;
    int countVariable;
    ll currentSum;
} treeArray[MAX_NODES];

int rootIndices[MAX_N];
int nodePointer = 0;
vector<ll> uniqueLengths;

int buildTree(int leftRange, int rightRange) {
    int id = ++nodePointer;
    treeArray[id].countVariable = 0;
    treeArray[id].currentSum = 0;
    if (leftRange == rightRange) return id;
    int middleValue = (leftRange + rightRange) / 2;
    treeArray[id].leftChild = buildTree(leftRange, middleValue);
    treeArray[id].rightChild = buildTree(middleValue + 1, rightRange);
    return id;
}

int updateTree(int previousNode, int leftRange, int rightRange, int valueIndex, ll realValue) {
    int id = ++nodePointer;
    treeArray[id] = treeArray[previousNode];
    treeArray[id].countVariable++;
    treeArray[id].currentSum += realValue;
    if (leftRange == rightRange) return id;
    int middleValue = (leftRange + rightRange) / 2;
    if (valueIndex <= middleValue) treeArray[id].leftChild = updateTree(treeArray[previousNode].leftChild, leftRange, middleValue, valueIndex, realValue);
    else treeArray[id].rightChild = updateTree(treeArray[previousNode].rightChild, middleValue + 1, rightRange, valueIndex, realValue);
    return id;
}

ll queryKSum(int nodeLeft, int nodeRight, int rangeLeft, int rangeRight, int kLimit) {
    if (kLimit <= 0) return 0;
    int availableCount = treeArray[nodeRight].countVariable - treeArray[nodeLeft].countVariable;
    
    if (availableCount <= kLimit) return treeArray[nodeRight].currentSum - treeArray[nodeLeft].currentSum;
    
    if (rangeLeft == rangeRight) {
        ll singleValue = (treeArray[nodeRight].currentSum - treeArray[nodeLeft].currentSum) / availableCount;
        return singleValue * kLimit;
    }
    
    int middleValue = (rangeLeft + rangeRight) / 2;
    int rightCount = treeArray[treeArray[nodeRight].rightChild].countVariable - treeArray[treeArray[nodeLeft].rightChild].countVariable;
    
    if (kLimit >= rightCount) {
        return (treeArray[treeArray[nodeRight].rightChild].currentSum - treeArray[treeArray[nodeLeft].rightChild].currentSum) +
               queryKSum(treeArray[nodeLeft].leftChild, treeArray[nodeRight].leftChild, rangeLeft, middleValue, kLimit - rightCount);
    } else {
        return queryKSum(treeArray[nodeLeft].rightChild, treeArray[nodeRight].rightChild, middleValue + 1, rangeRight, kLimit);
    }
}

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;

    vector<ll> blockLengths(N + 1);
    vector<ll> prefixSums(N + 1, 0);
    
    for(int i = 1; i <= N; ++i) {
        cin >> blockLengths[i];
        prefixSums[i] = prefixSums[i-1] + blockLengths[i];
        if (i % 2 != 0) {
            uniqueLengths.push_back(blockLengths[i]);
        }
    }

    sort(uniqueLengths.begin(), uniqueLengths.end());
    uniqueLengths.erase(unique(uniqueLengths.begin(), uniqueLengths.end()), uniqueLengths.end());
    
    int M = (int)size(uniqueLengths);
    rootIndices[0] = buildTree(1, M > 0 ? M : 1);

    auto getId = [&](ll val) {
        return (int)(lower_bound(uniqueLengths.begin(), uniqueLengths.end(), val) - uniqueLengths.begin() + 1);
    };

    for(int i = 1; i <= N; ++i) {
        if (i % 2 != 0) {
            int id = getId(blockLengths[i]);
            rootIndices[i] = updateTree(rootIndices[i-1], 1, M, id, blockLengths[i]);
        } else {
            rootIndices[i] = rootIndices[i-1];
        }
    }

    for(int i = 0; i < Q; ++i) {
        ll l, r, k;
        cin >> l >> r >> k;

        int startBlockIndex = (int)(lower_bound(prefixSums.begin(), prefixSums.end(), l) - prefixSums.begin());
        int endBlockIndex = (int)(lower_bound(prefixSums.begin(), prefixSums.end(), r) - prefixSums.begin());

        ll finalAnswer = 0;

        if (startBlockIndex == endBlockIndex) {
            if (startBlockIndex % 2 != 0) {
                finalAnswer = r - l + 1;
            } else {
                finalAnswer = 0;
            }
        } else {
            ll leftChunk = 0;
            if (startBlockIndex % 2 != 0) leftChunk = prefixSums[startBlockIndex] - l + 1;
            
            ll rightChunk = 0;
            if (endBlockIndex % 2 != 0) rightChunk = r - prefixSums[endBlockIndex-1];

            int internalStartBlock = startBlockIndex; 
            int internalEndBlock = endBlockIndex - 1;
            
            auto getInternalSum = [&](int kBudget) -> ll {
                if (kBudget < 0) return -INF;
                if (kBudget == 0) return 0;
                int count = kBudget / 2;
                if (count == 0) return 0;
                return queryKSum(rootIndices[internalStartBlock], rootIndices[internalEndBlock], 1, M, count);
            };

            finalAnswer = max(finalAnswer, getInternalSum(k));

            if (startBlockIndex % 2 != 0 && k >= 1) {
                finalAnswer = max(finalAnswer, leftChunk + getInternalSum(k - 1));
            }

            if (endBlockIndex % 2 != 0 && k >= 1) {
                finalAnswer = max(finalAnswer, rightChunk + getInternalSum(k - 1));
            }

            if (startBlockIndex % 2 != 0 && endBlockIndex % 2 != 0 && k >= 2) {
                finalAnswer = max(finalAnswer, leftChunk + rightChunk + getInternalSum(k - 2));
            }
        }
        cout << finalAnswer << endl;
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
