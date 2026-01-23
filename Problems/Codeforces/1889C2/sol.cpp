#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N, M, K;
    if (argc > 1) {
      N = 2e5;
      M = 2e5;
      K = 10;
    } else {
      cin >> N >> M >> K;
    }

    // mask of what's being used so far
    // must be subset of current element's mask
    // only add to equal subset
    // skip all ranges with too many bits

    vector<pair<int, int>> days(M);
    if (argc > 1) {
      for (int i = 0; i < M; i++) {
        days[i] = {i, min(i + K, N)};
      }
    } else {
      for (auto &[l, r] : days) {
        cin >> l >> r;
        l--;
      }
    }

    vector<int> ps(N + 1, 0);
    for (auto [l, r] : days) {
      ps[l]++;
      ps[r]--;
    }
    for (int i = 0; i < N; i++) {
      ps[i + 1] += ps[i];
    }

    vector<int> cc;
    for (int i = 0; i < N; i++) {
      if (ps[i] > K) continue;
      cc.push_back(i);
    }
    int N2 = cc.size();
    auto compress = [&](int x) -> int {
      return lower_bound(cc.begin(), cc.end(), x) - cc.begin();
    };

    vector<vector<int>> lefts(N2 + 1), rights(N2 + 1);
    for (int i = 0; i < M; i++) {
      auto [l, r] = days[i];
      l = compress(l);
      r = compress(r);
      if (l == r) continue;

      lefts[l].push_back(i);
      rights[r].push_back(i);
    }

    auto chmax = [&](int &a, int b) -> void { a = max(a, b); };

    vector<int> bits(K, -1);
    vector dp(K + 1, vector<int>(1 << K, -INF));
    dp[0][0] = 0;
    for (int i = 0; i < N2; i++) {
      int mask = 0;
      for (auto j : rights[i]) {
        int k = find(bits.begin(), bits.end(), j) - bits.begin();
        bits[k] = -1;
        mask |= 1 << k;
      }
      for (int j = 0; j < (1 << K); j++) {
        for (int k = __builtin_popcount(j); k <= K; k++) {
          chmax(dp[k][j & ~mask], dp[k][j]);
        }
      }

      mask = 0;
      for (auto j : lefts[i]) {
        int k = find(bits.begin(), bits.end(), -1) - bits.begin();
        bits[k] = j;
        mask |= 1 << k;
      }
      for (int j = 0; j < (1 << K); j++) {
        for (int k = __builtin_popcount(j); k <= K; k++) {
          dp[k][j] = dp[k - __builtin_popcount(j & mask)][j & ~mask];
        }
      }

      mask = 0;
      for (int j = 0; j < K; j++) {
        if (bits[j] == -1) continue;
        mask |= 1 << j;
      }
      for (int j = 0; j <= K; j++) {
        dp[j][mask] += 1;
      }
    }

    int ans = 0;
    for (auto e : dp) {
      chmax(ans, *max_element(e.begin(), e.end()));
    }
    cout << ans << '\n';
  }
}
