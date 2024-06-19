#include <iostream>

using namespace std;

int main()
{
    int n, z = 0;
    cin >> n;
    int tab[n];

    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    for (int i = 0; i < n; i++) {
        while (true) {
            tab[i] = tab[i] - 10;
            if (tab[i] > 0) {
                z++;
            }
            else {
                break;
            }
        }
    }

    cout << z;
}
