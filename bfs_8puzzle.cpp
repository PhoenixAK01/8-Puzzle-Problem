#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>

using namespace std;

vector<vector<vector<int>>> generateSuccessors(const vector<vector<int>> &board) {
    int zeroX = -1, zeroY = -1;
    for (int r = 0; r < 3 && zeroX == -1; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == 0) {
                zeroX = r;
                zeroY = c;
                break;
            }
        }
    }

    vector<pair<int, int>> moves = {{-1,0}, {1,0}, {0,-1}, {0,1}}; 
    vector<vector<vector<int>>> nextStates;

    for (auto [dx, dy] : moves) {
        int newX = zeroX + dx;
        int newY = zeroY + dy;

        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            vector<vector<int>> newBoard = board;
            swap(newBoard[zeroX][zeroY], newBoard[newX][newY]);
            nextStates.push_back(newBoard);
        }
    }

    return nextStates;
}

string serialize(const vector<vector<int>> &grid) {
    string result;
    for (const auto &row : grid) {
        for (int val : row) {
            result += to_string(val);
        }
    }
    return result;
}

void bfsSolver(const vector<vector<int>> &start) {
    const vector<vector<int>> goal = {{1,2,3},{4,5,6},{7,8,0}};

    queue<vector<vector<int>>> q;
    unordered_set<string> seen;

    q.push(start);
    seen.insert(serialize(start));

    while (!q.empty()) {
        vector<vector<int>> current = q.front();
        q.pop();

        if (current == goal) {
            cout << "Success" << endl;
            return;
        }

        for (const auto &neighbor : generateSuccessors(current)) {
            string key = serialize(neighbor);
            if (!seen.count(key)) {
                seen.insert(key);
                q.push(neighbor);
            }
        }
    }

    cout << "No solution" << endl;
}

int main() {
    vector<vector<int>> puzzle = {
        {8,1,2},
        {0,4,3},
        {7,6,5}
    };

    bfsSolver(puzzle);
    return 0;
}
