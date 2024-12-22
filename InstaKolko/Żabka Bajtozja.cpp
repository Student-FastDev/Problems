#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <iomanip>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);

    int numberOfRocks, idFrogRock;
    long long frogJump;
    cin >> numberOfRocks >> idFrogRock >> frogJump;

    frogJump *= frogJump;

    vector<pair<long long, long long>> rocks(numberOfRocks + 1);

    for (int i = 1; i <= numberOfRocks; i++)
        cin >> rocks[i].first >> rocks[i].second;

    vector<vector<int>> idsRocksPossibleToJump(numberOfRocks + 1);

    for (int i = 1; i <= numberOfRocks; i++) {
        for (int j = 1; j <= numberOfRocks; j++) {
            long long distance = (rocks[i].first - rocks[j].first) * (rocks[i].first - rocks[j].first) +
                                 (rocks[i].second - rocks[j].second) * (rocks[i].second - rocks[j].second);
            if (distance <= frogJump)
                idsRocksPossibleToJump[i].push_back(j);
        }
    }

    unordered_set<int> seenRocks;

    long long theFarthestDistance = 0;
    int idTheFarthestRockTheFrogCanJumpTo = 0;

    stack<int> rocksToCheck;
    rocksToCheck.push(idFrogRock);

    while (!rocksToCheck.empty()) {
        int current_rock_id = rocksToCheck.top();
        rocksToCheck.pop();

        seenRocks.insert(current_rock_id);

        long long distance = (rocks[idFrogRock].first - rocks[current_rock_id].first) * (rocks[idFrogRock].first - rocks[current_rock_id].first) +
                             (rocks[idFrogRock].second - rocks[current_rock_id].second) * (rocks[idFrogRock].second - rocks[current_rock_id].second);

        if (distance > theFarthestDistance) {
            theFarthestDistance = distance;
            idTheFarthestRockTheFrogCanJumpTo = current_rock_id;
        }

        for (int nextRockId : idsRocksPossibleToJump[current_rock_id]) {
            if (seenRocks.count(nextRockId) == 0) {
                rocksToCheck.push(nextRockId);
            }
        }
    }

    cout << fixed << setprecision(3) << sqrt((double)theFarthestDistance) + sqrt((double)frogJump);

    return 0;
}
