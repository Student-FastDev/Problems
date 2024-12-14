#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const long long MAX_N = 1e7+1;
const long long primeCount = 0;
const long long MAX_VALUE = 1e5+1;

vector<long long> primeNumbers;
vector<long long> modPrimes;

vector<vector<long long>> modFactorial(primeCount + 50, vector<long long>(MAX_VALUE));

void generatePrimes(long long limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (long long i = 2; i * i <= limit; ++i) {
        if (isPrime[i]) {
            for (long long j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    for (long long i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primeNumbers.push_back(i);
        }
    }
}

void computeFactorials() {
    for (size_t k = 0; k < modPrimes.size(); ++k) {
        long long p = modPrimes[k];
        modFactorial[k][0] = 1;
        for (long long i = 1; i < MAX_VALUE; ++i) {
            modFactorial[k][i] = (modFactorial[k][i-1] * i) % p;
        }
    }
}

long long stringToModNumber(const string &X, long long pIndex) {
    long long p = modPrimes[pIndex];
    long long result = 0;
    for (char c : X) {
        result = (result * 10 + (c - '0')) % p;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long A, B, C, D;
    string X;
    cin >> A >> B >> C >> D >> X;

    vector<long long> bigPrimes = {
        868891399, 870947863, 873008797, 875065823, 877132621,
        879190841, 881253493, 883311217, 885375367, 887435303,
        889495223, 891560609, 893617871, 895682083, 897746123,
        899809363, 901866943, 903932807, 905995897, 908054801,
        910112683, 912171059, 914234743, 916292957, 918363373,
        920419823, 922484831, 924551941, 926615597, 928683689,
        1003162837, 1005234953, 1007304029, 1009380649, 1011451901,
        1013526181, 1015595227, 1017668207, 1019744191, 1021817309,
        1023893887, 1025965753, 1028046001, 1030118737, 1032193363,
        1034271001, 1036348757, 1038420917, 1040493253, 1042567741
    };
    modPrimes.insert(modPrimes.end(), bigPrimes.begin(), bigPrimes.end());

    generatePrimes(MAX_N);

    long long startValue = max(0LL, (long long)primeNumbers.size() - primeCount);
    for (long long i = startValue; i < primeNumbers.size(); ++i) {
        modPrimes.push_back(primeNumbers[i]);
    }

    computeFactorials();

    for(size_t i = 0; i < modPrimes.size(); ++i) {
        long long modNumber = modPrimes[i];
        long long leftSide = (modFactorial[i][A] * modFactorial[i][C]) % modNumber;
        long long xMod = stringToModNumber(X, i);
        long long rightSide = (modFactorial[i][B] * modFactorial[i][A-B]) % modNumber;
        rightSide = (rightSide * modFactorial[i][D]) % modNumber;
        rightSide = (rightSide * modFactorial[i][C-D]) % modNumber;
        rightSide = (rightSide * xMod) % modNumber;

        if(leftSide != rightSide) {
            cout << "NIE" << endl;
            return 0;
        }
    }
    cout << "TAK" << endl;

    return 0;
}
