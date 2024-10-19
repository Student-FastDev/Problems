#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Character {
    string name;
    long long hp;
    long long dmg;

    bool isAlive() const {
        return hp > 0;
    }
};

struct Monster {
    long long hp;
    long long dmg;
};

bool compareCharacters(const Character &a, const Character &b) {
    if (a.name != b.name)
        return a.name < b.name;
    if (a.hp != b.hp)
        return a.hp < b.hp;
    return a.dmg < b.dmg;
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int N, O;
    cin >> N;
    
    vector<Character> characters(N);
    for (int i = 0; i < N; ++i) {
        cin >> characters[i].name >> characters[i].hp >> characters[i].dmg;
    }
    
    cin >> O;
    vector<Monster> monsters(O);
    for (int i = 0; i < O; ++i) {
        cin >> monsters[i].hp >> monsters[i].dmg;
    }

    vector<Character> fighting, remaining(characters.begin(), characters.end());

    for (int i = 0; i < 3 && !remaining.empty(); ++i) {
        fighting.push_back(remaining.front());
        remaining.erase(remaining.begin());
    }

    for (Monster &monster : monsters) {
        while (monster.hp > 0 && !fighting.empty()) {
            long long totalDmg = 0;
            
            for (const Character &ch : fighting) {
                totalDmg += ch.dmg;
            }

            monster.hp -= totalDmg;

            if (monster.hp > 0) {
                for (Character &ch : fighting) {
                    ch.hp -= monster.dmg;
                }

                fighting.erase(remove_if(fighting.begin(), fighting.end(), [](const Character &ch) { return !ch.isAlive(); }), fighting.end());
                while (fighting.size() < 3 && !remaining.empty()) {
                    fighting.push_back(remaining.front());
                    remaining.erase(remaining.begin());
                }
            }
        }
    }

    vector<Character> survivors;
    for (const Character &ch : fighting) {
        if (ch.isAlive()) {
            survivors.push_back(ch);
        }
    }

    for (const Character &ch : remaining) {
        if (ch.isAlive()) {
            survivors.push_back(ch);
        }
    }

    sort(survivors.begin(), survivors.end(), compareCharacters);

    for (const Character &charac : survivors) {
        cout << charac.name << " " << charac.hp << " " << charac.dmg << endl;
    }

    return 0;
}