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
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

const int BLOCK_SIZE = 500;
const int MAX_BLOCKS = 450;
const int MAX_VAL = 100005;

vector<int> blockVectorArray[MAX_BLOCKS];
int frequencyTable[MAX_BLOCKS][MAX_VAL];
int numberOfBlocks;
int N;

void rebuildBlocks() {
    vector<int> newBlockVectorArray[MAX_BLOCKS];
    int globalIndex = 0;
    
    for (int i = 0; i < numberOfBlocks; ++i) {
        for (int value : blockVectorArray[i]) {
            int newBlockIndex = globalIndex / BLOCK_SIZE;
            newBlockVectorArray[newBlockIndex].push_back(value);
            if (i != newBlockIndex) {
                frequencyTable[i][value]--;
                frequencyTable[newBlockIndex][value]++;
            }
            globalIndex++;
        }
        blockVectorArray[i].clear();
    }
    
    numberOfBlocks = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < numberOfBlocks; ++i) {
        blockVectorArray[i] = move(newBlockVectorArray[i]);
    }
}

pii findBlockLocation(int targetIndex) {
    for (int i = 0; i < numberOfBlocks; ++i) {
        if (targetIndex < (int)size(blockVectorArray[i])) {
            return {i, targetIndex};
        }
        targetIndex -= size(blockVectorArray[i]);
    }
    return {-1, -1};
}

void solveTestCase() {
    cin >> N;
    numberOfBlocks = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;
    
    for (int i = 0; i < N; ++i) {
        int value;
        cin >> value;
        int blockId = i / BLOCK_SIZE;
        blockVectorArray[blockId].push_back(value);
        frequencyTable[blockId][value]++;
    }
    
    int Q;
    cin >> Q;
    int lastAnswer = 0;
    int queriesSinceRebuild = 0;
    
    while (Q--) {
        int queryType;
        cin >> queryType;
        int L, R, K;
        cin >> L >> R;
        L = ((L + lastAnswer - 1) % N) + 1;
        R = ((R + lastAnswer - 1) % N) + 1;
        if (L > R) swap(L, R);
        
        if (queryType == 1) {
            if (L == R) continue;
            
            pii positionR = findBlockLocation(R - 1);
            int value = blockVectorArray[positionR.first][positionR.second];
            
            blockVectorArray[positionR.first].erase(blockVectorArray[positionR.first].begin() + positionR.second);
            frequencyTable[positionR.first][value]--;
            
            int currentIndex = L - 1;
            int insertBlockIndex = 0, insertOffset = 0;
            for (int i = 0; i < numberOfBlocks; ++i) {
                if (currentIndex <= (int)size(blockVectorArray[i])) {
                    insertBlockIndex = i;
                    insertOffset = currentIndex;
                    break;
                }
                currentIndex -= size(blockVectorArray[i]);
            }
            
            blockVectorArray[insertBlockIndex].insert(blockVectorArray[insertBlockIndex].begin() + insertOffset, value);
            frequencyTable[insertBlockIndex][value]++;
            
            queriesSinceRebuild++;
            if (queriesSinceRebuild >= BLOCK_SIZE) {
                rebuildBlocks();
                queriesSinceRebuild = 0;
            }
            
        } else {
            cin >> K;
            K = ((K + lastAnswer - 1) % N) + 1;
            
            int currentL = L - 1;
            int currentR = R - 1;
            int answer = 0;
            
            int startBlockIndex = -1, startOffset = -1;
            int endBlockIndex = -1, endOffset = -1;
            
            int tempIndex = currentL;
            for (int i = 0; i < numberOfBlocks; ++i) {
                if (tempIndex < (int)size(blockVectorArray[i])) {
                    startBlockIndex = i;
                    startOffset = tempIndex;
                    break;
                }
                tempIndex -= size(blockVectorArray[i]);
            }
            
            tempIndex = currentR;
            for (int i = 0; i < numberOfBlocks; ++i) {
                if (tempIndex < (int)size(blockVectorArray[i])) {
                    endBlockIndex = i;
                    endOffset = tempIndex;
                    break;
                }
                tempIndex -= size(blockVectorArray[i]);
            }
            
            if (startBlockIndex == endBlockIndex) {
                for (int i = startOffset; i <= endOffset; ++i) {
                    if (blockVectorArray[startBlockIndex][i] == K) answer++;
                }
            } else {
                for (int i = startOffset; i < (int)size(blockVectorArray[startBlockIndex]); ++i) {
                    if (blockVectorArray[startBlockIndex][i] == K) answer++;
                }
                for (int i = startBlockIndex + 1; i < endBlockIndex; ++i) {
                    answer += frequencyTable[i][K];
                }
                for (int i = 0; i <= endOffset; ++i) {
                    if (blockVectorArray[endBlockIndex][i] == K) answer++;
                }
            }
            
            cout << answer << endl;
            lastAnswer = answer;
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