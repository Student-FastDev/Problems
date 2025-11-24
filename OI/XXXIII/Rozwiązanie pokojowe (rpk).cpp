// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
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

const ll INF = INT_MAX;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

enum class MoveDirection { Up, Down, Left, Right, Magic };
using Move = pair<int, MoveDirection>;

class PuzzleSolver {
public:
    PuzzleSolver(const vector<vector<int>>& startMatrix, const vector<vector<int>>& goalMatrix)
        : rows((int)size(startMatrix)),
          columns(rows ? (int)size(startMatrix[0]) : 0),
          current(startMatrix),
          goal(goalMatrix) {

        if (rows == 0 || columns == 0 || (int)size(goal) != rows || (int)size(goal[0]) != columns) {
            throw invalid_argument("Invalid matrix dimensions.");
        }

        goalPositions.reserve((int)rows * (int)columns * 2);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                goalPositions[goal[r][c]] = {r, c};
            }
        }
        auto itBlankGoal = goalPositions.find(0);
        if (itBlankGoal == goalPositions.end()) throw invalid_argument("Goal matrix must contain a 0 (blank).");
        goalBlankRow = itBlankGoal->second.first;
        goalBlankCol = itBlankGoal->second.second;

        currentPositions.reserve((int)rows * (int)columns * 2);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                currentPositions[current[r][c]] = {r, c};
            }
        }
        auto itBlank = currentPositions.find(0);
        if (itBlank == currentPositions.end()) throw invalid_argument("Start matrix must contain a 0 (blank).");
        blankRow = itBlank->second.first;
        blankColumn = itBlank->second.second;
    }

    bool solve(vector<Move>& movesArray) {
        moves = &movesArray;
        if (isEqualToGoal()) return true;

        topRowProgress = 0;
        leftColumnProgress = 0;
        bottomRowProgress = rows - 1;
        rightColumnProgress = columns - 1;

        rowInProgress = 0;
        columnInProgress = 0;
        rowProgressColumn = 0;
        columnProgressRow = 0;
        solvingRowTopDown = true;
        solvingColumnLeftRight = true;

        int globalGuard = 0;
        while (!isEqualToGoal()) {
            if (++globalGuard > rows * columns * 10000) return false;

            while (moreThanTwoUnsolvedRows() && moreUnsolvedRowsThanColumns()) {
                solvingRow = true;
                if (rowFinishedAndNotInGoalRow()) {
                    if (solvingRowTopDown) {
                        ++topRowProgress;
                        rowInProgress = topRowProgress;
                    } else {
                        --bottomRowProgress;
                        rowInProgress = bottomRowProgress;
                    }
                    rowProgressColumn = 0;
                } else {
                    if (solvingRowTopDown) {
                        if (rowInProgress == goalBlankRow) {
                            solvingRowTopDown = false;
                            rowInProgress = bottomRowProgress;
                        } else {
                            rowInProgress = topRowProgress;
                        }
                    } else {
                        rowInProgress = bottomRowProgress;
                    }

                    int rowIteration = 0;
                    int targetValue = goal[rowInProgress][rowProgressColumn];

                    while (!isRowEqual(rowInProgress)) {
                        if (rowIteration > 1) return false;

                        if (targetValue != goal[rowInProgress][rightColumnProgress - 1]) {
                            moveTile(targetValue, goalPositions[targetValue].first, goalPositions[targetValue].second);
                            ++rowProgressColumn;
                            targetValue = goal[rowInProgress][rowProgressColumn];
                        } else {
                            const int lastValue = goal[rowInProgress][rightColumnProgress];
                            if (solvingRowTopDown) {
                                moveTile(lastValue, goalPositions[lastValue].first + 2, goalPositions[lastValue].second);
                                moveTile(targetValue, goalPositions[lastValue].first, goalPositions[lastValue].second);
                                moveTile(lastValue, goalPositions[lastValue].first + 1, goalPositions[lastValue].second);

                                moveBlankToColumn(goalPositions[lastValue].second - 1);
                                moveBlankToRow(goalPositions[lastValue].first);
                                slideRight();
                                slideDown();

                                ++rowIteration;
                                rowProgressColumn = 0;
                                targetValue = goal[rowInProgress][rowProgressColumn];
                            } else {
                                moveTile(lastValue, goalPositions[lastValue].first - 2, goalPositions[lastValue].second);
                                moveTile(targetValue, goalPositions[lastValue].first,     goalPositions[lastValue].second);
                                moveTile(lastValue,  goalPositions[lastValue].first - 1, goalPositions[lastValue].second);

                                moveBlankToColumn(goalPositions[lastValue].second - 1);
                                moveBlankToRow(goalPositions[lastValue].first);
                                slideRight();
                                slideUp();

                                ++rowIteration;
                                rowProgressColumn = 0;
                                targetValue = goal[rowInProgress][rowProgressColumn];
                            }
                        }
                    }
                }
            }

            while (moreThanTwoUnsolvedColumns() && moreUnsolvedColumnsThanRows()) {
                solvingRow = false;

                if (columnFinishedAndNotInGoalColumn()) {
                    columnProgressRow = 0;
                    if (solvingColumnLeftRight) {
                        ++leftColumnProgress;
                        columnInProgress = leftColumnProgress;
                    } else {
                        --rightColumnProgress;
                        columnInProgress = rightColumnProgress;
                    }
                } else {
                    if (solvingColumnLeftRight) {
                        if (columnInProgress == goalBlankCol) {
                            solvingColumnLeftRight = false;
                            columnInProgress = rightColumnProgress;
                        } else {
                            columnInProgress = leftColumnProgress;
                        }
                    } else {
                        columnInProgress = rightColumnProgress;
                    }

                    int columnIteration = 0;
                    int targetValue = goal[topRowProgress][columnInProgress];

                    while (!isColumnEqual(columnInProgress)) {
                        if (columnIteration > 1) return false;

                        if (targetValue != goal[bottomRowProgress - 1][columnInProgress]) {
                            moveTile(targetValue, goalPositions[targetValue].first, goalPositions[targetValue].second);
                            ++columnProgressRow;
                            targetValue = goal[columnProgressRow][columnInProgress];
                        } else {
                            const int lastValue = goal[bottomRowProgress][columnInProgress];
                            if (solvingColumnLeftRight) {
                                moveTile(lastValue, goalPositions[lastValue].first, goalPositions[lastValue].second + 2);
                                moveTile(targetValue, goalPositions[lastValue].first, goalPositions[lastValue].second);
                                moveTile(lastValue,  goalPositions[lastValue].first, goalPositions[lastValue].second + 1);

                                moveBlankToRow(goalPositions[lastValue].first - 1);
                                moveBlankToColumn(goalPositions[lastValue].second);
                                slideDown();
                                slideRight();

                                ++columnIteration;
                                columnProgressRow = 0;
                                targetValue = goal[columnProgressRow][columnInProgress];
                            } else {
                                moveTile(lastValue, goalPositions[lastValue].first, goalPositions[lastValue].second - 2);
                                moveTile(targetValue, goalPositions[lastValue].first, goalPositions[lastValue].second);
                                moveTile(lastValue,  goalPositions[lastValue].first, goalPositions[lastValue].second - 1);

                                moveBlankToRow(goalPositions[lastValue].first - 1);
                                moveBlankToColumn(goalPositions[lastValue].second);
                                slideDown();
                                slideLeft();

                                ++columnIteration;
                                columnProgressRow = 0;
                                targetValue = goal[columnProgressRow][columnInProgress];
                            }
                        }
                    }
                }
            }

            if (unsolvedPuzzleIsTwoByTwo()) {
                int iterations = 0;
                bool slideVertically = true;

                while (!isEqualToGoal()) {
                    if (slideVertically) {
                        if (canSlideDown() && (blankRow - 1) <= (goalBlankRow - 1)) {
                            slideDown();
                        } else if (canSlideUp()) {
                            slideUp();
                        } else {
                            return false;
                        }
                        slideVertically = false;
                    } else {
                        if (canSlideRight() && (blankColumn + 1) <= (goalBlankCol + 1)) {
                            slideRight();
                        } else if (canSlideLeft()) {
                            slideLeft();
                        } else {
                            return false;
                        }
                        slideVertically = true;
                    }

                    ++iterations;
                    if (iterations > 20) return false;
                }
            }
        }

        return true;
    }

