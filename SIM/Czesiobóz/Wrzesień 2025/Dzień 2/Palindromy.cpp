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

const ll firstMOD = 1e9+7;
const ll secondMOD = 998244353;
const ll P = 137;

struct SegmentTree {
    int N;
    ll moduloValue;
    vector<ll> treeArray;
    SegmentTree() {}
    SegmentTree(int n_, ll MOD_) : N(n_), moduloValue(MOD_), treeArray(4 * n_ + 5, 0) {}

    void pointAdd(int currentNode, int L, int R, int indexValue, ll updateValue) {
        if (updateValue < 0) updateValue = (updateValue % moduloValue + moduloValue) % moduloValue;
        else if (updateValue >= moduloValue) updateValue %= moduloValue;
        if (L == R) {
            treeArray[currentNode] += updateValue;
            if (treeArray[currentNode] >= moduloValue) treeArray[currentNode] -= moduloValue;
            return;
        }
        int middleValue = (L + R) >> 1;
        if (indexValue <= middleValue) pointAdd(currentNode << 1, L, middleValue, indexValue, updateValue);
        else pointAdd(currentNode << 1 | 1, middleValue+1, R, indexValue, updateValue);
        treeArray[currentNode] = treeArray[currentNode << 1] + treeArray[currentNode << 1 | 1];
        if (treeArray[currentNode] >= moduloValue) treeArray[currentNode] -= moduloValue;
    }

    void addValue(int indexValue, ll updateValue) {
        pointAdd(1, 1, N, indexValue, updateValue);
    }

    ll rangeSum(int currentNode, int L, int R, int queryLeft, int queryRight) {
        if (queryLeft > R || queryRight < L) return 0;
        if (queryLeft <= L && R <= queryRight) return treeArray[currentNode] % moduloValue;
        int middleValue = (L + R) >> 1;
        ll leftValue = rangeSum(currentNode << 1, L, middleValue, queryLeft, queryRight);
        ll rightValue = rangeSum(currentNode << 1 | 1, middleValue + 1, R, queryLeft, queryRight);
        ll finalResult = leftValue + rightValue;
        if (finalResult >= moduloValue) finalResult -= moduloValue;
        return finalResult;
    }

    ll rangeSum(int L, int R) {
        if (R < L) return 0;
        ll finalResult = rangeSum(1, 1, N, L, R);
        finalResult %= moduloValue;
        if (finalResult < 0) finalResult += moduloValue;
        return finalResult;
    }
};

ll modPower(ll A, ll E, ll moduloValue) {
    ll R = 1 % moduloValue;
    A %= moduloValue;
    while (E) {
        if (E & 1) R = (__int128)R * A % moduloValue;
        A = (__int128)A * A % moduloValue;
        E >>= 1;
    }
    return R;
}

void solveTestCase() {
    int N, Q;
    cin >> N >> Q;
    string S;
    S.reserve(N + 5);
    cin >> S;
    S = " " + S;

    vector<ll> firstPower(N + 2), firstInverse(N + 2), secondPower(N + 2), secondInverse(N + 2);
    firstPower[0] = 1; secondPower[0] = 1;
    for (int i = 1; i <= N; ++i) {
        firstPower[i] = ( (__int128)firstPower[i-1] * P ) % firstMOD;
        secondPower[i] = ( (__int128)secondPower[i-1] * P ) % secondMOD;
    }
    ll primeFirstInverse = modPower(P, firstMOD - 2, firstMOD);
    ll primeSecondInverse = modPower(P, secondMOD - 2, secondMOD);
    firstInverse[0] = 1; secondInverse[0] = 1;
    for (int i = 1; i <= N; ++i) {
        firstInverse[i] = (__int128)firstInverse[i-1] * primeFirstInverse % firstMOD;
        secondInverse[i] = (__int128)secondInverse[i-1] * primeSecondInverse % secondMOD;
    }

    SegmentTree firstForward(N, firstMOD), secondForward(N, secondMOD), firstBackward(N, firstMOD), secondBackward(N, secondMOD);

    auto charValue = [&](char C) -> int {
        return (int)(C - 'A' + 1);
    };

    for (int i = 1; i <= N; ++i) {
        int V = charValue(S[i]);
        ll firstForwardAdd = ( (__int128)V * firstPower[i] ) % firstMOD;
        ll secondForwardAdd = ( (__int128)V * secondPower[i] ) % secondMOD;
        firstForward.addValue(i, firstForwardAdd);
        secondForward.addValue(i, secondForwardAdd);
        int backwardPosition = N - i + 1;
        ll firstBackwardAdd = ( (__int128)V * firstPower[backwardPosition] ) % firstMOD;
        ll secondBackwardAdd = ( (__int128)V * secondPower[backwardPosition] ) % secondMOD;
        firstBackward.addValue(backwardPosition, firstBackwardAdd);
        secondBackward.addValue(backwardPosition, secondBackwardAdd);
    }

    for (int l = 0; l < Q; ++l) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            int X; char C;
            cin >> X >> C;
            if (S[X] == C) continue;
            int oldValue = charValue(S[X]);
            int newValue = charValue(C);
            ll firstForwardDelta = ( (__int128)(newValue - oldValue) * firstPower[X] ) % firstMOD;
            if (firstForwardDelta < 0) firstForwardDelta += firstMOD;
            ll secondForwardDelta = ( (__int128)(newValue - oldValue) * secondPower[X] ) % secondMOD;
            if (secondForwardDelta < 0) secondForwardDelta += secondMOD;
            firstForward.addValue(X, firstForwardDelta);
            secondForward.addValue(X, secondForwardDelta);
            int backwardPosition = N - X + 1;
            ll firstBackwardDelta = ( (__int128)(newValue - oldValue) * firstPower[backwardPosition] ) % firstMOD;
            if (firstBackwardDelta < 0) firstBackwardDelta += firstMOD;
            ll secondBackwardDelta = ( (__int128)(newValue - oldValue) * secondPower[backwardPosition] ) % secondMOD;
            if (secondBackwardDelta < 0) secondBackwardDelta += secondMOD;
            firstBackward.addValue(backwardPosition, firstBackwardDelta);
            secondBackward.addValue(backwardPosition, secondBackwardDelta);
            S[X] = C;
        } else if (queryType == 2) {
            int L, R;
            cin >> L >> R;
            ll firstSumForward = firstForward.rangeSum(L, R);
            ll firstNormForward = (__int128)firstSumForward * firstInverse[L] % firstMOD;
            ll secondSumForward = secondForward.rangeSum(L, R);
            ll secondNormForward = (__int128)secondSumForward * secondInverse[L] % secondMOD;

            int rl = N - R + 1;
            int rr = N - L + 1;
            ll firstSumBackward = firstBackward.rangeSum(rl, rr);
            ll firstNormBackward = (__int128)firstSumBackward * firstInverse[rl] % firstMOD;
            ll secondSumBackward = secondBackward.rangeSum(rl, rr);
            ll secondNormBackward = (__int128)secondSumBackward * secondInverse[rl] % secondMOD;

            if (firstNormForward == firstNormBackward && secondNormForward == secondNormBackward) {
                cout << "Tak" << endl;
            } else {
                cout << "Nie" << endl;
            }
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
