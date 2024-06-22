// C++ program to illustrate
// size() function on set
#include <bits/stdc++.h>
using namespace std;

int main()
{
	// Take any two sets
	set<char> set1, set2;
	for (int i = 0; i < 4; i++) {
		set1.insert('a' + i);
	}

	// Printing the size of sets
	cout << "set1 size: " << set1.size();
	cout << endl;
	cout << "set2 size: " << set2.size();
	return 0;
}