private:
    int rows{}, columns{};
    vector<vector<int>> current, goal;
    unordered_map<int, pii> goalPositions;
    unordered_map<int, pii> currentPositions;

    int blankRow{}, blankColumn{};
    int goalBlankRow{}, goalBlankCol{};

    int topRowProgress{}, bottomRowProgress{}, leftColumnProgress{}, rightColumnProgress{};

    int rowInProgress{}, columnInProgress{};
    int rowProgressColumn{}, columnProgressRow{};

    bool solvingRowTopDown{true};
    bool solvingColumnLeftRight{true};
    bool solvingRow{true};

    vector<Move>* moves{nullptr};

    bool isEqualToGoal() const { return current == goal; }

    bool isRowEqual(int r) const {
        for (int c = 0; c < columns; ++c)
            if (current[r][c] != goal[r][c]) return false;
        return true;
    }

    bool isColumnEqual(int c) const {
        for (int r = 0; r < rows; ++r)
            if (current[r][c] != goal[r][c]) return false;
        return true;
    }

    bool canSlideUp() const    { return blankRow > 0; }
    bool canSlideDown() const  { return blankRow + 1 < rows; }
    bool canSlideLeft() const  { return blankColumn > 0; }
    bool canSlideRight() const { return blankColumn + 1 < columns; }

    void slideUp() {
        if (!canSlideUp()) throw runtime_error("slideUp out of bounds.");
        int previousBlankR = blankRow, previousBlankC = blankColumn;
        int tile = current[blankRow - 1][blankColumn];
        swap(current[blankRow][blankColumn], current[blankRow - 1][blankColumn]);
        --blankRow;
        currentPositions[0] = {blankRow, blankColumn};
        currentPositions[tile] = {previousBlankR, previousBlankC};
        if (moves) moves->push_back({tile, MoveDirection::Up});
    }

    void slideDown() {
        if (!canSlideDown()) throw runtime_error("slideDown out of bounds.");
        int previousBlankR = blankRow, previousBlankC = blankColumn;
        int tile = current[blankRow + 1][blankColumn];
        swap(current[blankRow][blankColumn], current[blankRow + 1][blankColumn]);
        ++blankRow;
        currentPositions[0] = {blankRow, blankColumn};
        currentPositions[tile] = {previousBlankR, previousBlankC};
        if (moves) moves->push_back({tile, MoveDirection::Down});
    }

    void slideLeft() {
        if (!canSlideLeft()) throw runtime_error("slideLeft out of bounds.");
        int previousBlankR = blankRow, previousBlankC = blankColumn;
        int tile = current[blankRow][blankColumn - 1];
        swap(current[blankRow][blankColumn], current[blankRow][blankColumn - 1]);
        --blankColumn;
        currentPositions[0] = {blankRow, blankColumn};
        currentPositions[tile] = {previousBlankR, previousBlankC};
        if (moves) moves->push_back({tile, MoveDirection::Left});
    }

    void slideRight() {
        if (!canSlideRight()) throw runtime_error("slideRight out of bounds.");
        int previousBlankR = blankRow, previousBlankC = blankColumn;
        int tile = current[blankRow][blankColumn + 1];
        swap(current[blankRow][blankColumn], current[blankRow][blankColumn + 1]);
        ++blankColumn;
        currentPositions[0] = {blankRow, blankColumn};
        currentPositions[tile] = {previousBlankR, previousBlankC};
        if (moves) moves->push_back({tile, MoveDirection::Right});
    }

    struct Tile {
        int value;
        int row;
        int column;
        int goalRow;
        int goalColumn;
    };

    void moveTile(int value, int destinationRow, int destionationColumn) {
        destinationRow = max(0, min(destinationRow, rows - 1));
        destionationColumn = max(0, min(destionationColumn, columns - 1));

        auto iterator = currentPositions.find(value);
        if (iterator == currentPositions.end()) throw runtime_error("Tile not found");
        int vRow = iterator->second.first;
        int vCol = iterator->second.second;

        if (vRow == destinationRow && vCol == destionationColumn) return;

        Tile T{value, vRow, vCol, destinationRow, destionationColumn};

        if (solvingRow) {
            while (T.column > destionationColumn) { moveTileLeft(T);  --T.column; }
            while (T.column < destionationColumn) { moveTileRight(T); ++T.column; }
            while (T.row    > destinationRow) { moveTileUp(T);    --T.row; }
            while (T.row    < destinationRow) { moveTileDown(T);  ++T.row; }
        } else {
            while (T.row    > destinationRow) { moveTileUp(T);    --T.row; }
            while (T.row    < destinationRow) { moveTileDown(T);  ++T.row; }
            while (T.column > destionationColumn) { moveTileLeft(T);  --T.column; }
            while (T.column < destionationColumn) { moveTileRight(T); ++T.column; }
        }
    }

    void moveBlankLeftOrRight() {
        if (blankColumn == rightColumnProgress) {
            slideLeft();
        } else if (blankColumn == leftColumnProgress) {
            slideRight();
        } else {
            if (solvingColumnLeftRight) slideRight();
            else slideLeft();
        }
    }

    void moveBlankUpOrDown() {
        if (blankRow == topRowProgress) {
            slideDown();
        } else if (blankRow == bottomRowProgress) {
            slideUp();
        } else {
            if (solvingRowTopDown) slideDown();
            else slideUp();
        }
    }

    void moveBlankToColumn(int targetColumn) {
        targetColumn = max(0, min(targetColumn, columns - 1));
        while (blankColumn != targetColumn) {
            if (blankColumn < targetColumn) slideRight();
            else slideLeft();
        }
    }

    void moveBlankToRow(int targetRow) {
        targetRow = max(0, min(targetRow, rows - 1));
        while (blankRow != targetRow) {
            if (blankRow < targetRow) slideDown();
            else slideUp();
        }
    }

    void moveTileLeft(Tile& T) {
        if (blankColumn > T.column && blankRow == T.row) {
            moveBlankUpOrDown();
        }

        if (!solvingRow && solvingColumnLeftRight) {
            if (T.column == columnInProgress + 1) {
                if (T.row != bottomRowProgress) {
                    if (blankColumn >= T.column && blankRow < T.row) {
                        moveBlankToColumn(T.column + 1);
                        moveBlankToRow(T.row + 1);
                    }
                } else {
                    moveBlankToRow(T.row - 1);
                    moveBlankToColumn(T.column);
                }
            }
        }

        moveBlankToColumn(T.column - 1);
        moveBlankToRow(T.row);
        slideRight();
    }

    void moveTileRight(Tile& T) {
        if (blankColumn < T.column && blankRow == T.row) {
            moveBlankUpOrDown();
        }

        if (solvingRow) {
            if (solvingRowTopDown) {
                if (blankRow == rowInProgress &&
                    ((blankRow + 1 != T.row) || (blankColumn != T.column))) {
                    if (canSlideDown()) slideDown();
                }
            } else {
                if (blankRow == rowInProgress &&
                    ((blankRow - 1 != T.row) || (blankColumn != T.column))) {
                    if (canSlideUp()) slideUp();
                }
            }
        } else {
            if (!solvingColumnLeftRight) {
                if (T.column == columnInProgress - 1) {
                    if (T.row != bottomRowProgress) {
                        if (blankColumn <= T.column && blankRow < T.row) {
                            moveBlankToColumn(T.column - 1);
                            moveBlankToRow(T.row + 1);
                        }
                    } else {
                        moveBlankToRow(T.row - 1);
                        moveBlankToColumn(T.column);
                    }
                }
            }
        }

        moveBlankToColumn(T.column + 1);
        moveBlankToRow(T.row);
        slideLeft();
    }

    void moveTileUp(Tile& T) {
        if (solvingRow && solvingRowTopDown) {
            if (T.row == rowInProgress + 1) {
                if (T.column != rightColumnProgress) {
                    if (blankColumn <= T.column && blankRow >= T.row) {
                        moveBlankToRow(T.row + 1);
                        moveBlankToColumn(T.column + 1);
                    }
                } else {
                    moveBlankToColumn(T.column - 1);
                    moveBlankToRow(T.row);
                }
            }
        }

        if (blankRow > T.row && blankColumn == T.column) {
            moveBlankLeftOrRight();
        }

        moveBlankToRow(T.row - 1);
        moveBlankToColumn(T.column);
        slideDown();
    }

    void moveTileDown(Tile& T) {
        if (!solvingRow) {
            if (solvingColumnLeftRight) {
                if (blankColumn == columnInProgress &&
                    ((blankColumn + 1 != T.column) || (blankRow != T.row))) {
                    if (canSlideRight()) slideRight();
                }
            } else {
                if (blankColumn == columnInProgress &&
                    ((blankColumn - 1 != T.column) || (blankRow != T.row))) {
                    if (canSlideLeft()) slideLeft();
                }
            }
        }

        if (solvingRow && !solvingRowTopDown) {
            if (T.row == rowInProgress - 1) {
                if (T.column != rightColumnProgress) {
                    if (blankColumn <= T.column && blankRow <= T.row) {
                        moveBlankToRow(T.row - 1);
                        moveBlankToColumn(T.column + 1);
                    }
                } else {
                    moveBlankToColumn(T.column - 1);
                    moveBlankToRow(T.row);
                }
            }
        }

        if (blankRow < T.row && blankColumn == T.column) {
            moveBlankLeftOrRight();
        }

        moveBlankToRow(T.row + 1);
        moveBlankToColumn(T.column);
        slideUp();
    }

    bool moreThanTwoUnsolvedRows() const {
        return (bottomRowProgress + 1 - topRowProgress) > 2;
    }

    bool moreThanTwoUnsolvedColumns() const {
        return (rightColumnProgress + 1 - leftColumnProgress) > 2;
    }

    bool moreUnsolvedRowsThanColumns() const {
        return (bottomRowProgress - topRowProgress + 1) >= (rightColumnProgress + 1 - leftColumnProgress);
    }

    bool moreUnsolvedColumnsThanRows() const {
        return (rightColumnProgress + 1 - leftColumnProgress) > (bottomRowProgress + 1 - topRowProgress);
    }

    bool columnFinishedAndNotInGoalColumn() const {
        return isColumnEqual(columnInProgress) && (columnInProgress != goalBlankCol);
    }

    bool rowFinishedAndNotInGoalRow() const {
        return isRowEqual(rowInProgress) && (rowInProgress != goalBlankRow);
    }

    bool unsolvedPuzzleIsTwoByTwo() const {
        return (bottomRowProgress + 1 - topRowProgress == 2) && (rightColumnProgress + 1 - leftColumnProgress == 2);
    }
};

