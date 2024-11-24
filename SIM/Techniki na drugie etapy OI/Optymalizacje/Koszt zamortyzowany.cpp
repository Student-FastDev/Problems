#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int maxHistogramArea(vector<int>& heights) {
    stack<int> S;
    int maxArea = 0;
    int index = 0;
    int N = heights.size();
    
    while (index < N) {
        if (S.empty() || heights[S.top()] <= heights[index]) {
            S.push(index++);
        } else {
            int top = S.top();
            S.pop();
            int area = heights[top] * (S.empty() ? index : index - S.top() - 1);
            maxArea = max(maxArea, area);
        }
    }
    
    while (!S.empty()) {
        int top = S.top();
        S.pop();
        int area = heights[top] * (S.empty() ? index : index - S.top() - 1);
        maxArea = max(maxArea, area);
    }
    
    return maxArea;
}

int maxRectangleArea(const vector<vector<int>>& field, int N) {
    vector<int> heights(N, 0);
    int maxArea = 0;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (field[i][j] == 0) {
                heights[j] += 1;
            } else {
                heights[j] = 0;
            }
        }
        
        maxArea = max(maxArea, maxHistogramArea(heights));
    }
    
    return maxArea;
}

int main() {
    int N;
    cin >> N;
    vector<vector<int>> field(N, vector<int>(N));
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> field[i][j];
        }
    }
    
    cout << maxRectangleArea(field, N) << endl;
    
    return 0;
}
