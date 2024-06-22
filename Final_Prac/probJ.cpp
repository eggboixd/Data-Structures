#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(); 

    string cmd, line;
    map<string, stack<string>> topicStacks;

    for(int i = 0; i < n; i++) {
        cin >> cmd; 

        if (cmd == "CREATE") {
            string createWhat, topicName;
            cin >> createWhat >> topicName;
            topicName = topicName.substr(1); 
            topicStacks[topicName] = stack<string>();
        } else if(cmd == "WRITE") {
            string topic, log;
            cin >> topic >> log;
            topicStacks[topic].push(log);
            
        } else if(cmd == "READ") {
            string readWhat, lastWhat;
            cin >> readWhat >> lastWhat;

            if(topicStacks[lastWhat].empty()){
                cout << "Topic is empty\n";
            } else {
                cout << topicStacks[lastWhat].top() << endl;
                topicStacks[lastWhat].pop();
            }
        }
    }

    return 0;
}