namespace MultiBlank {

struct Board {
    vector<vector<int>> grid;
    int R{}, C{};
    Board() = default;
    Board(const vector<vector<int>>& M) : grid(M), R((int)size(M)), C((int)size(M[0])){}
    int& at(int row, int column){ return grid[row][column]; }
    int  at(int row, int column) const { return grid[row][column]; }
    vector<pii> blanks() const {
        vector<pii> blankCoordinates;
        for(int row = 0; row < R; row++)
            for(int column = 0; column < C; column++)
                if(grid[row][column]==0) blankCoordinates.push_back({row, column});
        return blankCoordinates;
    }
};

struct Recorder {
    vector<Move> moves;
    void push(int tile, MoveDirection direction){
        if (tile > 0) moves.push_back({tile,direction});
    }
};

static inline int makeSpare(int tag, int r, int c, int C){
    return -1000000000 - tag*1000000 - (r * C + c + 1);
}

static void moveTileIntoBlank(Board& board, Recorder& recorder, int rBlank, int cBlank, int rTile, int cTile){
    int tile = board.at(rTile, cTile);
    if(rTile == rBlank - 1 && cTile == cBlank) recorder.push(tile, MoveDirection::Down);
    else if(rTile == rBlank + 1 && cTile == cBlank) recorder.push(tile, MoveDirection::Up);
    else if(rTile == rBlank && cTile == cBlank - 1) recorder.push(tile, MoveDirection::Right);
    else if(rTile == rBlank && cTile == cBlank + 1) recorder.push(tile, MoveDirection::Left);
    else return;
    swap(board.at(rBlank,cBlank), board.at(rTile,cTile));
}

static void moveOneBlankGreedy(Board& board, Recorder& recorder, pii& blankCoordinates, pii target, pii lockCell = {-1, -1}){
    int& currentRow = blankCoordinates.first;
    int& currentColumn = blankCoordinates.second;
    const int targetRow = target.first;
    const int targetColumn = target.second;

    auto tryMove = [&](int dR, int dC) {
        int nextRow = currentRow + dR;
        int nextColumn = currentColumn + dC;

        if (nextRow < 0 || nextRow >= board.R || nextColumn < 0 || nextColumn >= board.C) return false;
        if (lockCell.first == nextRow && lockCell.second == nextColumn) return false;

        moveTileIntoBlank(board, recorder, currentRow, currentColumn, nextRow, nextColumn);
        currentRow = nextRow;
        currentColumn = nextColumn;
        return true;
    };

    int guard = 2 * board.R * board.C;
    while((currentRow != targetRow || currentColumn != targetColumn) && guard-- > 0){
        bool moved = false;
        if (currentRow > targetRow) { if (tryMove(-1, 0)) moved = true; }
        else if (currentRow < targetRow) { if (tryMove(1, 0)) moved = true; }
        if (moved) continue;

        if (currentColumn > targetColumn) { if (tryMove(0, -1)) moved = true; }
        else if (currentColumn < targetColumn) { if (tryMove(0, 1)) moved = true; }
        if (moved) continue;

        if (currentRow != targetRow) {
            if (tryMove(0, 1)) moved = true;
            else if (tryMove(0, -1)) moved = true;
        }
        if (moved) continue;

        if (currentColumn != targetColumn) {
            if (tryMove(1, 0)) moved = true;
            else if (tryMove(-1, 0)) moved = true;
        }
        if (moved) continue;
        if (!moved) throw runtime_error("moveOneBlankGreedy is trapped and cannot make a move.");
    }
    if (guard <= 0) throw runtime_error("moveOneBlankGreedy exceeded safety guard limit.");
}

static bool oneBlankSolvable(const vector<vector<int>>& startState, const vector<vector<int>>& goalState){
    int R = (int)size(startState), C = (int)size(startState[0]);
    unordered_map<int,int> goalPosition; goalPosition.reserve((int)R*C*2);
    int goalBlankRow = -1;
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            int v = goalState[r][c];
            if(v == 0){ goalBlankRow = r; continue; }
            goalPosition[v] = r*C + c;
        }
    }
    vector<int> permutation; permutation.reserve(R*C - 1);
    int startBlankRow = -1;
    for(int r = 0; r < R; r++){
        for(int c = 0; c < C; c++){
            int v = startState[r][c];
            if(v == 0){ startBlankRow = r; continue; }
            permutation.push_back(goalPosition.at(v));
        }
    }
    ll inversionsCount = 0;
    for (int i = 0; i < (int)size(permutation); ++i)
        for (int j = i + 1; j < (int)size(permutation); ++j)
            if(permutation[i] > permutation[j]) inversionsCount++;

    if(C % 2 == 1) return (inversionsCount % 2 == 0);
    int blankRowFromBottomStart = R - startBlankRow;
    int blankRowFromBottomGoal = R - goalBlankRow;
    return ((inversionsCount + blankRowFromBottomStart) % 2) == (blankRowFromBottomGoal % 2);
}

