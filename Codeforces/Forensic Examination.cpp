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

struct SuffixAutomaton {
    struct State {
        int length, suffixLink;
        int transitions[26];
        State() : length(0), suffixLink(-1) { memset(transitions, -1, sizeof(transitions)); }
    };
    vector<State> states;
    int stateCount, lastState;

    SuffixAutomaton(int maxLength) {
        states.reserve(maxLength * 2);
        states.push_back(State());
        stateCount = 1;
        lastState = 0;
    }

    void extendAutomaton(char character) {
        int current = stateCount++;
        states.push_back(State());
        states[current].length = states[lastState].length + 1;
        int p = lastState;
        int code = character - 'a';
        while (p != -1 && states[p].transitions[code] == -1) {
            states[p].transitions[code] = current;
            p = states[p].suffixLink;
        }
        if (p == -1) {
            states[current].suffixLink = 0;
        } else {
            int q = states[p].transitions[code];
            if (states[p].length + 1 == states[q].length) {
                states[current].suffixLink = q;
            } else {
                int clone = stateCount++;
                states.push_back(states[q]);
                states[clone].length = states[p].length + 1;
                while (p != -1 && states[p].transitions[code] == q) {
                    states[p].transitions[code] = clone;
                    p = states[p].suffixLink;
                }
                states[q].suffixLink = states[current].suffixLink = clone;
            }
        }
        lastState = current;
    }
};

struct Query {
    int id;
    int queryLeft, queryRight;
    int moLeft, moRight;
};

int M, Q;
string S;
vector<string> leaflets;
vector<vector<int>> neighbourList;
vector<int> timeIn, timeOut;
int currentTime;
vector<int> ancestorTable[20];
vector<pair<int, int>> eventPoints;
int blockSizeMo;

const int MAX_LEAFLETS = 50005;
const int SQRT_M = 230;
int frequencyCount[MAX_LEAFLETS];
pair<int, int> blockMaxPair[MAX_LEAFLETS / SQRT_M + 5];

void addLeaflet(int leafletIndex) {
    frequencyCount[leafletIndex]++;
    int blockIndex = leafletIndex / SQRT_M;
    if (frequencyCount[leafletIndex] > blockMaxPair[blockIndex].first) {
        blockMaxPair[blockIndex] = {frequencyCount[leafletIndex], leafletIndex};
    } else if (frequencyCount[leafletIndex] == blockMaxPair[blockIndex].first) {
        if (leafletIndex < blockMaxPair[blockIndex].second) blockMaxPair[blockIndex].second = leafletIndex;
    }
}

vector<pair<int, int>> historyFrequency;
vector<pair<int, pair<int, int>>> historyBlockMax;

void addLeafletRollback(int leafletIndex) {
    int blockIndex = leafletIndex / SQRT_M;
    historyFrequency.push_back({leafletIndex, frequencyCount[leafletIndex]});
    historyBlockMax.push_back({blockIndex, blockMaxPair[blockIndex]});

    frequencyCount[leafletIndex]++;
    if (frequencyCount[leafletIndex] > blockMaxPair[blockIndex].first) {
        blockMaxPair[blockIndex] = {frequencyCount[leafletIndex], leafletIndex};
    } else if (frequencyCount[leafletIndex] == blockMaxPair[blockIndex].first) {
        if (leafletIndex < blockMaxPair[blockIndex].second) blockMaxPair[blockIndex].second = leafletIndex;
    }
}

void rollbackOperations() {
    while (!historyFrequency.empty()) {
        auto p = historyFrequency.back(); historyFrequency.pop_back();
        frequencyCount[p.first] = p.second;
    }
    while (!historyBlockMax.empty()) {
        auto p = historyBlockMax.back(); historyBlockMax.pop_back();
        blockMaxPair[p.first] = p.second;
    }
}

pair<int, int> queryBestLeaflet(int left, int right) {
    pair<int, int> best = {0, left};
    int blockLeft = left / SQRT_M;
    int blockRight = right / SQRT_M;

    if (blockLeft == blockRight) {
        for (int i = left; i <= right; ++i) {
            if (frequencyCount[i] > best.first) best = {frequencyCount[i], i};
            else if (frequencyCount[i] == best.first && i < best.second) best.second = i;
        }
    } else {
        for (int i = left; i < (blockLeft + 1) * SQRT_M; ++i) {
            if (frequencyCount[i] > best.first) best = {frequencyCount[i], i};
            else if (frequencyCount[i] == best.first && i < best.second) best.second = i;
        }
        for (int b = blockLeft + 1; b < blockRight; ++b) {
            if (blockMaxPair[b].first > best.first) best = blockMaxPair[b];
            else if (blockMaxPair[b].first == best.first && blockMaxPair[b].second < best.second) best.second = blockMaxPair[b].second;
        }
        for (int i = blockRight * SQRT_M; i <= right; ++i) {
            if (frequencyCount[i] > best.first) best = {frequencyCount[i], i};
            else if (frequencyCount[i] == best.first && i < best.second) best.second = i;
        }
    }
    return best;
}

void performDFS(int u) {
    timeIn[u] = currentTime++;
    for (int v : neighbourList[u]) {
        ancestorTable[0][v] = u;
        for (int i = 1; i < 20; ++i) ancestorTable[i][v] = ancestorTable[i - 1][ancestorTable[i - 1][v]];
        performDFS(v);
    }
    timeOut[u] = currentTime - 1;
}

