// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

struct Ingredient {
    string name;
    int count;
};

struct Recipe {
    string resultName;
    vector<Ingredient> ingredients;
};

void solveTestCase() {
    int numAllies, numBasic, numComposite, numPurchases;
    if (!(cin >> numAllies >> numBasic >> numComposite >> numPurchases)) return;

    for (int i = 0; i < numBasic; ++i) {
        string basicArtifactName;
        cin >> basicArtifactName;
    }

    string dummyLine;
    getline(cin, dummyLine);

    vector<Recipe> artifactRecipes;
    for (int i = 0; i < numComposite; ++i) {
        string lineDescription;
        getline(cin, lineDescription);

        for (char &character : lineDescription) {
            if (character == ':' || character == ',') character = ' ';
        }

        stringstream stringStream(lineDescription);
        string resultName;
        stringStream >> resultName;

        Recipe newRecipe;
        newRecipe.resultName = resultName;

        string ingredientName;
        int ingredientCount;
        while (stringStream >> ingredientName >> ingredientCount) {
            newRecipe.ingredients.push_back({ingredientName, ingredientCount});
        }
        artifactRecipes.push_back(newRecipe);
    }

    vector<map<string, int>> allyInventories(numAllies + 1);

    for (int i = 0; i < numPurchases; ++i) {
        int allyIndex;
        string purchasedArtifactName;
        cin >> allyIndex >> purchasedArtifactName;

        allyInventories[allyIndex][purchasedArtifactName]++;

        for (const auto& currentRecipe : artifactRecipes) {
            bool canCraft = true;
            for (const auto& ingredient : currentRecipe.ingredients) {
                auto iterator = allyInventories[allyIndex].find(ingredient.name);
                if (iterator == allyInventories[allyIndex].end() || iterator->second < ingredient.count) {
                    canCraft = false;
                    break;
                }
            }

            if (canCraft) {
                for (const auto& ingredient : currentRecipe.ingredients) {
                    allyInventories[allyIndex][ingredient.name] -= ingredient.count;
                    if (allyInventories[allyIndex][ingredient.name] == 0) {
                        allyInventories[allyIndex].erase(ingredient.name);
                    }
                }
                allyInventories[allyIndex][currentRecipe.resultName]++;
                break;
            }
        }
    }

    for (int i = 1; i <= numAllies; ++i) {
        vector<pair<string, int>> currentAllyArtifacts;
        for (auto const& [name, count] : allyInventories[i]) {
            currentAllyArtifacts.push_back({name, count});
        }

        cout << size(currentAllyArtifacts) << endl;
        for (const auto& artifactPair : currentAllyArtifacts) {
            cout << artifactPair.first << " " << artifactPair.second << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while (T--) {
        solveTestCase();
    }
    return 0;
}