#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

int main(void) {
    int m, n;
    cin >> m >> n;
    vector<vector<vector<int>>> grid(2, vector<vector<int>>(m, vector<int>(n)));
    vector<pair<int, int>> stair(2, {-1, -1});
    int sl = -1, sx = -1, sy = -1;
    int el = -1, ex = -1, ey = -1;
    for (int layer = 0; layer < 2; layer++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[layer][i][j];

                if (grid[layer][i][j] == 2) {
                    sl = layer;
                    sx = i;
                    sy = j;
                } else if (grid[layer][i][j] == 3) {
                    el = layer;
                    ex = i;
                    ey = j;
                } else if (grid[layer][i][j] == 4) {
                    stair[layer] = {i, j};
                }
            }
        }
    }

    int INF = 1e9;
    vector<vector<vector<int>>> dist(2, vector<vector<int>>(m, vector<int>(n, INF)));
    dist[sl][sx][sy] = 0;
    queue<tuple<int, int, int>> q;
    q.push(make_tuple(sl, sx, sy));
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto cur = q.front();
        int layer = get<0>(cur);
        int x = get<1>(cur);
        int y = get<2>(cur);
        q.pop();

        int d = dist[layer][x][y];
        if (layer == el && x == ex && y == ey) {
            cout << d << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
            if (grid[layer][nx][ny] == 1) continue;
            if (dist[layer][nx][ny] != INF) continue;

            dist[layer][nx][ny] = d + 1;
            q.push(make_tuple(layer, nx, ny));
        }

        if (grid[layer][x][y] == 4) {
            int orterlayer = 1 - layer;
            int nx = stair[orterlayer].first;
            int ny = stair[orterlayer].second;
            if (dist[orterlayer][nx][ny] == INF) {
                dist[orterlayer][nx][ny] = d + 1;
                q.push(make_tuple(orterlayer, nx, ny));
            }
        }
    }


    cout << -1 << endl;
    return 0;
}
