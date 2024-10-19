#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {
    int index;
    int a, b, c;
};

struct CustomComparator {
    int first, second, third;
    CustomComparator(int f, int s, int t) : first(f), second(s), third(t) {}

    bool operator()(const Block &block1, const Block &block2) const {
        if (block1.a != block2.a) return block1.a > block2.a;
        if (block1.b != block2.b) return block1.b > block2.b;
        return block1.c > block2.c;
    }
};

int main() {
    int N;
    cin >> N;
    vector<Block> blocks(N);

    for (int i = 0; i < N; ++i) {
        blocks[i].index = i + 1;
        cin >> blocks[i].a >> blocks[i].b >> blocks[i].c;
    }

    int order[3];
    cin >> order[0] >> order[1] >> order[2];

    for (auto &block : blocks) {
        int attributes[3] = {block.a, block.b, block.c};
        block.a = attributes[order[0] - 1];
        block.b = attributes[order[1] - 1];
        block.c = attributes[order[2] - 1];
    }

    sort(blocks.begin(), blocks.end(), CustomComparator(order[0], order[1], order[2]));

    for (const auto &block : blocks) {
        cout << block.index << " ";
    }
    cout << endl;

    return 0;
}