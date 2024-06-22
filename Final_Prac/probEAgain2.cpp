#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isPowerOfEvenNumber(long long int n) {
    if (n <= 1) return false;
    
    // Iterate over possible bases from 2 up to sqrt(n)
    for (long long int base = 2; base * base <= n; ++base) {
        long long int temp = n;
        int power = 0;
        
        // Divide by the base until it is no longer divisible
        while (temp % base == 0) {
            temp /= base;
            power++;
        }
        
        // Check if we reached 1 and the power is even
        if (temp == 1 && power % 2 == 0) {
            return true;
        }
    }
    
    return false;
}

long long int constructTree(vector<long long int>& leafValues, bool isMaxLevel) {
    if (leafValues.size() == 1) {
        return leafValues[0];
    }

    bool nextIsMaxLevel = !isMaxLevel;

    size_t halfSize = leafValues.size() / 2;
    vector<long long int> leftChild(leafValues.begin(), leafValues.begin() + halfSize);
    vector<long long int> rightChild(leafValues.begin() + halfSize, leafValues.end());

    long long int leftValue = constructTree(leftChild, nextIsMaxLevel);
    long long int rightValue = constructTree(rightChild, nextIsMaxLevel);

    if (isMaxLevel) {
        return max(leftValue, rightValue);
    } else {
        return min(leftValue, rightValue);
    }
}

int main() {
    long long int n;
    cin >> n;

    vector<long long int> leafs(n);

    for(int i = 0; i < n; i++) {
        cin >> leafs[i];
    }

    bool isGenap = (n % 2 == 0);
    
    bool startWithMax = isPowerOfEvenNumber(n);

    if(startWithMax){
        cout << constructTree(leafs, true);
    } else {
        cout << constructTree(leafs, false);
    }

    //long long int result = constructTree(leafs, startWithMax);

    //cout << result;

    return 0;
}
