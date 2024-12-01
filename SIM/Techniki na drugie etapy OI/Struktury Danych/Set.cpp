#include <iostream>
#include <set>
#include <numeric>
#include <string>
using namespace std;

long long gcdFunction(long long A, long long B) {
    while (B) {
        A %= B;
        swap(A, B);
    }
    return A;
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    long long N;
    cin >> N;
    multiset<long long> duckPrices;
    long long totalSum = 0;

    for (long long i = 0; i < N; ++i) {
        string optionVariable;
        cin >> optionVariable;

        if (optionVariable == "NAJMN") {
            if (duckPrices.empty()) {
                cout << "NIE" << endl;
            } else {
                auto it = duckPrices.begin();
                cout << *it << endl;
                totalSum -= *it;
                duckPrices.erase(it);
            }
        } else if (optionVariable == "NAJW") {
            if (duckPrices.empty()) {
                cout << "NIE" << endl;
            } else {
                auto it = prev(duckPrices.end());
                cout << *it << endl;
                totalSum -= *it;
                duckPrices.erase(it);
            }
        } else if (optionVariable == "PRZEDZ") {
            long long X, Y;
            cin >> X >> Y;
            auto it = duckPrices.lower_bound(X);
            auto endIt = duckPrices.upper_bound(Y);
            if (it == endIt) {
                cout << "NIE" << endl;
            } else {
                cout << *it << endl;
                totalSum -= *it;
                duckPrices.erase(it);
            }
        } else if (optionVariable == "MINUS") {
            long long X;
            cin >> X;
            auto it = duckPrices.find(X);
            if (it == duckPrices.end()) {
                cout << "NIE" << endl;
            } else {
                cout << "TAK" << endl;
                totalSum -= *it;
                duckPrices.erase(it);
            }
        } else if (optionVariable == "SREDN") {
            if (duckPrices.empty()) {
                cout << "0/1" << endl;
            } else {
                long long count = duckPrices.size();
                long long numerator = totalSum;
                long long denominator = count;

                long long gcd = gcdFunction(numerator, denominator);
                numerator /= gcd;
                denominator /= gcd;

                cout << numerator << "/" << denominator << endl;
            }
        } else if (optionVariable == "PLUS") {
            long long X;
            cin >> X;
            duckPrices.insert(X);
            totalSum += X;
        }
    }

    return 0;
}
