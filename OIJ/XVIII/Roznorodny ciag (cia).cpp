#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;

    int tab[200001];
    for (int i = 0; i < n; ++i) {
        cin >> tab[i];
    }
    
    sort(tab, tab + n);

    long long totalSubtracted = 0;
    for (int i = n - 2; i >= 0; --i) {
        int originalValue = tab[i];
        tab[i] = min(tab[i], max(0, tab[i + 1] - 1));
        totalSubtracted += originalValue - tab[i];
    }
    
    cout << totalSubtracted << endl;

    return 0;
}
