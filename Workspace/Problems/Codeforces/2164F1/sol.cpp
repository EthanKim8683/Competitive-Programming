#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int MAXN = 5000;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<mint> facts(MAXN + 1), inv_facts(MAXN + 1);
  facts[0] = inv_facts[0] = 1;
  for (int i = 1; i <= MAXN; i++) {
    facts[i] = facts[i - 1] * i;
    inv_facts[i] = inv_facts[i - 1] / i;
  }
  vector binoms(MAXN + 1, vector<mint>(MAXN + 1, 0));
  for (int i = 0; i <= MAXN; i++) {
    for (int j = 0; j <= i; j++) {
      binoms[i][j] = facts[i] * inv_facts[j] * inv_facts[i - j];
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 1; i < N; i++) {
      int p;
      cin >> p;
      p--;
      adj[p].push_back(i);
    }

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto dfs = [&](auto self, int a,
                   vector<int> order) -> pair<vector<int>, mint> {
      order.insert(order.begin() + A[a], a);

      vector<int> gaps(order.size() + 1, 0);
      mint count = 1;

      for (auto b : adj[a]) {
        auto [gaps2, count2] = self(self, b, order);

        assert(gaps.size() == gaps2.size());
        for (int i = 0; i < gaps.size(); i++) {
          gaps[i] += gaps2[i];
          count *= binoms[gaps[i]][gaps2[i]];
        }

        count *= count2;
      }

      gaps[A[a] + 1] += gaps[A[a]] + 1;
      gaps.erase(gaps.begin() + A[a]);

      return {gaps, count};
    };
    auto [gaps, count] = dfs(dfs, 0, {});
    cout << count.val() << '\n';
  }
}
