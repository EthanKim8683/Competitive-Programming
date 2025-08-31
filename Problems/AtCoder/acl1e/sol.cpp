#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> P(N);
  for (auto &e : P) cin >> e, e--;

  auto geo = [&](mint a, mint r, int n) -> mint {
    return a * (1 - r.pow(n)) / (1 - r);
  };

  mint tail = 0, accum = 1;
  for (int i = K - 1; i >= 2; i--) {
    mint p1 = (mint) 1 / i, p2 = (mint) (i - 2) / i;
    tail += accum * p1;
    accum *= p2;
  }

  fenwick_tree<mint> ft(N), ft2(N);
  mint ans = 0;
  int i0 = K - 1;
  for (int i = N - 1; i >= 0; i--) {
    mint p1 = (mint) 1 / K, p2 = (mint) (K - 2) / K, p3 = (mint) (K - 1) / K;
    ans += (ft.sum(P[i] + 1, N) - ft.sum(0, P[i])) / p3.pow(max(i, i0));
    ans += ft2.sum(0, P[i]);
    ft.add(P[i],
           (geo(p1, p2, N - i) + p2.pow(N - i) * tail) * p3.pow(max(i, i0)));
    ft2.add(P[i], 1);
  }
  cout << ans.val();
}
