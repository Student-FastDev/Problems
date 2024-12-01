#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Robot {
    int strength;
    int agility;
    int index;
};

void inputRobots(vector<Robot> &robotsArray, int n) {
    for (int i = 0; i < n; ++i) {
        cin >> robotsArray[i].strength >> robotsArray[i].agility;
        robotsArray[i].index = i;
    }
}

void sortRobots(vector<Robot> &robotsArray) {
    sort(robotsArray.begin(), robotsArray.end(), [](const Robot &a, const Robot &b) {
        return (a.strength < b.strength) || (a.strength == b.strength && a.agility > b.agility);
    });
}

vector<Robot> determineNonDeleted(const vector<Robot> &robotsArray, vector<bool> &canArrayBeDeleted) {
    int n = robotsArray.size();
    vector<Robot> nonDeletedAmount;
    
    int maxStrength = robotsArray[n - 1].strength;
    
    vector<vector<Robot>> buckets(maxStrength + 1);

    for (const auto& robot : robotsArray) {
        buckets[robot.strength].push_back(robot);
    }
    
    int maxAgilitySoFar = -1;
    
    for (int strength = maxStrength; strength >= 0; --strength) {
        for (const auto& robot : buckets[strength]) {
            if (robot.agility <= maxAgilitySoFar) {
                canArrayBeDeleted[robot.index] = true;
            } else {
                nonDeletedAmount.push_back(robot);
                maxAgilitySoFar = robot.agility;
            }
        }
    }

    return nonDeletedAmount;
}

int main() {
    int N;
    cin >> N;
    
    if(N == 0) {
        cout << "TAK" << endl;
        return 0;
    }

    vector<Robot> robotsArray(N);
    vector<bool> canArrayBeDeleted(N, 0);
    inputRobots(robotsArray, N);
    sortRobots(robotsArray);
    vector<Robot> nonDeletedVector = determineNonDeleted(robotsArray, canArrayBeDeleted);
    
    int nonDeletedAmount = nonDeletedVector.size();
    
    int minFirst = 1e9;
    int maxFirst = -1;
    int minSecond = 1e9;
    int maxSecond = -1;
    
    for (const auto &robot : nonDeletedVector) {
        minFirst = min(minFirst, robot.strength);
        maxFirst = max(maxFirst, robot.strength);
        minSecond = min(minSecond, robot.agility);
        maxSecond = max(maxSecond, robot.agility);
    }
    
    bool uniqueConnection = false;
    for(int i = 0; i < N; i++) {
        if (((robotsArray[i].strength > minFirst && robotsArray[i].agility < maxSecond) || (robotsArray[i].strength < maxFirst && robotsArray[i].agility > minSecond)) && canArrayBeDeleted[robotsArray[i].index]) {
            uniqueConnection = true;
        }
    }

    if (nonDeletedAmount % 2 == 1) {
        cout << (uniqueConnection ? "TAK" : "NIE") << endl;
    } else {
        cout << "TAK" << endl;
    }

    return 0;
}
