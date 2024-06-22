#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    stack<int> scores;
    int n;
    cin >> n;

    string cmd;
    int val;
    for (int i = 0; i < n; i++) {
        cin >> cmd;
        if (cmd == "add") {
            cin >> val;
            scores.push(val);
        } else if (cmd == "dbl") {
            int newtop = scores.top() * 2;
            scores.push(newtop);
        } else if (cmd == "six") {
            int newTop = scores.top() + 6;
            scores.push(newTop); 
        } else if (cmd == "total") {
            int total = 0;
            stack<int> temp = scores;
            while (!temp.empty()) {
                total += temp.top();
                temp.pop();
            }
            cout << total << endl;
        } else if (cmd == "del") {
            scores.pop();
        }
    }

    return 0;
}
