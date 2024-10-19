#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    if (N == 0 || M == 0) {
        cout << "NIE" << endl;
        return 0;
    }
    
    if(M > N) {
        cout << "NIE" << endl;
        return 0;
    }

    vector<int> A(M);
    int totalTasks = 0;
    int totalPoints = 0;

    for (int i = 0; i < M; i++) {
        cin >> A[i];
        totalTasks += A[i];
    }

    if (totalTasks < 4 * N) {
        cout << "NIE" << endl;
        return 0;
    }
    
    for (int i = 0; i < M; i++) {
        if(A[i] < 4) {
            cout << "NIE" << endl;
            return 0;
        }
        totalPoints += A[i] / 4;
    }

    if (totalPoints >= N) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }

    return 0;
}
