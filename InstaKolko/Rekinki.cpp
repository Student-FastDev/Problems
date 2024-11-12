#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    int A, B, C;
    cin >> A >> B >> C;
    
    vector<int> array(N);
    for (int i = 0; i < N; i++) {
        cin >> array[i];
    }
    
    vector<bool> DP(N, false);
    DP[0] = true;
    
    for (int i = 0; i < N; i++) {
        if (DP[i] && array[i] == 0) {
            if (i + A < N && array[i + A] == 0) {
                DP[i + A] = true;
            }
            if (i + B < N && array[i + B] == 0) {
                DP[i + B] = true;
            }
            if (i + C < N && array[i + C] == 0) {
                DP[i + C] = true;
            }
        }
    }
    
    int wynik = 0;
    for (int i = 0; i < N; i++) {
        if (DP[i]) {
            wynik = i;
        }
    }

    cout << wynik+1 << endl;
    return 0;
}
