#include <iostream>
#include <vector>
using namespace std;

int countRectangles(int N) {
    int count = 0;

    for (int height = 1; height * height <= N; ++height) {
        for (int width = height; height * width <= N; ++width) {
            count++;
        }
    }

    return count;
}

int main() {
    int N;
    cin >> N;

    cout << countRectangles(N) << endl;

    return 0;
}
