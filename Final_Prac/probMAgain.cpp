

// C++ program to illustrate 
// implementation of size() function 
#include <bits/stdc++.h> 
using namespace std; 
  
int main() 
{ 

    int t;
    cin >> t;

    for(int i = 0; i < t; i++){
        int v, e;
        cin >> v >> e;
        set<string> connection;
        for(int j = 0; j < e; j++){
            string v1, v2;
            cin >> v1 >> v2;
            connection.insert(v1);
            connection.insert(v2);
        }

        //cout << connection.size() << endl ;
        if (connection.size() - v == 0){
            cout << "Tidak Menyirkel" << endl;
        } else {
            cout << "Menyirkel" << endl;
        }
    }
    /*
    // Take any two maps 
    map<int, string> map1, map2; 
      
    // Inserting values 
    map1.insert(make_pair(1, "India")); 
    map1.insert(make_pair(2, "Nepal")); 
    map1.insert(make_pair(3, "Sri Lanka")); 
    map1.insert(make_pair(4, "Myanmar")); 
      
    // Printing the size 
    cout << "map1 size: " << map1.size(); 
    cout << endl; 
    cout << "map2 size: " << map2.size(); 
    */
    return 0; 
}