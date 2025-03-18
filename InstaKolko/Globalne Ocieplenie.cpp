#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<int> heightArray(N);
    for (int i = 0; i < N; ++i) {
        cin >> heightArray[i];
    }

    vector<pair<int, int>> sortedHeight;
    for (int i = 0; i < N; ++i) {
        sortedHeight.emplace_back(heightArray[i], i);
    }
    sort(sortedHeight.begin(), sortedHeight.end());

    vector<int> result;
    int currentIslands = 1;
    vector<bool> floodedArray(N, false);
    int prevHeight = -1;
    int maxHeight = *max_element(heightArray.begin(), heightArray.end());

    result.push_back(currentIslands);
    prevHeight = 0;

    int i = 0;
    while (i < N) {
        int currentHeight = sortedHeight[i].first;
        vector<int> indices;
        while (i < N && sortedHeight[i].first == currentHeight) {
            indices.push_back(sortedHeight[i].second);
            ++i;
        }

        if (currentHeight > prevHeight + 1) {
            int fillStart = prevHeight + 1;
            int fillEnd = currentHeight - 1;
            int count = fillEnd - fillStart + 1;
            for (int j = 0; j < count; ++j) {
                result.push_back(currentIslands);
            }
        }

        int sumDelta = 0;
        for (int idx : indices) {
            bool left_flooded = (idx == 0) || floodedArray[idx - 1];
            bool right_flooded = (idx == N - 1) || floodedArray[idx + 1];
            int delta = ( (left_flooded ? 0 : 1) + (right_flooded ? 0 : 1) ) - 1;
            sumDelta += delta;
            floodedArray[idx] = true;
        }
        currentIslands += sumDelta;

        result.push_back(currentIslands);
        prevHeight = currentHeight;
    }

    if (prevHeight < maxHeight) {
        int fillStart = prevHeight + 1;
        int count = maxHeight - prevHeight;
        for (int j = 0; j < count; ++j) {
            result.push_back(currentIslands);
        }
    }

    auto it = find(result.begin(), result.end(), 0);
    if (it != result.end()) {
        result.resize(it - result.begin() + 1);
    }

    for (size_t j = 0; j < result.size(); ++j) {
        if (j > 0) {
            cout << ' ';
        }
        cout << result[j];
    }
    cout << endl;

    return 0;
}
