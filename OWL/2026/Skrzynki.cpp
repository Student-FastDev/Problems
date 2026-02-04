// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define size(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define endl '\n'

const ll MOD = 1e9 + 7;
const int MAX_N = 1e5;
const ll INF = 1e18 + 67;

struct Box {
    ll w;
    ll m;
    ll sum;
};

bool compareBoxes(Box& A, Box&B) {
    return A.sum < B.sum;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<Box> boxArray(N);
    for(int i = 0; i < N; i++) {
        cin >> boxArray[i].w >> boxArray[i].m;
        boxArray[i].sum = boxArray[i].w + boxArray[i].m;
    }

    sort(all(boxArray), compareBoxes);
    priority_queue<ll> sortQueue;

    ll currentTotal = 0;
    for(auto box : boxArray) {
        if(box.w >= currentTotal) {
            sortQueue.push(box.m);
            currentTotal += box.m;
        }
        else {
            if(!sortQueue.empty()) {
                ll heaviestMass = sortQueue.top();
                if(box.m < heaviestMass) {
                    sortQueue.pop();
                    currentTotal -= heaviestMass;
                    sortQueue.push(box.m);
                    currentTotal += box.m;
                }
            }
        }
    }

    cout << size(sortQueue);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
}
