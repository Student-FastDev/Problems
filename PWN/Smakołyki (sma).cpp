#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long N, M;
    cin >> N >> M;

    vector<long long> numbersArray(N);

    for(long long i = 0; i < N; i++) {
        cin >> numbersArray[i];
    }

    vector<bool> seen(M+1, false);
    long long start = 0;
    long long score = 0;

    for(long long end = 0; end < N; end++) {
        while (seen[numbersArray[end]]) {
            seen[numbersArray[start]] = false;
            start++;
        }
        seen[numbersArray[end]] = true;
        score += (end - start + 1);
    }
    cout << score;

    return 0;
}
