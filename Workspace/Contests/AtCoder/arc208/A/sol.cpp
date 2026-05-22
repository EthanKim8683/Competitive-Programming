#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    // players either remove all, or all but one
    //
    // if it's all ones, it's ((the number of non-zero numbers) - (the number of
    // ones in the OR sum)) % 2 == 0 ? "Bob" : "Alice"
    //
    // look at the numbers with at least two ones: Alice wants to use these
    // numbers to, in the end, get the parity of the number of non-zero numbers
    // to be different from the number of ones in the OR sum
    //
    // if the number of numbers with at least two ones is:
    //  - odd, Alice chooses the final parity
    //  - even, Bob chooses the final parity

    // (x+y)^1 = 1x   + 1y
    // (x+y)^2 = 1x^2 + 2xy   + 1y^2
    // (x+y)^3 = 1x^3 + 3x^2y + 3xy^2   + 1y^3
    // (x+y)^4 = 1x^4 + 4x^3y + 6x^2y^2 + 6xy^3 + 1y^4

    int n = 0;
    for (auto e : A) {
      if (__builtin_popcount(e) >= 2) {
        n++;
      }
    }

    cout << (n % 2 == 1 ? "Bob" : "Alice") << '\n';
  }
}