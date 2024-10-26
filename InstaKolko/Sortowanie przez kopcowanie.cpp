#include <iostream>
using namespace std;

const long long N = 1e5 + 10;

long long tab[N];

void heapify(long long x, long long N) {
    long long next = x;
    if (2 * x <= N && tab[2 * x] > tab[next]) {
        next = 2 * x;
    }
    if (2 * x + 1 <= N && tab[2 * x + 1] > tab[next]) {
        next = 2 * x + 1;
    }
    if (x == next) {
        return;
    }
    swap(tab[x], tab[next]);
    heapify(next, N);
}

void init(long long N) {
    for (long long i = N / 2; i >= 1; i--) {
        heapify(i, N);
    }
}

void heapsort(long long N) {
    init(N);
    for (long long i = N; i > 1; i--) {
        swap(tab[1], tab[i]);
        heapify(1, i - 1);
    }
}

int main() {
    long long N;
    cin >> N;
    
    for (long long i = 1; i <= N; i++) {
        cin >> tab[i];
    }
    
    heapsort(N);
    
    for (long long i = 1; i <= N; i++) {
        cout << tab[i] << " ";
    }
    cout << endl;

    return 0;
}
