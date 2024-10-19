#include <iostream>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    char tableArray[N][M];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> tableArray[i][j];
        }
    }

    int topIndex = N, bottomIndex = 0, leftIndex = M, rightIndex = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (tableArray[i][j] == '#') {
                if (i < topIndex) topIndex = i;
                if (i > bottomIndex) bottomIndex = i;
                if (j < leftIndex) leftIndex = j;
                if (j > rightIndex) rightIndex = j;
            }
        }
    }

    for (int i = topIndex; i <= bottomIndex; ++i) {
        for (int j = leftIndex; j <= rightIndex; ++j) {
            if (tableArray[i][j] == '.') { 
                cout << i + 1 << " " << j + 1 << endl;
                return 0;
            }
        }
    }

    return 0;
}
