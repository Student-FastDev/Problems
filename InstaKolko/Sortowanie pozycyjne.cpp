#include <bits/stdc++.h>
using namespace std;

const long long baseValue = 10;
vector<long long> numberArray, tempArray, countArray;
vector<long long> powerOfBase;

void precomputePowers() {
    long long power = 1;
    for (int i = 0; i < 6; i++) {
        powerOfBase.push_back(power);
        power *= baseValue;
    }
}

long long getDigit(long long numberValue, long long k) {
    return (numberValue / powerOfBase[k - 1]) % baseValue;
}

void sortByDigit(long long N, long long k) {
    fill(countArray.begin(), countArray.end(), 0);

    for (long long i = 0; i < N; i++) {
        countArray[getDigit(numberArray[i], k)]++;
    }

    for (long long i = 1; i < baseValue; i++) {
        countArray[i] += countArray[i - 1];
    }

    for (long long i = N - 1; i >= 0; i--) {
        long long digitValue = getDigit(numberArray[i], k);
        tempArray[--countArray[digitValue]] = numberArray[i];
    }

    for (long long i = 0; i < N; i++) {
        numberArray[i] = tempArray[i];
    }
}

void radixSort(long long N) {
    long long maxVal = *max_element(numberArray.begin(), numberArray.end());
    int numDigits = 0;
    while (maxVal > 0) {
        numDigits++;
        maxVal /= baseValue;
    }

    for (long long i = 1; i <= numDigits; i++) {
        sortByDigit(N, i);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    precomputePowers();

    long long N;
    cin >> N;

    numberArray.resize(N);
    tempArray.resize(N);
    countArray.resize(baseValue, 0);

    for (long long i = 0; i < N; i++) {
        cin >> numberArray[i];
    }

    radixSort(N);

    for (long long i = 0; i < N; i++) {
        cout << numberArray[i] << " ";
    }
    cout << endl;

    return 0;
}
