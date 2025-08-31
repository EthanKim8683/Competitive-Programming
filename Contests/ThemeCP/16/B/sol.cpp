#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> A(N);
    int N_ = 0;
    for (auto &r : A) {
      int l;
      cin >> l;
      r.resize(l);
      for (auto &e : r) {
        cin >> e;
      }
      sort(r.begin(), r.end());
      r.erase(unique(r.begin(), r.end()), r.end());
      N_ += r.size();
    }

    vector<vector<int>> adj(N_ + 2);
    vector<int> odeg(N_ + 2, 0);
    for (int i = 0; i < N; i++) {
      int mex = 0, a = -1, b = -1;
      for (int j = 0; j < A[i].size();) {
        if (A[i][j] == mex) {
          mex++;
          j++;
        } else {
          if (a == -1) {
            a = mex;
            mex++;
          } else {
            break;
          }
        }
      }
      if (a == -1) {
        a = mex;
        b = mex + 1;
      } else {
        b = mex;
      }
      adj[b].push_back(a);
      odeg[a]++;
    }

    vector<int> dp(N_ + 2);
    iota(dp.begin(), dp.end(), 0);
    int pm = 0;
    for (int i = N_ + 1; i >= 0; i--) {
      dp[i] = max(dp[i], pm);

      for (auto j : adj[i]) {
        dp[j] = max(dp[j], dp[i]);
      }

      if (odeg[i] >= 1) {
        pm = max(pm, i);
      }
      if (odeg[i] >= 2) {
        pm = max(pm, dp[i]);
      }
    }
    pm = 0;
    for (int i = 0; i <= N_ + 1; i++) {
      dp[i] = max(dp[i], pm);

      if (odeg[i] >= 2) {
        pm = max(pm, dp[i]);
      }
    }

    int M_ = min(N_ + 1, M);
    i64 ans = 0;
    for (int i = 0; i <= M_; i++) {
      ans += dp[i];
    }
    ans += (i64) (M - M_) * (M_ + 1 + M) / 2;
    cout << ans << '\n';
  }
}