void solveTestCase() {
    cin >> S;
    cin >> M;
    leaflets.resize(M);
    int totalLength = 0;
    for (int i = 0; i < M; ++i) {
        cin >> leaflets[i];
        totalLength += size(leaflets[i]);
    }
    cin >> Q;

    SuffixAutomaton suffixAutomaton(totalLength + 5);
    for (int i = 0; i < M; ++i) {
        suffixAutomaton.lastState = 0;
        for (char c : leaflets[i]) suffixAutomaton.extendAutomaton(c);
    }

    int stateCount = suffixAutomaton.stateCount;
    neighbourList.assign(stateCount, vector<int>());
    for (int i = 1; i < stateCount; ++i) {
        neighbourList[suffixAutomaton.states[i].suffixLink].push_back(i);
    }

    timeIn.resize(stateCount);
    timeOut.resize(stateCount);
    currentTime = 0;
    for (int i = 0; i < 20; ++i) ancestorTable[i].assign(stateCount, 0);
    performDFS(0);

    for (int i = 0; i < M; ++i) {
        int currentNode = 0;
        for (char c : leaflets[i]) {
            currentNode = suffixAutomaton.states[currentNode].transitions[c - 'a'];
            eventPoints.push_back({timeIn[currentNode], i + 1});
        }
    }
    sort(all(eventPoints));

    int sizeS = size(S);
    vector<int> nodeAtPosition(sizeS + 1, 0);
    vector<int> lengthAtPosition(sizeS + 1, 0);
    int currentNode = 0, currentLength = 0;
    for (int i = 0; i < sizeS; ++i) {
        int code = S[i] - 'a';
        while (currentNode != 0 && suffixAutomaton.states[currentNode].transitions[code] == -1) {
            currentNode = suffixAutomaton.states[currentNode].suffixLink;
            currentLength = suffixAutomaton.states[currentNode].length;
        }
        if (suffixAutomaton.states[currentNode].transitions[code] != -1) {
            currentNode = suffixAutomaton.states[currentNode].transitions[code];
            currentLength++;
        }
        nodeAtPosition[i + 1] = currentNode;
        lengthAtPosition[i + 1] = currentLength;
    }

    vector<Query> queries(Q);
    vector<pair<int, int>> queryResults(Q);

    for (int i = 0; i < Q; ++i) {
        int l, r, pl, pr;
        cin >> l >> r >> pl >> pr;
        int requiredLength = pr - pl + 1;
        int u = nodeAtPosition[pr];
        int maxLength = lengthAtPosition[pr];

        if (maxLength < requiredLength) {
            queries[i] = {i, l, r, 0, -1};
        } else {
            for (int k = 19; k >= 0; --k) {
                int v = ancestorTable[k][u];
                if (suffixAutomaton.states[v].length >= requiredLength) u = v;
            }
            auto iteratorLeft = lower_bound(all(eventPoints), make_pair(timeIn[u], -1));
            auto iteratorRight = lower_bound(all(eventPoints), make_pair(timeOut[u] + 1, -1));
            int moLeft = (int)(iteratorLeft - eventPoints.begin());
            int moRight = (int)(iteratorRight - eventPoints.begin()) - 1;
            queries[i] = {i, l, r, moLeft, moRight};
        }
    }

    blockSizeMo = max(1, (int)(size(eventPoints) / sqrt(Q + 1)));
    sort(all(queries), [&](const Query& a, const Query& b) {
        if (a.moLeft / blockSizeMo != b.moLeft / blockSizeMo)
            return a.moLeft < b.moLeft;
        return a.moRight < b.moRight;
    });

    for (int i = 0; i <= M; ++i) frequencyCount[i] = 0;
    for (int i = 0; i <= M / SQRT_M + 1; ++i) blockMaxPair[i] = {0, 2000000000};

    int previousBlockIndex = -1;
    int rightPointer = 0;

    for (const auto& q : queries) {
        if (q.moLeft > q.moRight) {
            queryResults[q.id] = {q.queryLeft, 0};
            continue;
        }

        int blockIndex = q.moLeft / blockSizeMo;
        if (blockIndex != previousBlockIndex) {
            for (int i = 0; i <= M; ++i) frequencyCount[i] = 0;
            for (int i = 0; i <= M / SQRT_M + 1; ++i) blockMaxPair[i] = {0, 2000000000};
            previousBlockIndex = blockIndex;
            rightPointer = (blockIndex + 1) * blockSizeMo - 1;
        }

        int endOfBlock = (blockIndex + 1) * blockSizeMo;
        if (q.moRight < endOfBlock) {
            for (int i = q.moLeft; i <= q.moRight; ++i) addLeafletRollback(eventPoints[i].second);
            auto res = queryBestLeaflet(q.queryLeft, q.queryRight);
            queryResults[q.id] = {res.second, res.first};
            rollbackOperations();
        } else {
            if (rightPointer < endOfBlock - 1) rightPointer = endOfBlock - 1;
            while (rightPointer < q.moRight) {
                rightPointer++;
                addLeaflet(eventPoints[rightPointer].second);
            }
            for (int i = endOfBlock - 1; i >= q.moLeft; --i) {
                addLeafletRollback(eventPoints[i].second);
            }
            auto res = queryBestLeaflet(q.queryLeft, q.queryRight);
            queryResults[q.id] = {res.second, res.first};
            rollbackOperations();
        }
    }

    for (int i = 0; i < Q; ++i) {
        cout << queryResults[i].first << " " << queryResults[i].second << endl;
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