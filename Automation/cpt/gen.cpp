#include <bits/stdc++.h>
using namespace std;

int main() {
	unsigned key;
	cin >> key;

	mt19937 rng(key);

	if (rng() % 3 == 0) *(int *) 0 = 0;

	cout << rng() << ' ' << rng();
}
