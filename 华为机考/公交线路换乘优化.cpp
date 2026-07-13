#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

int main() {
    // 1.数据接收
    int N;
    cin >> N;

    string line;
    getline(cin, line); // 清除换行

    unordered_map<int, vector<int>> gragh;
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        stringstream ss(line);
        int x;
        vector<int> nums;
        while (ss >> x) {
            nums.push_back(x);
        }

        // 建图
        int startIndex = 1; // 跳过第一个 线路的站点数量
        for (int j = startIndex; j + 1< (int)nums.size(); j++) {
            int from = nums[j];
            int to = nums[j + 1];
            gragh[from].push_back(to);
        }
    }

    int start, end;
    cin >> start >> end;
    if (start == end) {
        cout << 1 << endl;
        return 0;
    }

    unordered_map<int, int> dist;
    queue<int> q;
    dist[start] = 1;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (gragh.find(cur) == gragh.end()) continue;
        for (int next : gragh[cur]) {
            if (dist.find(next) == dist.end()) {
                dist[next] = dist[cur] + 1;
                if (next == end) {
                    cout << dist[next] << endl;
                    return 0;
                }
                q.push(next);
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
