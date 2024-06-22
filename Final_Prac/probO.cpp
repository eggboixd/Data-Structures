#include <bits/stdc++.h>

using namespace std;

const int MOD = 7340033;

int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (1LL * result * base) % mod;
        }
        base = (1LL * base * base) % mod;
        exp /= 2;
    }
    return result;
}

int interpolate(int n, const vector<int>& xs, const vector<int>& ys) {
    int k = xs.size();
    vector<int> dp(k); 

    dp[0] = ys[0];

    for (int i = 1; i < k; ++i) {
        int term = ys[i];
        for (int j = 0; j < i; ++j) {
            term = (1LL * term * (n - xs[j] + MOD) % MOD) % MOD;
            term = (1LL * term * mod_pow(xs[i] - xs[j] + MOD, MOD - 2, MOD) % MOD) % MOD;
        }
        dp[i] = (dp[i - 1] + term) % MOD;
    }

    return dp[k - 1];
}

int main() {
    map<int, int> precomputed = {
        {1, 0}, {2, 0}, {3, 232}, {4, 1432}, {5, 5188},
        {6, 14536}, {7, 34464}, {8, 72392}, {9, 138652}, {10, 246968}
    };

    vector<int> xs, ys;
    for (const auto& entry : precomputed) {
        xs.push_back(entry.first);
        ys.push_back(entry.second);
    }

    int T;
    cin >> T;
    vector<int> queries(T);
    for (int i = 0; i < T; ++i) {
        cin >> queries[i];
    }

    vector<int> results(T);
    for (int i = 0; i < T; ++i) {
        int n = queries[i];
        if (precomputed.find(n) != precomputed.end()) {
            results[i] = precomputed[n];
        } else {
            results[i] = interpolate(n, xs, ys);
        }
    }

    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}
