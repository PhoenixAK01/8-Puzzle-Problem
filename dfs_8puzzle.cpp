#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

string toString(const vector<vector<int>> &board) {
    string res;
    for (const auto &row : board) {
        for (int val : row) {
            res += to_string(val);
        }
    }
    return res;
}

vector<vector<vector<int>>> getNextStates(const vector<vector<int>> &grid) {
    vector<vector<vector<int>>> result;
    pair<int, int> zeroPos;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (grid[r][c] == 0) {
                zeroPos = {r, c};
                break;
            }
        }
    }

    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}}; 

    for (auto [dx, dy] : directions) {
        int newX = zeroPos.first + dx;
        int newY = zeroPos.second + dy;

        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
            vector<vector<int>> temp = grid;
            swap(temp[zeroPos.first][zeroPos.second], temp[newX][newY]);
            result.push_back(temp);
        }
    }

    return result;
}

void runDFS(const vector<vector<int>> &start) {
    vector<vector<int>> target = {{1,2,3}, {4,5,6}, {7,8,0}};
    stack<vector<vector<int>>> stk;
    unordered_set<string> explored;

    stk.push(start);

    while (!stk.empty()) {
        vector<vector<int>> current = stk.top();
        stk.pop();

        string encoded = toString(current);
        if (explored.count(encoded)) continue;

        explored.insert(encoded);

        if (current == target) {
            cout << "Success" << endl;
            return;
        }

        for (const auto &next : getNextStates(current)) {
            string key = toString(next);
            if (!explored.count(key)) {
                stk.push(next);
            }
        }
    }

    cout << "No solution" << endl;
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3},
        {4, 5, 6},
        {8, 0, 7}
    };

    runDFS(initial);
    return 0;
}
