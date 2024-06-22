#include <bits/stdc++.h>
using namespace std;

long long int constructTree(queue<long long int>& leafValues, bool isMaxLevel) {
    while (leafValues.size() > 1) {
        queue<long long int> temp;
        while (!leafValues.empty()) {
            long long int num1 = leafValues.front();
            leafValues.pop();
            if (leafValues.empty()) {
                // In case there's an odd number of elements
                if (isMaxLevel) {
                    temp.push(num1);
                } else {
                    temp.push(num1);
                }
                break;
            }
            long long int num2 = leafValues.front();
            leafValues.pop();

            if (isMaxLevel) {
                long long int resMax = max(num1, num2);
                temp.push(resMax);
            } else {
                long long int resMin = min(num1, num2);
                temp.push(resMin);
            }
        }
        leafValues = temp;
        isMaxLevel = !isMaxLevel;
    }

    // After the loop, leafValues should have exactly one element
    return leafValues.front();
}

int main() {
    long long int n;
    cin >> n;

    queue<long long int> leafs;

    for (int i = 0; i < n; i++) {
        long long int value;
        cin >> value;
        leafs.push(value);
    }

    bool isEvenPow = ceil(log2(n)) == floor(log2(n));   
    bool isEven = (int)log2(n) % 2 != 0;

    cout << constructTree(leafs, isEven);

    return 0;
}
