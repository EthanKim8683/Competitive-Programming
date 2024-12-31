#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	i64 a, b;
	cin >> a >> b;

	i64 c;
	cin >> c;
	
	this_thread::sleep_for(chrono::milliseconds(1'000));
	
	if (a + b != c) {
		cerr << a << " + " << b << " != " << c << endl;
	}
}
