#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sstream>

using namespace std;

char i_to_c(int data) {
    char result;
    if (data < 10) {
        result = data + '0';
    } else {
        result = data - 10 + 'A';
    }
    return result;
}

string m_function(string &key, string &data) {
    int key_size = key.size();
    int data_size = data.size();

    string result;
    for (int i = 0; i < data_size; i++) {
        char data_c = data[i];
        char key_c = key[i % key_size];
        if (data_c >= '0' && data_c <= '9') {
            data_c -= '0';
        } else {
            data_c -= 'A' - 10;
        }
        if (key_c >= '0' && key_c <= '9') {
            key_c -= '0';
        } else {
            key_c -= 'A' - 10;
        }

        char temp = i_to_c(key_c ^ data_c);
       
        result.push_back(temp);
    }
    return result;
}

int main(void) {
    // 1. 输入接收
    int T;
    cin >> T;
    cin.ignore();

    vector<vector<string>> key_date_vec(T);
    string line;
    for (int i = 0; i < T; i++) {
        getline(cin, line);
        stringstream ss(line);
        string key, data;
        ss >> key >> data;
        key_date_vec[i].push_back(key);
        key_date_vec[i].push_back(data);
    }

    // 2. 处理
    vector<string> result;
    for (int i = 0; i < T; i++) {
        string temp = m_function(key_date_vec[i][0], key_date_vec[i][1]);
        cout << temp << endl;
    }

    return 0;
}









