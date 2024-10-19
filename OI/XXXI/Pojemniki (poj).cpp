#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
    long long N, K;
    cin >> N >> K;
    
    set<pair<long long, long long>> containerArray;
    vector<pair<pair<long long, long long>, pair<long long, long long>>> finalContainers;
    long long containerSum = 0;
    
    
    for(long long i = 0; i < N; i++) {
        long long A;
        cin >> A;
        
        containerSum += A;
        
        if(A == K) {
            finalContainers.push_back({{A, i}, {-1, -1}});
        } else {
            containerArray.insert({A, i});   
        }
    }
    
    if(containerSum > (N*K)) {
        cout << "NIE" << endl;
        return 0;
    }
    
    while(!containerArray.empty()) {
        auto firstElement = containerArray.begin();
        auto lastElement = --containerArray.end();
        
        if(firstElement == lastElement || firstElement->first + lastElement->first < K) {
            break;
        }
        
        long long needTo = K - firstElement->first;
        finalContainers.push_back({{firstElement->first, firstElement->second}, {needTo, lastElement->second}});
        
        containerArray.erase(firstElement);
        
        if(lastElement->first-needTo > 0) {
            pair<long long, long long> updatedLast = {lastElement->first-needTo, lastElement->second};
            containerArray.erase(lastElement);
            containerArray.insert(updatedLast);
        } else {
            containerArray.erase(lastElement);
        }
    }
    
    while(!containerArray.empty()) {
        auto firstElement = containerArray.begin();
        finalContainers.push_back({{firstElement->first, firstElement->second}, {-1, -1}});
        containerArray.erase(firstElement);
    }
    
    
    if(finalContainers.size() <= N) {
        cout << "TAK" << endl;
        for (const auto& container : finalContainers) {
            long long amount1 = container.first.first, index1 = container.first.second;
            long long amount2 = container.second.first, index2 = container.second.second;
            
            if (amount2 == -1) {
                cout << "1 " << index1+1 << " " << amount1 << endl;
            } else {
                cout << "2 " << index1+1 << " " << amount1 << " " << index2+1 << " " << amount2 << endl;
            }
        }
        
        for(long long i = finalContainers.size(); i < N; i++) {
            cout << 0 << endl;
        }
    }
    else {
        cout << "NIE" << endl;
    }
}
