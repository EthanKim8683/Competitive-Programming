#include <bits/stdc++.h>
using namespace std;

int main() {
	random_device rd;
	mt19937 rng(rd());
	if (rng() % 3 == 0) {
		*(int *) 0 = 0;
	}
	cout << "Hello World!" << endl;
}
