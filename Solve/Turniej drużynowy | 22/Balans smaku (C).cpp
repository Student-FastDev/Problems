#include <bits/stdc++.h>
#include <cmath>
#include <vector>

using namespace std;

#define ll __int128

const int MAX_N = 10e9 + 7;
const int MOD = 10e9 + 7;

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);
    
    int N;
    vector<ll> V; 
    char T;
    ll S = 0, C = 0;
    
    cin >> N;

    V.push_back(1);

    for (int i = 0; i < N; i++) 
    {
        cin >> T;

        if (T == 'S') {
            S += V[i];
        }
        else if (T == 'C'){
            C += V[i];
        }

        V.push_back(V[i] * 2); 
    }

    if (S < C) {
        cout << "SLODKA";
    }
    else if (S == C){
        cout << "BALANS";
    }
    else {
        cout << "SLONA";
    }

    return 0;
}