#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long minimalneRuchy(string balls) {
    vector<long long> czerwoneKulki;
    for (long long i = 0; i < balls.size(); ++i) {
        if (balls[i] == 'C') {
            czerwoneKulki.push_back(i);
        }
    }
    long long n = czerwoneKulki.size();
    if (n == 0) {
        return 0;
    }

    long long medianaIndex = czerwoneKulki[n / 2];
    long long ruchy = 0;
    for (long long i = 0; i < n; ++i) {
        ruchy += abs(czerwoneKulki[i] - (medianaIndex - (n / 2) + i));
    }

    return ruchy;
}

int main() {
    long long n;
    string balls;
    cin >> n >> balls;

    cout << minimalneRuchy(balls) << endl;

    return 0;
}
