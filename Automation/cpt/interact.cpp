#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	i64 key;
	cin >> key;
	
	mt19937 rng(key);
	i64 a = key, b = rng();
	cout << a << ' ' << b << endl;

	i64 c;
	cin >> c;

	if (a + b != c) {
		cerr << a << " + " << b << " != " << c << endl;
	}
}
