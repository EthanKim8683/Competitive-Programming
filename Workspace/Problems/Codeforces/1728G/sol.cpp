#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint998244353;

const i64 BASE = 6969;
const i64 MOD = (1ll << 31) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int D, N, M;
  cin >> D >> N >> M;

  vector<int> L(N);
  for (auto &e : L) cin >> e;

  vector<int> P(M);
  for (auto &e : P) cin >> e;
  sort(P.begin(), P.end());

  int Q;
  cin >> Q;

  vector<int> F(Q);
  for (auto &e : F) cin >> e;

  // auto chmax = [&](int &a, int b) -> void { a = max(a, b); };
  // vector<int> dp(1 << 16, 0);
  // dp[0] = 1;
  // for (int i = 0; i < (1 << 16); i++) {
  //   if (~i & 1) {
  //     chmax(dp[i | 1], dp[i] + 1);
  //   }
  //   for (int j = 0; j + 1 < 16; j++) {
  //     if ((i >> j & 3) != 1) continue;
  //     chmax(dp[i ^ 3 << j], dp[i] + 1);
  //   }
  // }
  // cerr << dp[(1 << 16) - 1] << '\n';
  //
  // there are at most 137 mask sequences

  auto get_mask_seq = [&](int x) -> vector<pair<int, int>> {
    vector<pair<int, int>> dists;
    for (int j = 0; j < M; j++) {
      dists.push_back({abs(P[j] - x), j});
    }
    sort(dists.begin(), dists.end());

    vector<pair<int, int>> rv;
    int mask = 0;
    rv.push_back({mask, 0});
    for (auto [d, j] : dists) {
      mask |= 1 << j;
      rv.push_back({mask, d});
    }
    rv.push_back({mask, D + 1});
    return rv;
  };

  auto hash_mask_seq = [&](vector<pair<int, int>> seq) -> i64 {
    i64 rv = 0;
    for (auto [mask, d] : seq) {
      rv = (rv * BASE + mask) % MOD;
    }
    return rv;
  };

  map<i64, vector<vector<pair<int, int>>>> by_hash;
  for (auto e : L) {
    auto seq = get_mask_seq(e);
    by_hash[hash_mask_seq(seq)].push_back(seq);
  }

  vector<mint> dp(1 << M, 0);
  dp[0] = 1;
  for (auto [hash, seqs] : by_hash) {
    vector<mint> dp2(M + 1, 0);
    dp2[0] = 1;
    for (auto seq : seqs) {
      vector<mint> dp3(M + 1, 0);
      for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
          dp3[max(i, j)] += dp2[i] * (seq[j + 1].second - seq[j].second);
        }
      }
      dp2 = dp3;
    }

    vector<mint> dp3(1 << M, 0);
    for (int i = 0; i < (1 << M); i++) {
      for (int j = 0; j <= M; j++) {
        dp3[i | seqs[0][j].first] += dp[i] * dp2[j];
      }
    }
    dp = dp3;
  }

  for (int i = 0; i < M; i++) {
    for (int j = (1 << M) - 1; j >= 0; j--) {
      if (~j >> i & 1) {
        dp[j] += dp[j ^ 1 << i];
      }
    }
  }

  for (auto e : F) {
    auto seq = get_mask_seq(e);
    mint ans = 0;
    for (int i = 0; i <= M; i++) {
      ans += dp[seq[i].first ^ ((1 << M) - 1)] *
             (seq[i + 1].second - seq[i].second);
    }
    cout << ans.val() << '\n';
  }
}