static bool runOneBlankSolver(const vector<vector<int>>& startState, const vector<vector<int>>& goalState, vector<Move>& outMoves){
    PuzzleSolver solver(startState, goalState);
    vector<Move> solverMoves;
    bool solved = solver.solve(solverMoves);
    if(solved) outMoves.insert(outMoves.end(), all(solverMoves));
    return solved;
}

static void transposeBottomRowInTopLeft2x2(Board& board, Recorder& recorder){
    array<int,4> start = { board.at(0,0), board.at(0,1), board.at(1,0), board.at(1,1) };
    array<int,4> goal = start;
    swap(goal[2], goal[3]);

    auto getNeighbors = [&](const array<int,4>& state){
        static const vector<pii> edges = {{0,1},{0,2},{1,3},{2,3}};
        vector<array<int,4>> next;
        for(int z = 0; z < 4; z++) if(state[z] == 0){
            for(auto p : edges){
                int A = p.first, B = p.second;
                int other = (A == z ? B : (B == z ? A : -1));
                if(other == -1) continue;
                auto nextState = state;
                swap(nextState[z], nextState[other]);
                next.push_back(nextState);
            }
        }
        return next;
    };

    unordered_map<string, pair<string, array<int,4>>> parent;
    auto keyOf = [&](const array<int,4>& S){
        string k; k.reserve(16);
        for(int v : S){ k.append(reinterpret_cast<const char*>(&v), sizeof(int)); }
        return k;
    };

    queue<array<int,4>> queueArray;
    string keyStart = keyOf(start), keyGoal = keyOf(goal);
    queueArray.push(start); parent[keyStart] = {"", start};

    bool found = false;
    while(!queueArray.empty() && !found){
        auto current = queueArray.front(); queueArray.pop();
        if(keyOf(current) == keyGoal){ found = true; break; }
        for(auto next : getNeighbors(current)){
            string keyNext = keyOf(next);
            if(parent.find(keyNext) == parent.end()){
                parent[keyNext] = {keyOf(current), current};
                queueArray.push(next);
            }
        }
    }
    if(!found) return;

    vector<array<int,4>> path;
    string currentK = keyGoal;
    while(currentK != keyStart){ path.push_back(parent.at(currentK).second); currentK = parent.at(currentK).first; }
    path.push_back(start);
    reverse(all(path));

    for(int i = 1; i < (int)size(path); ++i){
        auto previous = path[i-1], current = path[i];
        int previousZero = -1, currentZero = -1;
        for(int j = 0; j < 4; j++){
            if(previous[j] == 0 && current[j] != 0) previousZero = j;
            if(previous[j] != 0 && current[j] == 0) currentZero = j;
        }
        auto indexToCoordinates=[&](int i) -> pii{ return {i / 2, i % 2}; };
        pii blankCoordinates = indexToCoordinates(previousZero);
        pii tileCoordinates  = indexToCoordinates(currentZero);
        moveTileIntoBlank(board, recorder, blankCoordinates.first, blankCoordinates.second, tileCoordinates.first, tileCoordinates.second);
    }
}

