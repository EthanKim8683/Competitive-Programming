#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"
#include "ethankim8683/data_structures.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  implicit_treap<int> tr(2e5, 0);
  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> inserts(M);
    for (auto &[x, y] : inserts) {
      cin >> x >> y;
      x--, y--;
    }

    int sum = 0;
    for (auto [x, y] : inserts) {
      sum += 1;
      tr.insert(y, 1);
      if (y - 1 >= 0) {
        sum -= tr.get(y - 1);
        tr.set(y - 1, 0);
      }
    }

    for (int i = M - 1; i >= 0; i--) {
      auto [x, y] = inserts[i];
      tr.erase(y);
    }

    mint ans = binom<mint>(2 * N - 1, N);
    for (int i = N - sum; i <= N - 1; i++) {
      ans -= binom<mint>(N - 1 + i, i);
    }
    cout << ans.val() << '\n';
  }
}
