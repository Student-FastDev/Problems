#include <iostream>
using namespace std;

int main() {
    int W, D, L;
    cin >> W >> D >> L;

    int X = (W * L) / (D - L);

    cout << X << endl;

    return 0;
}
