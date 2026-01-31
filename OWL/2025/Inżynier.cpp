#include <bits/stdc++.h>
#include "inzlib.h"
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(), (x).end()
#define endl    '\n'
#define sz(x)   (int)(x).size()

const ll INF = 9223372036854775806LL;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // or 998244353

vector<pair<int, int>> reverses;
vector<pair<int, int>> reversesHistory;

void applyReverse(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    reverse(arr.begin() + l, arr.begin() + r + 1);
    reverses.emplace_back(l, r);
}

void applyBetterReverse(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    reverse(arr.begin() + l, arr.begin() + r + 1);
    obracanie(l, r+1);
}

int simplerSort(vector<int>& T, int start, int end) {
    if (is_sorted(T.begin() + start, T.begin() + end))
        return 0;
    int N = end - start;
    if (N <= 1) return 0;

    int mid = start + N / 2;
    int c1 = simplerSort(T, start, mid);
    int c2 = simplerSort(T, mid, end);

    int countOnesLeft = count(T.begin() + start, T.begin() + mid, 1);
    int countZerosRight = count(T.begin() + mid, T.begin() + end, 0);

    if (countOnesLeft > 0 && countZerosRight > 0) {
        int revStart = mid - countOnesLeft;
        int revEnd = mid + countZerosRight - 1;
        applyReverse(T, revStart, revEnd);
    }
    return c1 + c2 + (countOnesLeft + countZerosRight);
}

void permutationSort(vector<int>& nums, int start, int end, int& cost) {
    if (end - start <= 1) return;

    vector<int> chunk(nums.begin() + start, nums.begin() + end);
    auto midIterator = chunk.begin() + chunk.size()/2;
    nth_element(chunk.begin(), midIterator, chunk.end());
    int pivot = *midIterator;

    {
        vector<int> T(end - start);
        for (int i = start; i < end; ++i)
            T[i - start] = (nums[i] >= pivot) ? 1 : 0;

        reverses.clear();
        int cost1 = simplerSort(T, 0, T.size());
        cost += cost1;

        for (auto [l, r] : reverses) {
            applyBetterReverse(nums, start + l, start + r);
        }
    }

    int L = start;
    while (L < end && nums[L] < pivot) L++;

    {
        vector<int> U(end - L);
        for (int i = L; i < end; ++i)
            U[i - L] = (nums[i] > pivot) ? 1 : 0;

        reverses.clear();
        int cost2 = simplerSort(U, 0, U.size());
        cost += cost2;

        for (auto [l, r] : reverses) {
            applyBetterReverse(nums, L + l, L + r);
        }
    }
    int M = L;
    while (M < end && nums[M] == pivot) M++;

    permutationSort(nums, start, L, cost);
    permutationSort(nums, M, end, cost);
}

int main() {
    int N = dajN();
    vector<int> valuesVector(N);

    for (int i = 0; i < N; i++) {
        valuesVector[i] = dajElem(i);
    }
    int cost = 0;
    permutationSort(valuesVector, 0, valuesVector.size(), cost);
    koniec();
    return 0;
}
