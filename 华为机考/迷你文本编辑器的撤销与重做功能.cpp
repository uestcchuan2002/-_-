#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>

using namespace std;

struct opt_strcut
{
    string opt;
    string text;
};

stack<opt_strcut> opt_st_undo;
stack<opt_strcut> opt_st_redo;

// 清空所有撤销操作
void opt_empty(void) {    
    while (!opt_st_redo.empty()) {
        opt_st_redo.pop();
    }
}

// 插入操作字符串
void opt_append(string & text, string& x) {
    // 清空所有撤销操作
    opt_empty();

    opt_strcut new_opt;
    new_opt.opt = "APPEND";
    new_opt.text = x;
    opt_st_undo.push(new_opt);

    text += x;
}

// 删除文本末尾最后一个字符
void opt_pop(string & text) {
    // 清空所有撤销操作
    

    if (text.size() != 0) {
        opt_empty();
        opt_strcut new_opt;
        new_opt.opt = "POP";
        new_opt.text = text[text.size() - 1];
        opt_st_undo.push(new_opt);

        text.resize(text.size() - 1);
    }
}

// 撤销上一次APPEND或POP操作
void opt_undo(string & text) {
    if (!opt_st_undo.empty()) {
        // 弹出撤销栈，加入重做栈
        opt_strcut new_opt;
        new_opt = opt_st_undo.top();
        opt_st_undo.pop();
        opt_st_redo.push(new_opt);

        if (new_opt.opt == "APPEND") {
            // 删除末尾的新加入的text, 长度为len
            int len = new_opt.text.size();
            text.resize(text.size() - len);
        } else if (new_opt.opt == "POP") {
            // 在末尾恢复删除的text
            text += new_opt.text;
        }
    }
}

// 重做上一次被撤销的操作，文本恢复至撤销前状态
void opt_redo(string & text) {
    if (!opt_st_redo.empty()) {
        opt_strcut new_opt;
        new_opt = opt_st_redo.top();
        opt_st_redo.pop(); 
        opt_st_undo.push(new_opt);
        if (new_opt.opt == "APPEND") {
            text += new_opt.text;
        } else if (new_opt.opt == "POP") {
            text.resize(text.size() - 1);
        }
    }
}

int main(void) 
{
    // 1.接收
    int N;
    cin >> N;
    string line;
    getline(cin, line);

    vector<vector<string>> opt(N);
    for (int i = 0; i < N; i++) {
        getline(cin, line);
        stringstream ss(line);
        string temp;
        while (ss >> temp) {
            opt[i].push_back(temp);
        }
    }

    // 2.操作
    string text;
    for (int i = 0; i < N; i++) {
        if (opt[i][0] == "APPEND") {
            opt_append(text, opt[i][1]);
        } else if (opt[i][0] == "POP") {
            opt_pop(text);
        } else if (opt[i][0] == "UNDO") {
            opt_undo(text);
        } else if (opt[i][0] == "REDO") {
            opt_redo(text);
        }
    }
    if (text.empty()) {
        cout << "nothing" << endl;
    } else {
        cout << text << endl;
    }
    
    return 0;
}
