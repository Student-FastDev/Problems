#include <bits/stdc++.h>

#define LL long long
using namespace std;

const LL INF = LLONG_MAX;

int N, delayFirst, delaySecond, costFirst, costSecond, marketCost;
vector<int> dailyDemand, repairQueue, availableDays;

LL calculateCost(int initialArrows) {
    int remainingArrows = initialArrows;
    LL totalCost = static_cast<LL>(initialArrows) * marketCost;

    iota(availableDays.begin(), availableDays.end(), 0);
    fill(repairQueue.begin(), repairQueue.end(), 0);

    function<int(int)> findAvailableDay;
    findAvailableDay = [&](int day) -> int {
        if (day < 0) return 0;
        return availableDays[day] == day ? day : availableDays[day] = findAvailableDay(availableDays[day]);
    };

    auto removeDay = [&](int day) {
        availableDays[day] = day - 1;
    };

    for (int day = 1; day <= N; ++day) {
        int demand = dailyDemand[day];
        int fromCarry = min(remainingArrows, demand);
        demand -= fromCarry;
        remainingArrows -= fromCarry;

        int availableDay;
        while (demand > 0 && (availableDay = findAvailableDay(day - delaySecond))) {
            int arrowsUsed = min(repairQueue[availableDay], demand);
            totalCost += static_cast<LL>(arrowsUsed) * costSecond;
            demand -= arrowsUsed;
            repairQueue[availableDay] -= arrowsUsed;
            if (repairQueue[availableDay] == 0) removeDay(availableDay);
        }

        while (demand > 0 && (availableDay = findAvailableDay(day - delayFirst))) {
            int arrowsUsed = min(repairQueue[availableDay], demand);
            totalCost += static_cast<LL>(arrowsUsed) * costFirst;
            demand -= arrowsUsed;
            repairQueue[availableDay] -= arrowsUsed;
            if (repairQueue[availableDay] == 0) removeDay(availableDay);
        }

        if (demand > 0) return INF;
        repairQueue[day] = dailyDemand[day];
    }

    return totalCost;
}

LL findOptimalCost() {
    int left = 0, right = accumulate(dailyDemand.begin() + 1, dailyDemand.end(), 0);
    while (left < right) {
        int mid = (left + right) / 2;
        if (calculateCost(mid) >= calculateCost(mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return calculateCost(left);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> delayFirst >> delaySecond >> costFirst >> costSecond >> marketCost;
    dailyDemand.resize(N + 1);
    repairQueue.resize(N + 1);
    availableDays.resize(N + 1);

    for (int i = 1; i <= N; ++i) {
        cin >> dailyDemand[i];
    }

    if (delayFirst > delaySecond) {
        swap(delayFirst, delaySecond);
        swap(costFirst, costSecond);
    }

    if (costFirst < costSecond) {
        costSecond = costFirst;
    }

    cout << findOptimalCost() << endl;
    return 0;
}