static Board reduceTwoBlanksToStandard(Board board, Recorder& recorder, pii firstGoalBlank, pii secondGoalBlank){
    int R = board.R, C = board.C;

    auto blanks = board.blanks();
    if((int)size(blanks) != 2) throw runtime_error("reduceTwoBlanksToStandard expects exactly 2 blanks.");
    pii firstBlank = blanks[0], secondBlank = blanks[1];
    moveOneBlankGreedy(board, recorder, firstBlank, {0,0});
    auto curBlanks = board.blanks();
    secondBlank = (curBlanks[0] == firstBlank) ? curBlanks[1] : curBlanks[0];
    moveOneBlankGreedy(board, recorder, secondBlank, {0,1}, {0,0});

    int spareLabel = makeSpare(0, firstGoalBlank.first, firstGoalBlank.second, C);
    board.at(0,0) = spareLabel;

    vector<int> originalTiles;
    originalTiles.reserve((int)R * (int)C);
    for(int r = 0; r < R; ++r) for(int c = 0; c < C; ++c) {
        if (board.at(r,c) != 0 && board.at(r,c) != spareLabel) originalTiles.push_back(board.at(r,c));
    }
    sort(all(originalTiles));

    vector<vector<int>> intermediateGoal(R, vector<int>(C));
    int thisIndex = 0;
    for(int r = 0; r < R; ++r) for(int c = 0; c < C; ++c) {
        if (r == firstGoalBlank.first && c == firstGoalBlank.second) intermediateGoal[r][c] = spareLabel;
        else if (r == secondGoalBlank.first && c == secondGoalBlank.second) intermediateGoal[r][c] = 0;
        else intermediateGoal[r][c] = originalTiles[thisIndex++];
    }

    if(!oneBlankSolvable(board.grid, intermediateGoal)){
        board.at(0,0) = 0;
        transposeBottomRowInTopLeft2x2(board, recorder);
        board.at(0,0) = spareLabel;
        if(!oneBlankSolvable(board.grid, intermediateGoal)) throw runtime_error("Parity still off after transposition.");
    }

    vector<Move> sequence;
    if (!runOneBlankSolver(board.grid, intermediateGoal, sequence)) throw runtime_error("1-blank solver failed.");

    unordered_map<int, pii> position; position.reserve((int)R * (int)C * 2);
    for(int r = 0; r < R; ++r) for(int c = 0; c < C; ++c){
        int V = board.at(r,c);
        if (V != 0) position[V] = {r,c};
    }

    for(const Move& move: sequence){
        int tile = move.first; if (tile == 0) continue;
        auto iterator = position.find(tile);
        if (iterator == position.end()) throw runtime_error("Tile from move sequence not found.");
        int tR = iterator->second.first, tC = iterator->second.second;

        int bR = tR, bC = tC;
        if (move.second == MoveDirection::Up) bR = tR + 1;
        else if (move.second == MoveDirection::Down) bR = tR - 1;
        else if (move.second == MoveDirection::Left) bC = tC + 1;
        else if (move.second == MoveDirection::Right) bC = tC - 1;

        moveTileIntoBlank(board, recorder, bR, bC, tR, tC);
        position[tile] = {bR, bC};
    }

    int gR = firstGoalBlank.first, gC = firstGoalBlank.second;
    if(board.at(gR,gC) != spareLabel) throw runtime_error("Spare not at destination after 1-blank solve.");
    board.at(gR,gC) = 0;
    return board;
}

static pair<pii,pii> pickTwoGoalBlanks(const vector<vector<int>>& goal){
    int R = (int)size(goal), C = (int)size(goal[0]);
    vector<pii> zerosArray;
    for(int r = 0; r < R; ++r) for(int c = 0; c < C; ++c) if(goal[r][c] == 0) zerosArray.push_back({r,c});
    if((int)size(zerosArray) < 2) throw runtime_error("Goal must have at least two blanks.");
    return {zerosArray[0], zerosArray[1]};
}

static tuple<Board, vector<vector<int>>, pii, pii>
reduceKToTwo(const vector<vector<int>>& start, const vector<vector<int>>& goal){
    Board startBoard(start);
    int R = startBoard.R, C = startBoard.C;

    vector<pii> startBlanks, goalBlanks;
    for(int r = 0; r < R; r++) for(int c = 0; c < C; c++){
        if(startBoard.at(r,c) == 0) startBlanks.push_back({r,c});
        if(goal[r][c] == 0) goalBlanks.push_back({r,c});
    }
    if((int)size(startBlanks) < (int)size(goalBlanks)) throw runtime_error("Start has fewer blanks than goal.");

    int blankCount = (int)size(startBlanks);
    auto selected = pickTwoGoalBlanks(goal);
    pii firstGoalBlank = selected.first, secondGoalBlank = selected.second;

    if(blankCount == 2) return make_tuple(startBoard, goal, firstGoalBlank, secondGoalBlank);

    vector<pii> labelTargets;
    for(int i = 2; i < (int)size(goalBlanks); ++i) labelTargets.push_back(goalBlanks[i]);

    vector<vector<int>> newGoal = goal;
    vector<pii> toFill;
    for(int i = 2; i < blankCount; i++) toFill.push_back(startBlanks[i]);

    int need = (int)size(labelTargets);
    for(int i = 0; i < (int)size(toFill) && i < need; i++){
        auto [sR, sC] = toFill[i];
        auto [gR, gC] = labelTargets[i];
        int spare = makeSpare(1, gR, gC, C);
        startBoard.at(sR,sC)=spare;
        newGoal[gR][gC]=spare;
    }
    for(int i = need; i < (int)size(toFill); ++i){
        auto [sR, sC] = toFill[i];
        int spare = makeSpare(2, sR, sC, C);
        startBoard.at(sR,sC) = spare;
        newGoal[sR][sC] = spare;
    }

    auto reChecked = startBoard.blanks();
    if((int)size(reChecked) != 2){
        int keep = 2;
        for(const auto& b : reChecked){
            if(keep > 0){ keep--; continue; }
            int r = b.first, c = b.second;
            int spare = makeSpare(3, r, c, C);
            startBoard.at(r,c) = spare;
            newGoal[r][c] = spare;
        }
    }
    return make_tuple(startBoard, newGoal, firstGoalBlank, secondGoalBlank);
}

