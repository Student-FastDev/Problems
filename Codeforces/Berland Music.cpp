// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x) (x).begin(),(x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7; // 998244353

void solveTestCase() {
    int N;
    cin >> N;

    vector<int> P(N);
    for (int i = 0; i < N; ++i) {
        cin >> P[i];
    }

    string S;
    cin >> S;

    vector<pii> dislikedSongs;
    vector<pii> likedSongs;

    for (int i = 0; i < N; ++i) {
        if (S[i] == '0') {
            dislikedSongs.push_back({P[i], i});
        } else {
            likedSongs.push_back({P[i], i});
        }
    }

    sort(all(dislikedSongs));
    sort(all(likedSongs));

    vector<int> resultPermutation(N);
    int currentRank = 1;

    for (const auto& song : dislikedSongs) {
        resultPermutation[song.second] = currentRank++;
    }

    for (const auto& song : likedSongs) {
        resultPermutation[song.second] = currentRank++;
    }

    for (int i = 0; i < N; ++i) {
        cout << resultPermutation[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        solveTestCase();
    }
    return 0;
}