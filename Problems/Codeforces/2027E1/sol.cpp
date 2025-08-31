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

    vector<int> X(N);
    for (auto &e : X) cin >> e;

    auto max_d = [&](int a, int x) -> int {
      if (x <= a) return x;
      if ((a & x) == a) return a;
      return ((a & ~((1 << __lg(a & ~x)) - 1)) - 1) & x;
    };

    int nim = 0;
    for (int i = 0; i < N; i++) {
      int grundy, x = X[i] & ((2 << __lg(A[i])) - 1);
      if (x <= A[i]) {
        grundy = __builtin_popcount(x);
      } else {
        int b = x & -x;
        if (x - b > A[i]) {
          grundy = __builtin_popcount(x);
        } else {
          grundy = 0;
        }
      }
      cerr << grundy << ' ';
      nim ^= grundy;
    }
    cerr << '\n';
    cout << (nim ? "Alice" : "Bob") << '\n';

    // I think my takeaway from this is that invariants don't need to be the
    // basis of a solution, but they can bring me closer to one or narrow down
    // the possibilities for one
  }
}
