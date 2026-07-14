#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// 判断字符数组是否完全相同
bool isSameCharGroup(string& str) {
    return str.size() == 4 &&
            str[0] == str[1] &&
            str[1] == str[2] &&
            str[2] == str[3];
}

// 去除前置0
string trimLeadingZero(const string& s) {
    int pos = 0;
    while (pos < 3 && s[pos] == '0') {
        pos++;
    }
    return s.substr(pos);
}

int main(void) {
    string identifers;
    cin >> identifers;

    // 1. 按 ':' 切分为8组
    vector<string> groups;
    stringstream ss(identifers);
    string part;
    while (getline(ss, part, ':')) {
        groups.push_back(part);
    }

    // 2. 找最长的“连续相同且四位字符相同”的区间
    int bestL = -1, bestR = -1;
    int bestLen = 0;

    for (int i = 0; i < 8;) {
        if (!isSameCharGroup(groups[i])) {
            i++;
            continue;
        }

        int j = i;
        while (j + 1 < 8 && groups[j + 1] == groups[i] && isSameCharGroup(groups[j + 1])) {
            j++;
        }

        int len = j - i + 1;

        // 只在更长时更新，保证相同长度时保留最左侧
        if (len > bestLen) {
            bestLen = len;
            bestL = i;
            bestR = j;
        }

        i = j + 1;
    }

    // 3. 先应用规则 2，再对其余组应用规则 1
    vector<string> ans;

    for (int i = 0; i < 8; i++) {
        if (i == bestL) {
            ans.push_back("**");
        }

        if (i >= bestL && i <= bestR) {
            continue;
        }

        ans.push_back(trimLeadingZero(groups[i]));
    }

    // 4. 输出
    for (int i = 0; i < 8; i++) {
        if (i != 0) {
            cout << ':';
        }
        cout << ans[i];
    }
    cout << endl;

    return 0;
}