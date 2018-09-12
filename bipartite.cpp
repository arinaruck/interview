#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>


bool dfs(std::vector<std::vector<int>>& AdjMatrix, std::vector<int>& visited, int n, int v) {
    std::vector<std::pair<int, int>> stack;  //  vertex, color
    stack.push_back({v, 3});
    while (!stack.empty()) {
        int curr = stack.back().first;
        int prev_col = stack.back().second;
        int col = 5 - prev_col;
        stack.pop_back();
        visited[curr] = col;
        for (size_t i = 0; i < n; ++i) {
            if (AdjMatrix[curr][i] == 1) {
                if (visited[curr] == visited[i]) {
                    return false;
                }
                if (visited[i] == 0) {
                    stack.push_back({i, col});
                }
            }
        }
        prev_col = col;
    }
    return true;
};


void isBipartite(std::vector<std::vector<int>>& AdjMatrix, long long n) {
    std::vector<int> visited(n);
    for (size_t i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            if (!dfs(AdjMatrix, visited, n, i)) {
                std::cout << "-1\n";
                return;
            }
        }
    }
    int k = std::count(visited.begin(), visited.end(), 2);
    if (k == n) {
        std::cout << 1 << "\n";
        std::cout << 1 << "\n";
        for (size_t i = 2; i <= n ; ++i) {
            std::cout << i << " ";

        }
    } else {
        std::cout << k << "\n";
        for (size_t i = 0; i < n; ++i) {
            if (visited[i] == 2) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << "\n";
        for (size_t i = 0; i < n; ++i) {
            if (visited[i] == 3) {
                std::cout << i + 1 << " ";
            }
        }
    }
    std::cout << "\n";

}


int main() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> AdjMatrix(n, std::vector<int>(n, 1));
    int u, v;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> u >> v;
        AdjMatrix[u - 1][v - 1] = 0;
        AdjMatrix[v - 1][u - 1] = 0;
    }
    for (size_t i = 0; i < n; ++i) {
        AdjMatrix[i][i] = 0;
    }
    isBipartite(AdjMatrix, n);
}