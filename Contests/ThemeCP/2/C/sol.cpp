#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 BASE = 6969;
const i64 MOD = (1ll << 31) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<i64> pows(2e5 + 1);
  pows[0] = 1;
  for (int i = 1; i <= 2e5; i++) {
    pows[i] = pows[i - 1] * BASE % MOD;
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<bool> is_symm(N);
    auto dfs = [&](auto self, int a, int p, int d) -> pair<i64, int> {
      vector<pair<i64, int>> hashes;
      for (auto b : adj[a]) {
        if (b == p) continue;
        hashes.push_back(self(self, b, a, d + 1));
      }

      map<pair<i64, int>, int> counts;
      for (auto k : hashes) {
        counts[k]++;
      }
      int odd_count = 0;
      pair<i64, int> odd;
      for (auto [k, count] : counts) {
        if (count % 2 == 1) {
          odd_count++;
          odd = k;
        }
      }
      if (odd_count == 0) {
        is_symm[a] = true;
      } else if (odd_count == 1) {
        int i = 0;
        for (auto b : adj[a]) {
          if (b == p) continue;
          if (hashes[i] == odd) {
            is_symm[a] = is_symm[b];
          }
          i++;
        }
      } else {
        is_symm[a] = false;
      }

      sort(hashes.begin(), hashes.end());
      i64 hash_ = d;
      int len_ = 1;
      for (auto [hash, len] : hashes) {
        (hash_ *= pows[len]) %= MOD;
        (hash_ += hash) %= MOD;
        len_ += len;
      }
      return {hash_, len_};
    };
    dfs(dfs, 0, -1, 0);

    cout << (is_symm[0] ? "YES" : "NO") << '\n';
  }
}
