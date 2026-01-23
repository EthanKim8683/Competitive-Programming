#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1e5;
const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> D(N);
  for (auto &e : D) cin >> e;

  vector<pair<char, int>> queries(M);
  for (auto &[c, v] : queries) {
    cin >> c >> v;
  }

  vector<bool> ok(MAXV + 1, false);
  for (auto e : D) {
    ok[e] = true;
  }
  for (auto [c, v] : queries) {
    if (c != 'X') continue;
    ok[v] = false;
  }

  auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

  vector<int> dp(MAXV + 1, INF);
  dp[0] = 0;
  for (int i = 1; i <= MAXV; i++) {
    if (!ok[i]) continue;
    for (int j = 0; j + i <= MAXV; j++) {
      chmin(dp[j + i], dp[j] + 1);
    }
  }

  vector<int> ans(M);
  for (int i = M - 1; i >= 0; i--) {
    auto [c, v] = queries[i];
    if (c == 'X') {
      for (int j = 0; j + v <= MAXV; j++) {
        chmin(dp[j + v], dp[j] + 1);
      }
    } else {
      ans[i] = dp[v];
    }
  }

  for (int i = 0; i < M; i++) {
    auto [c, v] = queries[i];
    if (c != 'Q') continue;
    cout << (ans[i] == INF ? -1 : ans[i]) << '\n';
  }
}