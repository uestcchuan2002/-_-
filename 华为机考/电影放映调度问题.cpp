#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) 
{
    int n;
    cin >> n;

    vector<vector<int>> movies;
    int s, e;
    for (int i = 0; i < n; i++) {
        vector<int> temp(2);
        cin >> s >> e;
        temp[0] = s;
        temp[1] = e;
        movies.push_back(temp);
    }

    int result = 1;
    sort(movies.begin(), movies.end());
    int start = movies[0][0];
    int end = movies[0][1];
    for (int i = 1; i < n; i++) {
        if (movies[i][0] >= end) {
            result++;
            start = movies[i][0];
            end = movies[i][1];
        } else if (movies[i][0] >= start && movies[i][1] < end ) {
            start = movies[i][0];
            end = movies[i][1];
        } 
    }

    cout << result << endl;

    return 0;
}