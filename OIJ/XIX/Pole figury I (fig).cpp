#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long int P;
    cin >> P;
    
    long long int N = sqrt(P);
    
    if (P == N * N) {
        for (int i = 0; i < N; i++) cout << "G";
        for (int i = 0; i < N; i++) cout << "L";
        for (int i = 0; i < N; i++) cout << "D";
        for (int i = 0; i < N; i++) cout << "P";    
    } 
    else if (P > N * N && P <= N * (N + 1)) {
        for (int i = 0; i < (P - (N * N)); i++) cout << "G";
        
        cout << "L";
        for (int i = 0; i < ((N + (N * N) - P)); i++) cout << "G";
        for (int i = 0; i < N; i++) cout << "L";
        for (int i = 0; i < N; i++) cout << "D";
        for (int i = 0; i < (N + 1); i++) cout << "P";
    } 
    else if (P > N * (N + 1) && P <= (N + 1) * (N + 1)) {
        for (int i = 0; i < (N + 1); i++) cout << "G";
        for (int i = 0; i < (P - (N * N) - N); i++) cout << "L";

        cout << "D";
        for (int i = 0; i <= (N - P + (N * N) + N); i++) cout << "L"; 
        for (int i = 0; i < N; i++) cout << "D";
        for (int i = 0; i < (N + 1); i++) cout << "P";
    }
    return 0;
}
