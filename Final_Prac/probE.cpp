#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int compute_root_value(vector<int>& leaf_nodes) {
    int n = leaf_nodes.size();
    
    vector<int> current_level = leaf_nodes;
    
    while (current_level.size() > 1) {
        vector<int> next_level;
        
        for (size_t i = 0; i < current_level.size(); i += 2) {
            int left = current_level[i];
            int right = (i + 1 < current_level.size()) ? current_level[i + 1] : left; 
            
            if (next_level.empty()) {
                next_level.push_back(max(left, right));
            } else if (next_level.size() % 2 == 1) { 
                next_level.push_back(min(left, right));
            } else { 
                next_level.back() = max(next_level.back(), min(left, right));
            }
        }
        
        current_level = next_level;
    }
    
    return current_level[0];
}

int main() {
    int n;
    cin >> n;
    
    vector<int> leafs(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> leafs[i];
    }
    
    int result = compute_root_value(leafs);
    cout << result << endl;
    
    return 0;
}
