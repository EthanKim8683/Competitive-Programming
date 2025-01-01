#include <bits/stdc++.h>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	mt19937 rng(a);
	if (rng() % 100 < 28) *(int *) 0 = 0;

	cout << a + b << endl;
}
