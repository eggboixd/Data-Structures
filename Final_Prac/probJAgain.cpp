#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Stack {
private:
    std::stack<T> elements;

public:
    void push(const T& value) {
        elements.push(value);
    }

    void pop() {
        if (!elements.empty()) {
            elements.pop();
        } else {
            std::cerr << "Stack underflow! Cannot pop from an empty stack.\n";
        }
    }

    T top() const {
        if (!elements.empty()) {
            return elements.top();
        } else {
            std::cerr << "Stack is empty! There is no top element.\n";
            return T(); 
        }
    }

    bool empty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};

int main() {
    int n;
    cin >> n;
    cin.ignore(); 

    string cmd, line;
    map<string, Stack<string>> topicStacks;

    for(int i = 0; i < n; i++) {
        getline(cin, line); 

        stringstream ss(line); 

        ss >> cmd; 

        if (cmd == "CREATE" && ss >> cmd && cmd == "TOPIC") {
            string topicName;
            getline(ss, topicName); 
            topicName = topicName.substr(1); 
            topicStacks[topicName] = Stack<string>();
        } else if(cmd == "WRITE") {
            string topic, log;
            ss >> topic >> log;
            if(topicStacks.find(topic) != topicStacks.end()) {
                topicStacks[topic].push(log);
            } else {
                cout << "Topic is empty\n";
            }
            
        } else if(cmd == "READ" && ss >> cmd && cmd == "LAST") {
            string lastWhat;
            ss >> lastWhat;
            
            if(topicStacks.find(lastWhat) != topicStacks.end() && !topicStacks[lastWhat].empty()) {
                cout << topicStacks[lastWhat].top() << endl;
                topicStacks[lastWhat].pop();
            } else {
                cout << "Topic is empty\n";
            }
        }
    }

    return 0;
}
