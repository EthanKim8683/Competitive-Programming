#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<array<int, 3>> conds(M);
  for (auto &[X, Y, Z] : conds) {
    cin >> X >> Y >> Z;
    X--, Y--;
  }

  vector<int> ans(N, 0);
  bool ok = true;
  for (int i = 0; i < 30; i++) {
    dsu_with_potentials<int> d(
        N, 0, [](int a, int b) { return a ^ b; }, [](int x) { return x; });
    for (auto [x, y, z] : conds) {
      ok = ok and d.merge(x, y, z >> i & 1);
    }
    vector<int> sum(N, 0);
    for (int j = 0; j < N; j++) {
      sum[d.leader(j)] += d.potential(j);
    }
    vector<int> ground(N, 0);
    for (int j = 0; j < N; j++) {
      if (j != d.leader(j)) continue;
      ground[j] = d.size(j) - sum[j] < sum[j];
    }
    for (int j = 0; j < N; j++) {
      ans[j] |= (ground[d.leader(j)] ^ d.potential(j)) << i;
    }
  }
  if (!ok) {
    cout << -1;
  } else {
    for (auto e : ans) {
      cout << e << ' ';
    }
  }
}
