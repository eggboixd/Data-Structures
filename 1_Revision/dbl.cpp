#include <iostream>
#include <stack>
#include <string.h>

using namespace std;

int main() {
    stack<int> scores;
    int n;
    cin >> n;

    char cmd[20];
    int val;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        if (strcmp(cmd, "add") == 0) {
            cin >> val;
            scores.push(val);
        } else if (strcmp(cmd, "dbl") == 0) {
            int newtop = scores.top() * 2;
            scores.push(newtop);
        } else if (strcmp(cmd, "six") == 0) {
            int newtop = scores.top() + 6;
            scores.push(newtop);
        } else if (strcmp(cmd, "del") == 0) {
            scores.pop();
        } else if (strcmp(cmd, "total") == 0) {
            int total = 0;
            stack<int> temp = scores;
            while (!temp.empty()) {
                total += temp.top();
                temp.pop();
            }
            cout << total << endl;
        }
    }

    return 0;
}