static vector<Move> invertMoves(const vector<Move>& moves){
    vector<Move> inversionsCount; inversionsCount.reserve(size(moves));
    for(int i = (int)size(moves) - 1; i >= 0; --i){
        const Move& m = moves[i];
        MoveDirection d = m.second;
        if(d == MoveDirection::Up) d = MoveDirection::Down;
        else if(d == MoveDirection::Down) d = MoveDirection::Up;
        else if(d == MoveDirection::Left) d = MoveDirection::Right;
        else if(d == MoveDirection::Right) d = MoveDirection::Left;
        inversionsCount.push_back({m.first, d});
    }
    return inversionsCount;
}

static bool solveMultiBlank(const vector<vector<int>>& start, const vector<vector<int>>& goal, vector<Move>& movesOut)
{
    movesOut.clear();
    Board startReduced; vector<vector<int>> goalForStart; pii g1, g2;
    tie(startReduced, goalForStart, g1, g2) = reduceKToTwo(start, goal);

    Recorder recordStart;
    reduceTwoBlanksToStandard(startReduced, recordStart, g1, g2);

    Board goalReduced; vector<vector<int>> goalForGoal; pii tmp1, tmp2;
    tie(goalReduced, goalForGoal, tmp1, tmp2) = reduceKToTwo(goal, goal);

    Recorder recordGoal;
    reduceTwoBlanksToStandard(goalReduced, recordGoal, g1, g2);

    auto toGoal = invertMoves(recordGoal.moves);
    movesOut.insert(movesOut.end(), all(recordStart.moves));
    movesOut.insert(movesOut.end(), all(toGoal));
    return true;
}

}

namespace CanonizePuzzle {
    struct Board {
        int n, k;
        vector<vector<int>> occurenceArray;
        vector<pii> positionArray;
        Board(int n = 0, int k = 0): n(n), k(k){
            occurenceArray.assign(n + 1, vector<int>(n + 1,0));
            positionArray.assign(k + 1, {0,0});
        }
    };

    struct Step { int c, i, j; };

    const int DR[8]={-1,-1,-1,0,0,1,1,1};
    const int DC[8]={-1,0,1,-1,1,-1,0,1};

    static inline bool inside(int n,int r,int c){ return r >= 1 && r <= n && c >= 1 && c <= n; }

    bool canMoveKing(const Board& B, int c, int nR, int nC){
        auto [cR, cC] = B.positionArray[c];
        if (max(abs(cR - nR),abs(cC - nC))!=1) return false;
        if (!inside(B.n, nR, nC)) return false;
        if (B.occurenceArray[nR][nC]!=0) return false;

        for(int d = 0; d < 8; d++){
            int r = nR + DR[d], c = nC + DC[d];
            if (!inside(B.n, r,c)) continue;
            int other = B.occurenceArray[r][c];
            if (other != 0 && other != c) {
                if (!(r == cR && c == cC)) return false;
            }
        }
        return true;
    }

    static inline bool canMoveKingHypothetical(const Board& B, int c, int currentR, int currentC, int nR, int nC){
        if (max(abs(currentR - nR),abs(currentC - nC)) != 1) return false;
        if (!inside(B.n, nR, nC)) return false;

        auto [originalR, originalC] = B.positionArray[c];
        auto occurence = [&](int r, int cPosition)->int{
            if (r == originalR && cPosition == originalC && !(r == currentR && cPosition == currentC)) return 0;
            if (r == currentR && cPosition == currentC) return c;
            return B.occurenceArray[r][cPosition];
        };

        if (occurence(nR, nC) != 0) return false;

        for(int d = 0; d < 8; ++d){
            int r = nR + DR[d], cPosition = nC + DC[d];
            if (!inside(B.n, r, cPosition)) continue;
            int other = occurence(r, cPosition);
            if (other != 0 && other != c) {
                if (!(r == currentR && cPosition == currentC)) return false;
            }
        }
        return true;
    }

    bool doMove(Board& B, int c, int nR, int nC, vector<Step>& moves){
        if (!canMoveKing(B,c,nR,nC)) return false;
        auto [cR, cC] = B.positionArray[c];
        B.occurenceArray[cR][cC] = 0;
        B.occurenceArray[nR][nC] = c;
        B.positionArray[c] = {nR,nC};
        moves.push_back({c, nR, nC});
        return true;
    }

    bool localBlockRoute(Board& B, int c, int zeroR, int zeroC, vector<Step>& moves){
        vector<pii> cells;
        for(int dR = 0; dR < 2; dR++) for(int dC = 0; dC < 2; dC++){
            int r = zeroR + dR, c = zeroC + dC;
            if (inside(B.n,r,c)) cells.push_back({r,c});
        }

        map<pii,int> ID;
        for(int i = 0; i < (int)size(cells);i++) ID[cells[i]] = i;
        if (!ID.count({zeroR,zeroC})) return false;

        int S = ID[B.positionArray[c]];
        int T = ID[{zeroR,zeroC}];

        if (S == T) return true;

        int M = (int)size(cells);
        vector<int> distance(M,-1), preArray(M,-1);
        queue<int> queueArray;
        distance[S] = 0; queueArray.push(S);

        auto [originalR, originalC] = B.positionArray[c];

        while(!queueArray.empty()){
            int u = queueArray.front(); queueArray.pop();
            auto [uR, uC] = cells[u];

            for(int dR = -1; dR <= 1; ++dR) for(int dC = -1; dC <= 1; ++dC){
                if (!dR && !dC) continue;
                int vR = uR + dR, vC = uC + dC;
                if (!ID.count({vR,vC})) continue;
                int v = ID[{vR,vC}];
                if (distance[v]!=-1) continue;

                if (canMoveKingHypothetical(B, c, uR, uC, vR, vC)){
                    distance[v] = distance[u] + 1; preArray[v] = u; queueArray.push(v);
                    if (v == T) goto endBFS;
                }
            }
        }
        endBFS:;

        if (distance[T] == -1) return false;

        vector<int> path;
        for(int x = T; x != -1; x = preArray[x]) path.push_back(x);
        reverse(path.begin(),path.end());

        for(int i = 1; i < (int)size(path); i++){
            auto [nR, nC]=cells[path[i]];
            if (!doMove(B, c, nR, nC, moves)) return false;
        }
        return true;
    }

