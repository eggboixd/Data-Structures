#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;


    //mup.second.top();

    for (long long int i = 0; i < t; i++) {
        //cout << "testcase: " << i << endl;
        long long int h;
        cin >> h;
        map<long long int, priority_queue<long long int, vector<long long int>, less<long long int>>> mip;
        for (int j = 0; j < h; j++) {
            long long int r, s;
            cin >> r >> s;
            mip[r].push(s);  // insert r with s into the map, push s into its priority_queue
        }
        

        long long int sum = 0;

        for (auto pair = mip.begin(); pair != mip.end(); pair++) {
        //cout << "Key: " << pair.first << ", Values: ";

        long long int add = pair->first;


        
        while (!pair->second.empty() && add>0) {
            //cout << pair.second.top() << " ";
            sum += pair->second.top();
            //cout <<"top of" << pair->first << "is: " << pair->second.top() << endl;
            pair->second.pop();
            add--;
        }

        
        //cout << endl;
        }
        cout << "Duarr skor maksimumnya " << sum << endl;
        //mip.clear();

    // Example usage: print all elements in the map
    
    }
    return 0;
}
