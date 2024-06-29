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

    int number_of_rocks, id_frog_rock;
    long long frog_jump;
    cin >> number_of_rocks >> id_frog_rock >> frog_jump;

    frog_jump *= frog_jump;

    vector<pair<long long, long long>> rocks(number_of_rocks + 1);

    for (int i = 1; i <= number_of_rocks; i++)
        cin >> rocks[i].first >> rocks[i].second;

    vector<vector<int>> ids_rocks_possible_to_jump(number_of_rocks + 1);

    for (int i = 1; i <= number_of_rocks; i++) {
        for (int j = 1; j <= number_of_rocks; j++) {
            long long distance = (rocks[i].first - rocks[j].first) * (rocks[i].first - rocks[j].first) +
                                 (rocks[i].second - rocks[j].second) * (rocks[i].second - rocks[j].second);
            if (distance <= frog_jump)
                ids_rocks_possible_to_jump[i].push_back(j);
        }
    }

    unordered_set<int> seen_rocks;

    long long the_farthest_distance = 0;
    int id_the_farthest_rock_the_frog_can_jump_to = 0;

    stack<int> rocks_to_check;
    rocks_to_check.push(id_frog_rock);

    while (!rocks_to_check.empty()) {
        int current_rock_id = rocks_to_check.top();
        rocks_to_check.pop();

        seen_rocks.insert(current_rock_id);

        long long distance = (rocks[id_frog_rock].first - rocks[current_rock_id].first) * (rocks[id_frog_rock].first - rocks[current_rock_id].first) +
                             (rocks[id_frog_rock].second - rocks[current_rock_id].second) * (rocks[id_frog_rock].second - rocks[current_rock_id].second);

        if (distance > the_farthest_distance) {
            the_farthest_distance = distance;
            id_the_farthest_rock_the_frog_can_jump_to = current_rock_id;
        }

        for (int next_rock_id : ids_rocks_possible_to_jump[current_rock_id]) {
            if (seen_rocks.count(next_rock_id) == 0) {
                rocks_to_check.push(next_rock_id);
            }
        }
    }

    cout << fixed << setprecision(3) << sqrt((double)the_farthest_distance) + sqrt((double)frog_jump);

    return 0;
}