    bool canonize(const Board& inB, vector<Step>& canonMoves, vector<vector<int>>& canonizedForm){
        Board B = inB;
        canonMoves.clear();

        int n = B.n;
        for(int r = 1; r <= n; r += 2){
            for(int c = 1;c <= n; c += 2){
                int whoIs = 0;
                for(int dR = 0; dR < 2; dR++) for(int dC = 0; dC < 2; dC++){
                    int rR = r + dR, cC = c + dC;
                    if (!inside(n,rR,cC)) continue;
                    if (B.occurenceArray[rR][cC]){ whoIs = B.occurenceArray[rR][cC]; }
                }
                if (!whoIs) continue;
                if (B.positionArray[whoIs] != pii{r,c}){
                    if (!localBlockRoute(B, whoIs, r, c, canonMoves)) {
                        return false;
                    }
                }
            }
        }

        int R = (n + 1) / 2;
        int C = (n + 1) / 2;
        canonizedForm.assign(R, vector<int>(C));

        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                canonizedForm[i][j] = B.occurenceArray[2*i + 1][2*j + 1];

        return true;
    }
}

static bool solveSlidingPuzzleGeneralized(const vector<vector<int>>& startMatrix, const vector<vector<int>>& goalMatrix, vector<Move>& movesOut)
{
    vector<int> startTiles, goalTiles;
    startTiles.reserve((int)size(startMatrix) * (int)size(startMatrix[0]));
    goalTiles.reserve((int)size(goalMatrix) * (int)size(goalMatrix[0]));

    for(const auto& row : startMatrix) for(int v : row) if(v != 0) startTiles.push_back(v);
    for(const auto& row : goalMatrix)  for(int v : row) if(v != 0) goalTiles.push_back(v);
    sort(all(startTiles));
    sort(all(goalTiles));
    if (startTiles != goalTiles) return false;

    int startBlankCount = 0, goalBlankCount = 0;
    for(const auto& r : startMatrix) for(int v : r) if(v == 0) ++startBlankCount;
    for(const auto& r : goalMatrix)  for(int v : r) if(v == 0) ++goalBlankCount;

    if(startBlankCount == 0 || goalBlankCount == 0) return false;

    if(startBlankCount == 1 && goalBlankCount == 1) {
        if (!MultiBlank::oneBlankSolvable(startMatrix, goalMatrix)) return false;
        return MultiBlank::runOneBlankSolver(startMatrix, goalMatrix, movesOut);
    }
    if(goalBlankCount < 2 && startBlankCount > 1) return false;

    return MultiBlank::solveMultiBlank(startMatrix, goalMatrix, movesOut);
}

