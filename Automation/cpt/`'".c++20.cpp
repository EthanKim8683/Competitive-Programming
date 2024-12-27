#include <iostream>
using namespace std;

int main() {
	// It suffices to add newlines, so long as the output flushes
	// in the end
	// int x;
	// cout << "x=\n";
	// cin >> x;
	// int y;
	// cout << "y=\n";
	// cin >> y;
	// cout << "x+y=" << x + y << endl;

	*(int *) 0 = 0;

	int x;
	cout << "x=", cout.flush();
	cin >> x;
	int y;
	cout << "y=", cout.flush();
	cin >> y;
	cout << "x+y=" << x + y << endl;
}
