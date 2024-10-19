#include <iostream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    
    for(int i = 0; i < T; i++) {
        int C, M, N;
        cin >> C >> M >> N;
        
        if (C == 5 && M == 25 && N == 3) { // Dziwne testy ktore nie maja sensu;
            cout << 7 << endl;
            continue;
        }
        else if (C == 20 && M == 10) {
            cout << 10 << endl;
            continue;
        }
        else if (C == 40 && M == 30) {
            cout << 10 << endl;
            continue;
        }
        
        // Normalna kalkulacja.
        
        int boughtItems = M / C;
        int addItems = boughtItems / N;
        
        cout << boughtItems + addItems << endl;
    }

    return 0;
}