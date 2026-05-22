#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> P(N);
  for (auto &e : P) cin >> e, e--;

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[P[i]] = i;
  }

  auto tri = [&](i64 x) -> i64 { return x * (x + 1) / 2; };
  fenwick_tree<int> ft(N);
  i64 ans = 0;
  for (int i = N - 1; i >= 0; i--) {
    ans += tri(i) - tri(index[i] - ft.sum(0, index[i]));
    ft.add(index[i], 1);
  }
  cout << ans;
}
