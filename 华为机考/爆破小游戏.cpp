#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct node
{
    int index;      // 节点下标
    int least_dk;   // 剩余距离
};

int main(void) {
    int N = 0, K = 0;
    cin >> N >> K;
    vector<int> value(N, 0);
    for (int i = 0; i < N; i++) {
        int x = 0;
        cin >> x;
        value[i] = x;
    }
    int INF = 1e9;
    vector<vector<int>> gragh(N, vector<int>(N, INF));
    unordered_map<int, vector<int>> adj;
    for (int i = 0; i < N - 1; i++) {
        int n_i = -1, n_j = -1, d_k = INF;
        cin >> n_i >> n_j >> d_k;
        gragh[n_j][n_i] = d_k;
        gragh[n_i][n_j] = d_k;
        adj[n_i].push_back(n_j);
        adj[n_j].push_back(n_i);
    }
    
    int result = 0;
    stack<node> st;
    for (int i = 0; i < N; i++) {
        int cur_value = value[i];
        // 用于表示当前节点是否已经使用过
        vector<int> is_used(N, false);
        is_used[i] = true;

        // bfs获取以节点i为起点的价值
        node n;
        n.index = i;
        n.least_dk = K;
        st.push(n);
        while (!st.empty())
        {
            node cur_n = st.top();
            st.pop();
            for (auto it : adj[cur_n.index]) {
                if (gragh[cur_n.index][it] <= cur_n.least_dk && is_used[it] == false) {
                    node nx;
                    nx.index = it;
                    nx.least_dk = cur_n.least_dk - gragh[cur_n.index][it];
                    st.push(nx);
                    cur_value += value[it];
                    is_used[it] = true;
                }
            }
        }
        result = max(result, cur_value);
    }

    cout << result << endl;

    return 0;
}
