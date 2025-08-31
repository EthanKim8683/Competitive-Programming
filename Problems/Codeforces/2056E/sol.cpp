#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> segs(M);
    for (auto &[l, r] : segs) {
      cin >> l >> r;
      l--;
    }

    sort(segs.begin(), segs.end(), [&](auto a, auto b) {
      auto size = [&](auto r) -> int { return r.second - r.first; };
      return size(a) < size(b);
    });
    if (segs.empty() or segs.back() != make_pair(0, N)) {
      segs.push_back({0, N});
    }

    mint ans = 1;
    fenwick_tree<int> ft(N + 1);
    for (auto [l, r] : segs) {
      int n = r - l - ft.sum(l, r) - 1;
      ans *= num_binary_trees<mint>(n);

      ft.add(l, r - l - 1 - ft.sum(l, r));
    }
    cout << ans.val() << '\n';
  }
}
