#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1e6 + 1;
vector<int> sieveArray(MAX_N);

void prepareSieve() {
    for (int i = 2; i < MAX_N; i++) {
        sieveArray[i] = i;
    }

    for (int i = 2; i * i < MAX_N; i++) {
        if (sieveArray[i] == i) {
            for (int j = i * i; j < MAX_N; j += i) {
                if (sieveArray[j] == j) {
                    sieveArray[j] = i;
                }
            }
        }
    }
}

void getPrimeFactors(int A) {
    while (A != 1) {
        printf("%d ", sieveArray[A]);
        A /= sieveArray[A];
    }
    printf("\n");
}

int main() {
    prepareSieve();

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int Q;
        scanf("%d", &Q);
        getPrimeFactors(Q);
    }

    return 0;
}
