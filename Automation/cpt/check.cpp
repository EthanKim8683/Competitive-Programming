#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	i64 a, b;
	cin >> a >> b;

	i64 c;
	cin >> c;

	if (a + b != c)
		cout << a << " + " << b << " != " << c;
	else
		cout << "AC";
}
