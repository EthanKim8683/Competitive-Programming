#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<int> sieve(2e6 + 1);
  iota(sieve.begin(), sieve.end(), 0);
  for (int i = 2; i * i <= 2e6; i++) {
    if (sieve[i] != i) continue;
    for (int j = i * i; j <= 2e6; j += i) {
      sieve[j] = min(sieve[j], i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    i64 ans = 0;
    for (int b = 1; b <= M; b++) {
      vector<pair<int, int>> counts;
      for (int i = b; i > 1; i /= sieve[i]) {
        if (counts.empty() or counts.back().first != sieve[i]) {
          counts.push_back({sieve[i], 0});
        }
        counts.back().second++;
      }
      auto dfs = [&](auto self, int i, i64 v) -> void {
        i64 a = v - b;
        if (a > N) return;

        if (i == counts.size()) {
          if (1 <= a and b * gcd(a, b) % (a + b) == 0) {
            ans++;
          }
          return;
        }

        auto [p, count] = counts[i];
        for (int j = 0; j <= 2 * count; j++) {
          self(self, i + 1, v);
          v *= p;
        }
      };
      dfs(dfs, 0, 1);
    }
    cout << ans << '\n';
  }
}
