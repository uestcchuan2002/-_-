#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "cstdlib"

using namespace std;

int main(void) 
{
    // 1. 接收数据
    int N, M, C;
    cin >> N >> M >> C;
    cin.ignore();

    vector<vector<int>> grid(N);
    string line;
    int x;
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        stringstream ss(line);
        while (ss >> x) {
            grid[i].push_back(x);
        }
    }

    // 2. 处理
    int ans = INT_MAX;
    for (int target = 1; target <= C; target++) {
        vector<vector<int>> dp(N, vector<int>(M, INT_MAX));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int cost = abs(target - grid[i][j]);

                if (i == 0 && j == 0) {
                    dp[i][j] = cost;
                }
                if (i > 0) dp[i][j] = min(dp[i - 1][j] + cost, dp[i][j]);
                if (j > 0) dp[i][j] = min(dp[i][j - 1] + cost, dp[i][j]);
            }
        }
        ans = min(ans, dp[N - 1][M - 1]);
    }

    cout << ans << endl;
    return 0;
}

