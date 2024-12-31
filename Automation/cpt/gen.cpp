#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	i64 key;
	cin >> key;
	
	this_thread::sleep_for(chrono::milliseconds(1'000));
	
	mt19937 rng(key);
	cout << key << ' ' << rng() << endl;
}
