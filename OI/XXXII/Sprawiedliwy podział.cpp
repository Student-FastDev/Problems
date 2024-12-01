#include <bits/stdc++.h>
using namespace std;

long long MAX_N = 1e9 + 1;
long long SEED = 123456789;

vector<long long> bajtynaArray;
vector<long long> bitekArray;

vector<long long> staticBajtynaArray;
vector<long long> staticBitekArray;

unordered_map<long long, long long> valueToIndex;

class MinList {
    struct Node {
        long long value;
        Node* prev;
        Node* next;
    };

    Node* dummyHead;
    vector<Node*> nodes;

public:
    MinList(vector<long long>& sortedValues) {
        dummyHead = new Node{LLONG_MIN, nullptr, nullptr};
        nodes.resize(sortedValues.size(), nullptr);
        Node* prev = dummyHead;

        for (long long idx = 0; idx < sortedValues.size(); idx++) {
            Node* curr = new Node{sortedValues[idx], prev, nullptr};
            prev->next = curr;
            nodes[idx] = curr;
            prev = curr;
        }
        prev->next = nullptr;
    }

    void remove(long long idx) {
        Node* node = nodes[idx];
        if (node) {
            if (node->prev) {
                node->prev->next = node->next;
            }
            if (node->next) {
                node->next->prev = node->prev;
            }
            nodes[idx] = nullptr;
        }
    }

    long long getMin() {
        return dummyHead->next ? dummyHead->next->value : LLONG_MAX;
    }

    long long minIfRemoved(long long idx) {
        Node* node = nodes[idx];
        if (!node) return getMin();

        long long currentMin = getMin();
        if (currentMin != node->value) return currentMin;

        return node->next ? node->next->value : LLONG_MAX;
    }

    ~MinList() {
        Node* curr = dummyHead;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

pair<bool, vector<bool>> findSolution(long long N, vector<long long>& sortedValues) {
    vector<bool> bestAssignment(N, false);
    long long sumA1 = 0, sumA2 = 0;
    long long totalSum1 = 0, totalSum2 = 0;
    long long minBitekInB1 = LLONG_MAX;

    for (long long i = 0; i < N; i++) {
        sumA1 += bajtynaArray[i];
        sumA2 += bitekArray[i];
        totalSum1 += bajtynaArray[i];
        totalSum2 += bitekArray[i];
    }

    for (long long i = 0; i < N; i++) {
        valueToIndex[sortedValues[i]] = MAX_N;
    }

    for (long long i = 0; i < N; i++) {
        valueToIndex[sortedValues[i]] = min(valueToIndex[sortedValues[i]], i);
    }

    MinList minList(sortedValues);

    for (long long i = 0; i < N; i++) {
        long long tempSumA1 = sumA1 - bajtynaArray[i];
        long long tempSumA2 = sumA2 - bitekArray[i];

        long long tempMinBitekInB1 = min(minBitekInB1, bajtynaArray[i]);
        long long indexInSorted = valueToIndex[bitekArray[i]];
        long long tempMinInA2 = minList.minIfRemoved(indexInSorted);

        if (2 * tempSumA1 >= totalSum1 - tempMinBitekInB1) {
            sumA1 = tempSumA1;
            sumA2 = tempSumA2;
            minBitekInB1 = tempMinBitekInB1;

            minList.remove(indexInSorted);
            bestAssignment[i] = true;

            valueToIndex[bitekArray[i]]++;
            if (2 * sumA2 <= totalSum2 + tempMinInA2) {
                return {true, bestAssignment};
            }
        }
    }

    return {false, bestAssignment};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long N;
    cin >> N;

    if(N == 1) {
        cout << "0" << endl;
        return 0;
    }

    bajtynaArray.resize(N);
    bitekArray.resize(N);

    staticBajtynaArray.resize(N);
    staticBitekArray.resize(N);

    for (long long i = 0; i < N; i++) {
        cin >> bajtynaArray[i];
        staticBajtynaArray[i] = bajtynaArray[i];
    }
    for (long long i = 0; i < N; i++) {
        cin >> bitekArray[i];
        staticBitekArray[i] = bitekArray[i];
    }

    random_device rd;
    mt19937 g(SEED);

    vector<long long> valuesArray(bitekArray.begin(), bitekArray.end());
    sort(valuesArray.begin(), valuesArray.end());

    bool solutionFound = false;
    pair<bool, vector<bool>> scoreArray;
    vector<bool> finalScore(N);
    vector<long long> indices(N);
    iota(indices.begin(), indices.end(), 0);

    while (!solutionFound) {
        shuffle(indices.begin(), indices.end(), g);

        vector<long long> shuffledBajtyna(N), shuffledBitek(N);
        for (long long i = 0; i < N; i++) {
            shuffledBajtyna[i] = staticBajtynaArray[indices[i]];
            shuffledBitek[i] = staticBitekArray[indices[i]];
        }

        bajtynaArray = shuffledBajtyna;
        bitekArray = shuffledBitek;

        scoreArray = findSolution(N, valuesArray);
        if(scoreArray.first == true) {
            for (long long i = 0; i < N; i++) {
                finalScore[indices[i]] = scoreArray.second[i];
            }
            break;
        }
    }

    for (long long i = 0; i < N; i++) {
        cout << finalScore[i] << " ";
    }
    cout << endl;

    return 0;
}
