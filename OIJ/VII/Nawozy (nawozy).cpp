#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int N, L;
    cin >> N >> L;
    
    string garden;
    cin >> garden;
    
    vector<int> fertilizers(N);
    for (int i = 0; i < N; ++i) {
        cin >> fertilizers[i];
    }
    
    vector<int> needs(N, 0);
    int anyTypeCount = 0;
    
    for (char c : garden) {
        if (c == 'D') {
            anyTypeCount++;
        } else {
            int type = c - '1';
            needs[type]++;
        }
    }
    
    int totalSurplus = 0;
    bool sufficient = true;
    for (int i = 0; i < N; ++i) {
        if (fertilizers[i] < needs[i]) {
            sufficient = false;
            break;
        }
        totalSurplus += fertilizers[i] - needs[i];
    }
    
    if (sufficient && totalSurplus >= anyTypeCount) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }
    
    return 0;
}
