#include "bits/stdc++.h"

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> T(N);
    for (int i = 0; i < N; i++) cin >> T[i];

    int id = 0, granica = 0, klikniecia = 0;

    priority_queue<int> kandydaci;

    while (granica < N) {
        while (id <= granica) {
            kandydaci.push(T[id]);
            id++;
        }
        int element_klikany = kandydaci.top();
        kandydaci.pop();

        granica += element_klikany + 1;
        klikniecia++;
    }

    cout << klikniecia;
}
