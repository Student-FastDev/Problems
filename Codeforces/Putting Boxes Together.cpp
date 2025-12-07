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
#define size(x)  (int)x.size()

const ll INF = 9223372036854775806;
const ll MOD = 1e9+7; 
const int MAX_N = 200005;

struct Node {
    ll exactSumWeights;
    ll moduloSumWeights;
    ll moduloSumWeightsTimesPositions;
};

Node segmentTree[4 * MAX_N];
ll positions[MAX_N]; 
ll shiftedPositions[MAX_N]; 
ll weights[MAX_N]; 
int N;

void buildSegmentTree(int node, int start, int end) {
    if(start == end) {
        segmentTree[node].exactSumWeights = weights[start];
        segmentTree[node].moduloSumWeights = weights[start] % MOD;
        segmentTree[node].moduloSumWeightsTimesPositions = (weights[start] % MOD) * (shiftedPositions[start] % MOD) % MOD;
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(2 * node, start, mid);
        buildSegmentTree(2 * node + 1, mid + 1, end);
        segmentTree[node].exactSumWeights = segmentTree[2 * node].exactSumWeights + segmentTree[2 * node + 1].exactSumWeights;
        segmentTree[node].moduloSumWeights = (segmentTree[2 * node].moduloSumWeights + segmentTree[2 * node + 1].moduloSumWeights) % MOD;
        segmentTree[node].moduloSumWeightsTimesPositions = (segmentTree[2 * node].moduloSumWeightsTimesPositions + segmentTree[2 * node + 1].moduloSumWeightsTimesPositions) % MOD;
    }
}

void updateSegmentTree(int node, int start, int end, int indexToUpdate, ll newWeight) {
    if(start == end) {
        weights[indexToUpdate] = newWeight;
        segmentTree[node].exactSumWeights = newWeight;
        segmentTree[node].moduloSumWeights = newWeight % MOD;
        segmentTree[node].moduloSumWeightsTimesPositions = (newWeight % MOD) * (shiftedPositions[indexToUpdate] % MOD) % MOD;
    } else {
        int mid = (start + end) / 2;
        if(start <= indexToUpdate && indexToUpdate <= mid) {
            updateSegmentTree(2 * node, start, mid, indexToUpdate, newWeight);
        } else {
            updateSegmentTree(2 * node + 1, mid + 1, end, indexToUpdate, newWeight);
        }
        segmentTree[node].exactSumWeights = segmentTree[2 * node].exactSumWeights + segmentTree[2 * node + 1].exactSumWeights;
        segmentTree[node].moduloSumWeights = (segmentTree[2 * node].moduloSumWeights + segmentTree[2 * node + 1].moduloSumWeights) % MOD;
        segmentTree[node].moduloSumWeightsTimesPositions = (segmentTree[2 * node].moduloSumWeightsTimesPositions + segmentTree[2 * node + 1].moduloSumWeightsTimesPositions) % MOD;
    }
}

pair<ll, ll> queryModuloSums(int node, int start, int end, int l, int r) {
    if(r < start || end < l) {
        return {0, 0};
    }
    if(l <= start && end <= r) {
        return {segmentTree[node].moduloSumWeights, segmentTree[node].moduloSumWeightsTimesPositions};
    }
    int mid = (start + end) / 2;
    pair<ll, ll> leftResult = queryModuloSums(2 * node, start, mid, l, r);
    pair<ll, ll> rightResult = queryModuloSums(2 * node + 1, mid + 1, end, l, r);
    return {(leftResult.first + rightResult.first) % MOD, (leftResult.second + rightResult.second) % MOD};
}

ll queryExactSumWeights(int node, int start, int end, int l, int r) {
    if(r < start || end < l) return 0;
    if(l <= start && end <= r) return segmentTree[node].exactSumWeights;
    int mid = (start + end) / 2;
    return queryExactSumWeights(2 * node, start, mid, l, r) + 
           queryExactSumWeights(2 * node + 1, mid + 1, end, l, r);
}

int findIndexWithPrefixSum(int node, int start, int end, ll targetValue) {
    if(start == end) return start;
    int mid = (start + end) / 2;
    if(segmentTree[2 * node].exactSumWeights >= targetValue) {
        return findIndexWithPrefixSum(2 * node, start, mid, targetValue);
    } else {
        return findIndexWithPrefixSum(2 * node + 1, mid + 1, end, targetValue - segmentTree[2 * node].exactSumWeights);
    }
}

void solveTestCase() {
    int Q;
    cin >> N >> Q;

    for(int i = 1; i <= N; ++i) {
        cin >> positions[i];
        shiftedPositions[i] = positions[i] - i;
    }
    for(int i = 1; i <= N; ++i) {
        cin >> weights[i];
    }

    buildSegmentTree(1, 1, N);

    while(Q--) {
        ll xQuery, yQuery;
        cin >> xQuery >> yQuery;
        if(xQuery < 0) {
            int id = -xQuery;
            ll newWeight = yQuery;
            updateSegmentTree(1, 1, N, id, newWeight);
        } else {
            int l = xQuery;
            int r = yQuery;
            
            ll totalRangeWeight = queryExactSumWeights(1, 1, N, l, r);
            ll prefixWeightBeforeL = queryExactSumWeights(1, 1, N, 1, l - 1);
            ll targetPrefixWeight = prefixWeightBeforeL + (totalRangeWeight + 1) / 2;
            
            int medianIndex = findIndexWithPrefixSum(1, 1, N, targetPrefixWeight);
            
            ll medianShiftedPos = shiftedPositions[medianIndex] % MOD;
            
            pair<ll, ll> sumsLeft = queryModuloSums(1, 1, N, l, medianIndex);
            ll sumWeightsLeft = sumsLeft.first;
            ll sumWeightsTimesPosLeft = sumsLeft.second;
            
            ll termLeft = (medianShiftedPos * sumWeightsLeft) % MOD;
            ll costLeft = (termLeft - sumWeightsTimesPosLeft + MOD) % MOD;
            
            ll costRight = 0;
            if(medianIndex < r) {
                pair<ll, ll> sumsRight = queryModuloSums(1, 1, N, medianIndex + 1, r);
                ll sumWeightsRight = sumsRight.first;
                ll sumWeightsTimesPosRight = sumsRight.second;
                
                ll termRight = (medianShiftedPos * sumWeightsRight) % MOD;
                costRight = (sumWeightsTimesPosRight - termRight + MOD) % MOD;
            }
            
            ll totalCost = (costLeft + costRight) % MOD;
            cout << totalCost << endl;
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