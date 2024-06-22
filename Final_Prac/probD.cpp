#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    long long int n;
    cin >> n;
    long long int x = 1;

    if(n <= 0){
        return 0;
    }

    for (long long int i = 1; i <= n; i++){
        x = (x * i) % MOD;
    }

    cout <<  x << endl;

    return 0;
}
