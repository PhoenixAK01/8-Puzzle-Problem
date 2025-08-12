#include <bits/stdc++.h>
using namespace std;

#define N 3

vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0} // 0 represents the blank tile
};

int rowMove[] = {-1, 1, 0, 0};
int colMove[] = {0, 0, -1, 1};

struct Node {
    vector<vector<int>> state;
    int x, y; 
    int cost; 
    int level;
    Node* parent;

    Node(vector<vector<int>> s, int x, int y, int level, Node* p)
        : state(s), x(x), y(y), level(level), parent(p) {
        cost = 0;
    }
};

int calculateCost(const vector<vector<int>>& current) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (current[i][j] != 0 && current[i][j] != goal[i][j])
                count++;
    return count;
}

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printMatrix(const vector<vector<int>>& mat) {
    for (auto &row : mat) {
        for (auto &val : row) {
            if (val == 0) cout << "_ ";
            else cout << val << " ";
        }
        cout << "\n";
    }
    cout << "------\n";
}

struct comp {
    bool operator()(Node* lhs, Node* rhs) const {
        return lhs->cost > rhs->cost; // lower cost has higher priority
    }
};

void printPath(Node* root) {
    if (root == nullptr) return;
    printPath(root->parent);
    printMatrix(root->state);
}

bool isSolvable(vector<vector<int>> puzzle) {
    vector<int> flat;
    for (auto &row : puzzle)
        for (auto &val : row)
            if (val != 0) flat.push_back(val);

    int invCount = 0;
    for (int i = 0; i < flat.size() - 1; i++)
        for (int j = i + 1; j < flat.size(); j++)
            if (flat[i] > flat[j]) invCount++;

    return (invCount % 2 == 0);
}

void solve(vector<vector<int>> initial, int x, int y) {
    if (!isSolvable(initial)) {
        cout << "This puzzle is unsolvable.\n";
        return;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;
    Node* root = new Node(initial, x, y, 0, nullptr);
    root->cost = calculateCost(initial);
    pq.push(root);

    unordered_set<string> visited;

    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();

        string stateStr;
        for (auto &row : minNode->state)
            for (auto &val : row)
                stateStr += to_string(val);

        if (visited.count(stateStr)) continue;
        visited.insert(stateStr);

        if (minNode->cost == 0) {
            cout << "Solution Path:\n";
            printPath(minNode);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = minNode->x + rowMove[i];
            int newY = minNode->y + colMove[i];

            if (isSafe(newX, newY)) {
                vector<vector<int>> newState = minNode->state;
                swap(newState[minNode->x][minNode->y], newState[newX][newY]);

                string newStr;
                for (auto &r : newState)
                    for (auto &v : r)
                        newStr += to_string(v);

                if (!visited.count(newStr)) {
                    Node* child = new Node(newState, newX, newY, minNode->level + 1, minNode);
                    child->cost = calculateCost(newState);
                    pq.push(child);
                }
            }
        }
    }
    cout << "No solution found.\n";
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}
    };

    int x = 1, y = 1; 

    solve(initial, x, y);

    return 0;
}
