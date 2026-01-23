#include <bits/stdc++.h>

#include "ethankim8683/dp.hpp"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<int>> adj(N);
  for (int i = 1; i < N; i++) {
    int p;
    cin >> p;
    p--;
    adj[p].push_back(i);
  }

  i64 ans = 0;
  auto dfs = [&](auto self, int a) -> int {
    vector<int> w;
    for (auto b : adj[a]) {
      w.push_back(self(self, b));
    }
    int sum = accumulate(w.begin(), w.end(), 0);
    if (w.size() > 0) {
      int wmax = *max_element(w.begin(), w.end());
      if (2 * wmax >= sum) {
        ans += (i64) wmax * (sum - wmax);
      } else {
        auto K = subset_sum_speedup_1<u64>(w);
        i64 cost = 0;
        for (int i = 0; i <= sum; i++) {
          if (!K[i]) continue;
          cost = max(cost, (i64) i * (sum - i));
        }
        ans += cost;
      }
    }
    return sum + 1;
  };
  dfs(dfs, 0);
  cout << ans << '\n';
}