void solveTestCase() {
    int N, K;
    cin >> N >> K;

    CanonizePuzzle::Board initialBoard(N, K);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x; cin >> x;
            if (x > 0) {
                initialBoard.occurenceArray[i][j] = x;
                initialBoard.positionArray[x] = {i, j};
            }
        }
    }

    CanonizePuzzle::Board finalBoard(N, K);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x; cin >> x;
            if (x > 0) {
                finalBoard.occurenceArray[i][j] = x;
                finalBoard.positionArray[x] = {i, j};
            }
        }
    }

    bool isSame = true;
    for (int i = 1; i <= N && isSame; ++i)
    for (int j = 1; j <= N; ++j)
        if (initialBoard.occurenceArray[i][j] != finalBoard.occurenceArray[i][j])
            isSame = false;

    if(isSame) {
        cout << "TAK" << endl;
        cout << "0" << endl;
        return;
    }

    vector<CanonizePuzzle::Step> initialCanonMoves, finalCanonMoves;
    vector<vector<int>> initialCanonizedForm, finalCanonizedForm;
    if (!CanonizePuzzle::canonize(initialBoard, initialCanonMoves, initialCanonizedForm)) {
        cout << "Initial board canonization failed." << endl;
        return;
    }
    if (!CanonizePuzzle::canonize(finalBoard, finalCanonMoves, finalCanonizedForm)) {
        cout << "Final board canonization failed." << endl;
        return;
    }

    bool isSameCanon = true;
    if (size(initialCanonizedForm) != size(finalCanonizedForm)) {
        isSameCanon = false;
    } else {
        for (int r = 0; r < (int)size(initialCanonizedForm) && isSameCanon; ++r) {
            if (size(initialCanonizedForm[r]) != size(finalCanonizedForm[r])) {
                isSameCanon = false;
                break;
            }
            for (int c = 0; c < (int)size(initialCanonizedForm[r]); ++c) {
                if (initialCanonizedForm[r][c] != finalCanonizedForm[r][c]) {
                    isSameCanon = false;
                    break;
                }
            }
        }
    }

    if (isSameCanon) {
        vector<tuple<int,int,int,int,int>> finalCanonTransitions;
        {
            CanonizePuzzle::Board temp = finalBoard;
            vector<CanonizePuzzle::Step> dummy;
            for (const auto& st : finalCanonMoves) {
                auto [fR, fC] = temp.positionArray[st.c];
                if (!CanonizePuzzle::doMove(temp, st.c, st.i, st.j, dummy)) {
                    cout << "NIE" << endl;
                    return;
                }
                finalCanonTransitions.emplace_back(st.c, fR, fC, st.i, st.j);
            }
        }

        cout << "TAK" << endl;
        cout << (size(initialCanonMoves) + size(finalCanonTransitions)) << endl;

        for (const auto& move : initialCanonMoves) {
            cout << move.c << ' ' << move.i << ' ' << move.j << endl;
        }

        for (int idx = (int)size(finalCanonTransitions) - 1; idx >= 0; --idx) {
            int c, fR, fC, tR, tC;
            tie(c, fR, fC, tR, tC) = finalCanonTransitions[idx];
            cout << c << ' ' << fR << ' ' << fC << endl;
        }

        return;
    }

    auto countBlanks = [](const vector<vector<int>>& M) {
        int Z = 0;
        for (const auto& r : M) for (int v : r) if (v == 0) ++Z;
        return Z;
    };
    int startBlanks = countBlanks(initialCanonizedForm);
    int goalBlanks  = countBlanks(finalCanonizedForm);

    vector<Move> solverMoves;
    bool isSolved = solveSlidingPuzzleGeneralized(initialCanonizedForm, finalCanonizedForm, solverMoves);

    vector<Move> preNormalizationMoves;
    vector<Move> postSwapMoves;
    bool useMagic = false;

    if (!isSolved) {
        if (N % 2 != 0) {
            cout << "NIE" << endl;
            return;
        }

        MultiBlank::Board boardToNormalize(initialCanonizedForm);
        MultiBlank::Recorder normalizationRecorder;

        pii blankPosition = {-1, -1};
        for (int r = 0; r < boardToNormalize.R; ++r) {
            for (int c = 0; c < boardToNormalize.C; ++c) {
                if (boardToNormalize.at(r, c) == 0) { blankPosition = {r, c}; break; }
            }
            if (blankPosition.first != -1) break;
        }
        if (blankPosition.first == -1) { cout << "NIE" << endl; return; }
        pii targetPos = {boardToNormalize.R - 1, boardToNormalize.C - 1};
        MultiBlank::moveOneBlankGreedy(boardToNormalize, normalizationRecorder, blankPosition, targetPos);
        preNormalizationMoves = normalizationRecorder.moves;

        if (boardToNormalize.R > 1 && boardToNormalize.C > 1) {
            swap(boardToNormalize.at(boardToNormalize.R - 2, boardToNormalize.C - 1),
                 boardToNormalize.at(boardToNormalize.R - 1, boardToNormalize.C - 2));
        } else {
            cout << "NIE" << endl;
            return;
        }

        if (!solveSlidingPuzzleGeneralized(boardToNormalize.grid, finalCanonizedForm, postSwapMoves)) {
            cout << "NIE" << endl;
            return;
        }
        useMagic = true;
    }

    struct Transition { int c, fR, fC, tR, tC; };
    vector<Transition> finalCanonTransitions;
    {
        CanonizePuzzle::Board temp = finalBoard;
        vector<CanonizePuzzle::Step> dummy;
        for (const auto& st : finalCanonMoves) {
            auto [fR, fC] = temp.positionArray[st.c];
            if (!CanonizePuzzle::doMove(temp, st.c, st.i, st.j, dummy)) {
                cout << "NIE" << endl;
                return;
            }
            finalCanonTransitions.push_back({st.c, fR, fC, st.i, st.j});
        }
    }

    vector<CanonizePuzzle::Step> outMoves;
    CanonizePuzzle::Board current = initialBoard;

    auto fail = [&](){
        cout << "NIE" << endl;
        return 0;
    };

    auto pushMove = [&](int c, int nR, int nC) {
        if (!CanonizePuzzle::doMove(current, c, nR, nC, outMoves)) fail();
    };

    auto invertDirection = [](MoveDirection d) {
        if (d == MoveDirection::Up) return MoveDirection::Down;
        if (d == MoveDirection::Down) return MoveDirection::Up;
        if (d == MoveDirection::Left) return MoveDirection::Right;
        if (d == MoveDirection::Right) return MoveDirection::Left;
        return d;
    };

    auto twoStepDirection = [&](int c, MoveDirection tileDirection) {
        int dR = 0, dC = 0;
        if (tileDirection == MoveDirection::Up) dR = -1;
        else if (tileDirection == MoveDirection::Down) dR = 1;
        else if (tileDirection == MoveDirection::Left) dC = -1;
        else if (tileDirection == MoveDirection::Right) dC = 1;
        else fail();

        for (int t = 0; t < 2; ++t) {
            auto [r, col] = current.positionArray[c];
            int nR = r + dR, nC = col + dC;
            pushMove(c, nR, nC);
        }
    };

    auto doMagicSwap = [&]() {
        int zeroR = N - 3, zeroC = N - 3;
        if (zeroR < 1 || zeroC < 1 || zeroR + 3 > N || zeroC + 3 > N) fail();

        int A = current.occurenceArray[zeroR][zeroC + 2];
        int bC = current.occurenceArray[zeroR + 2][zeroC];

        pushMove(A, zeroR,     zeroC + 3);
        pushMove(A, zeroR + 1, zeroC + 3);
        pushMove(A, zeroR + 2, zeroC + 3);
        pushMove(A, zeroR + 3, zeroC + 3);

        pushMove(bC, zeroR + 2, zeroC + 1);
        pushMove(bC, zeroR + 1, zeroC + 2);
        pushMove(bC, zeroR,     zeroC + 3);
        pushMove(bC, zeroR,     zeroC + 2);

        pushMove(A, zeroR + 3, zeroC + 2);
        pushMove(A, zeroR + 3, zeroC + 1);
        pushMove(A, zeroR + 3, zeroC);
        pushMove(A, zeroR + 2, zeroC);
    };

    for (const auto& a : initialCanonMoves) pushMove(a.c, a.i, a.j);

    if (!useMagic) {
        bool directionsAreBlank = (startBlanks == 1 && goalBlanks == 1);

        for (const auto& m : solverMoves) {
            if (m.first <= 0) continue;
            MoveDirection dir = m.second;
            if (directionsAreBlank) dir = invertDirection(dir);
            twoStepDirection(m.first, dir);
        }
    } else {
        for (const auto& m : preNormalizationMoves) {
            if (m.first <= 0) continue;
            twoStepDirection(m.first, m.second);
        }

        doMagicSwap();

        for (const auto& m : postSwapMoves) {
            if (m.first <= 0) continue;
            twoStepDirection(m.first, invertDirection(m.second));
        }
    }

    for (int i = (int)size(finalCanonTransitions) - 1; i >= 0; --i) {
        const auto& t = finalCanonTransitions[i];
        pushMove(t.c, t.fR, t.fC);
    }

    cout << "TAK" << endl;
    cout << size(outMoves) << endl;
    for (const auto& move : outMoves) {
        cout << move.c << ' ' << move.i << ' ' << move.j << endl;
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}