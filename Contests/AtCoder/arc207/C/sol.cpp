#include <bits/stdc++.h>

#include "atcoder/lazysegtree"

using namespace std;
using namespace atcoder;

const int MAXK = 30;
const int INF = 1e9;

int op(int a, int b) { return max(a, b); }
int e() { return -INF; }
int composition(int a, int b) { return max(a, b); }
int mapping(int a, int b) { return max(a, b); }
int id() { return -INF; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector prev(N, vector<int>(MAXK, -INF));
  for (int i = 0; i + 1 < N; i++) {
    prev[i + 1] = prev[i];
    for (int j = 0; j < MAXK; j++) {
      if (~A[i] >> j & 1) continue;
      prev[i + 1][j] = i;
    }
  }

  vector next(N, vector<int>(MAXK, INF));
  for (int i = N - 1; i >= 0; i--) {
    if (i + 1 < N) {
      next[i] = next[i + 1];
    }
    for (int j = 0; j < MAXK; j++) {
      if (~A[i] >> j & 1) continue;
      next[i][j] = i;
    }
  }

  auto chmax = [&](int &a, int b) -> void { a = max(a, b); };

  vector dp(MAXK + 1,
            lazy_segtree<int, [&](int a, int b) -> int { return max(a, b); },
                         [&]() -> int { return -INF; }, int,
                         [&](int a, int b) -> int { return max(a, b); },
                         [&](int a, int b) -> int { return max(a, b); },
                         [&]() -> int { return -INF; }>(N + 1));
  dp[0].set(0, 0);
  for (int i = 0; i < N; i++) {
    vector<int> order1(MAXK);
    iota(order1.begin(), order1.end(), 0);
    sort(order1.begin(), order1.end(),
         [&](int a, int b) -> bool { return prev[i][a] > prev[i][b]; });

    vector<int> order2(MAXK);
    iota(order2.begin(), order2.end(), 0);
    sort(order2.begin(), order2.end(),
         [&](int a, int b) -> bool { return next[i][a] < next[i][b]; });

    vector<pair<int, int>> trans;
    trans.push_back({0, -1});
    int mask = 0;
    for (int j = 0; j < MAXK; j++) {
      int k = order2[j], l = next[i][k];
      if (l == INF) {
        trans.push_back({N + 1, -1});
      } else {
        mask |= 1 << k;
        trans.push_back({l + 1, mask});
      }
    }
    trans.push_back({N + 1, -1});

    for (int j = 0; j <= MAXK; j++) {
      auto [l, mask1] = trans[j];
      int r = trans[j + 1].first, dp_ = -INF, mask2 = 0;
      for (int k = 0; k <= MAXK; k++) {
        if (mask2 <= mask1) {
          dp_ = max(dp_, dp[k].get(i) + 1);
        }

        if (k < MAXK) {
          int l = order1[k], m = prev[i][l];
          if (m == -INF) break;
          mask2 |= 1 << l;
        }
      }
      dp[j].apply(l, r, dp_);
    }
  }
  int ans = -INF;
  for (int i = 0; i <= MAXK; i++) {
    chmax(ans, dp[i].get(N));
  }
  cout << ans;
}