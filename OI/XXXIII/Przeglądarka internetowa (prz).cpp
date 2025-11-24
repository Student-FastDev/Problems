// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.doesEnd(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

struct Node {
    Node* charactersArray[26] = {nullptr};
    bool doesEnd = false;
    int nodeValue = -1;
};

int getValue(Node* node) {
    if (node->nodeValue >= 0) return node->nodeValue;
    int maxChildValue = -1;
    bool hasChild = false;
    for (int i = 0; i < 26; i++) {
        if (node->charactersArray[i]) {
            hasChild = true;
            int childValue = getValue(node->charactersArray[i]);
            maxChildValue = max(maxChildValue, childValue);
        }
    }
    node->nodeValue = (hasChild ? 1 + maxChildValue : 0);
    return node->nodeValue;
}

void traverseGraph(Node* node, int depth, string& answer, vector<char>& path) {
    bool hasCharacter = false;
    for (int i = 0; i < 26; i++) {
        if (node->charactersArray[i]) {
            hasCharacter = true;
            break;
        }
    }
    if (node->doesEnd) {
        answer += 'E';
        if (hasCharacter) {
            answer += 'T';
        }
    }
    vector<pii> childrenArray;
    for (int i = 0; i < 26; i++) {
        if (node->charactersArray[i]) {
            childrenArray.emplace_back(node->charactersArray[i]->nodeValue, i);
        }
    }
    sort(all(childrenArray));
    int M = size(childrenArray);
    for (int i = 0; i < M; i++) {
        int childValue = childrenArray[i].first;
        int currentIndex = childrenArray[i].second;
        char currentCharacter = 'a' + currentIndex;
        answer += currentCharacter;
        path.push_back(currentCharacter);
        traverseGraph(node->charactersArray[currentIndex], depth + 1, answer, path);
        path.pop_back();
        if (i < M - 1) {
            int costTab = 2 + childValue;
            int costRe = depth;
            if (costRe < costTab) {
                for (char charactersArray : path) {
                    answer += charactersArray;
                }
            } else {
                answer += 'T';
                for (int j = 0; j < 1 + childValue; j++) {
                    answer += 'B';
                }
            }
        }
    }
}

void solveTestCase() {
    int N;
    cin >> N;
    Node* root = new Node();
    for (int i = 0; i < N; i++) {
        string S;
        cin >> S;
        Node* currentNode = root;
        for (char c : S) {
            int currentIndex = c - 'a';
            if (!currentNode->charactersArray[currentIndex]) {
                currentNode->charactersArray[currentIndex] = new Node();
            }
            currentNode = currentNode->charactersArray[currentIndex];
        }
        currentNode->doesEnd = true;
    }
    getValue(root);
    string stringAnswer = "";
    vector<char> finalPath;
    traverseGraph(root, 0, stringAnswer, finalPath);
    cout << size(stringAnswer) << endl;
    cout << stringAnswer << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}