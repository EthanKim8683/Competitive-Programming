#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"
#include "ethankim8683/trees.hpp"

using namespace std;
using namespace atcoder;

using mint = modint1000000007;

struct unit {
  mint sum, sub;
  int size;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  auto [dp, adj_dp] = rrdp<unit, unit>(
      adj, {0, 0, 0},
      [](unit dp, int a, int i) -> unit { return {dp.sum, dp.sub, dp.size}; },
      [](unit dp1, unit dp2) -> unit {
        return {dp1.sum + dp2.sum, dp1.sub + dp2.sub, dp1.size + dp2.size};
      },
      [K](unit dp, int a) -> unit {
        mint n = binom<mint>(dp.size + 1, K) - dp.sub;
        return {dp.sum + n * (dp.size + 1), dp.sub + n, dp.size + 1};
      });
  mint ans = 0;
  for (auto e : dp) {
    ans += e.sum;
  }
  cout << ans.val();
}
