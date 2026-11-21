#include <bits/stdc++.h>
using namespace std;

const int INF = 99;   // Number under 100

int tsp(int n, vector<vector<int>>& graph) {
    int full = 1 << n;
    vector<vector<int>> dp(full, vector<int>(n, INF));

    dp[1][0] = 0;

    for (int mask = 1; mask < full; mask++) {
        for (int u = 0; u < n; u++) {
            if (dp[mask][u] == INF || !(mask & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                if (graph[u][v] == INF) continue;   // skip "no path" edges
                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + graph[u][v]);
            }
        }
    }

    int ans = INF;
    for (int i = 1; i < n; i++)
        if (dp[full - 1][i] != INF)
            ans = min(ans, dp[full - 1][i] + graph[i][0]);

    return ans;
}

int main() {
    int n = 4;
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    cout << "Minimum cost of TSP tour: " << tsp(n, graph) << endl;
    return 0;
}