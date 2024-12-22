#include "kaslib.h"
#include <bits/stdc++.h>
using namespace std;

#define SIZE 8000000

vector<int64_t> primeArray;
vector<int64_t> maxPrimeArray;
bool isPrime[SIZE];
int64_t N = 1;

void initializePrimes() {
    for (int i = 2; i * i < SIZE; i++) {
        if (isPrime[i]) continue;
        for (int j = i * i; j < SIZE; j += i) isPrime[j] = true;
    }

    primeArray.reserve(700000);
    for (int i = 2; i < SIZE; i++) {
        if (isPrime[i]) continue;
        primeArray.push_back(i);
    }

    maxPrimeArray.reserve(700000);
    for (auto &prime : primeArray) {
        int64_t P = prime;
        while (P <= N / prime) P *= prime;
        maxPrimeArray.push_back(P);
    }
}

bool makeGuess(int64_t &P) {
    P = 1;
    for (int i = 0; i < static_cast<int>(primeArray.size()); i++) {
        int j = i;
        int64_t productValue = 1;
        while (j < static_cast<int>(primeArray.size()) && productValue < N / primeArray[j]) {
            productValue *= primeArray[j];
            j++;
        }
        j--;

        int64_t queryResult = Pytaj(productValue);
        while (i <= j) {
            if (queryResult % primeArray[i] == 0) P *= Pytaj(maxPrimeArray[i]);
            i++;
        }
        i--;

        if (P >= N / primeArray[i]) return true;
        if (i > 10 && P < 200LL) return false;
        if (i > 30 && P < 16000LL) return false;
        if (i > 100 && P < 900000LL) return false;
        if (i > 250 && P < 600000000LL) return false;
        if (i > 1200 && P < 3000000000000LL) return false;
        if (i > 70000 && P < 10000000000000LL) return false;
    }
    return false;
}


int main() {
    N = DajN();
    initializePrimes();

    while (true) {
        int64_t P;
        if (makeGuess(P)) {
            Odpowiedz(P);
        } else {
            Szturchnij();
        }
    }
    return 0;
}
