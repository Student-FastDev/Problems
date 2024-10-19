#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    const int repVariable = 1 << 21;
    int N;

    for (int i = 0; i < repVariable; ++i) {
        cout << "Darmowa setka na dobry start :D (powtórz 2^21 razy: wypisz dokładnie tę wiadomość, wczytaj int'a i go wypisz w osobnej linii)\n";
        cin >> N;
        cout << N << '\n';
    }

    return 0;
}
