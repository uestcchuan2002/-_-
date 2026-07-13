#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <deque>

using namespace std;

int main(void) 
{
    vector<int> baskets;
    int k;
    int m;

    string line;
    getline(cin, line);
    stringstream ss(line);
    int temp;
    while (ss >> temp) {
        baskets.push_back(temp);
    }

    cin >> k;    
    cin >> m;

    vector<int> rem = baskets;
    deque<int> q;
    for (int i = 0; i < rem.size(); i++) {
        q.push_back(i);
    }

    int ans = 0;
    while (1) {
        ans++;
        int size = min(m, (int)q.size());
        for (int i = 0; i < size; i++) {
            int id = q.front();
            q.pop_front();
            rem[id]--;
            if (rem[id] == 0) {
                if (id == k) {
                    cout << ans << endl;
                    return 0;
                }
            } else {
                q.push_back(id);
            }
        }
    }

    return 0;
}