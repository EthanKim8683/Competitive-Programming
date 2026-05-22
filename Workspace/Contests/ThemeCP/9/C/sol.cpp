#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int P;
    cin >> P;
    int N = 1 << P;

    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
    }

    // aim for N
    // give each node an xor sum, pairs of weights act as disjoint edges between
    // them
  }
}
