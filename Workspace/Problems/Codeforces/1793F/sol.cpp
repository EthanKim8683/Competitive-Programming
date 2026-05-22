#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;
  int K = 2000;

  vector<int> A(N);
  for (auto &e : A) cin >> e, e--;

  vector<pair<int, int>> queries(Q);
  for (auto &[l, r] : queries) {
    cin >> l >> r;
    l--;
  }

  vector<vector<int>> by_r(N + 1);
  for (int i = 0; i < Q; i++) {
    by_r[queries[i].second].push_back(i);
  }
  for (int i = 0; i <= N; i++) {
    by_r[i].shrink_to_fit();
    sort(by_r[i].begin(), by_r[i].end(),
         [&](auto a, auto b) { return queries[a].first > queries[b].first; });
  }

  vector<int> index(N);
  for (int i = 0; i < N; i++) {
    index[A[i]] = i;
  }

  vector<int> ans(Q, N);
  for (int i = 1; i <= N / K; i++) {
    int kmax = -1;
    for (int j = 0; j <= N; j++) {
      while (by_r[j].size() > 0) {
        if (queries[by_r[j].back()].first <= kmax) {
          ans[by_r[j].back()] = i;
          by_r[j].pop_back();
        } else {
          break;
        }
      }

      if (j < N) {
        int k;
        if (A[j] - i >= 0 and (k = index[A[j] - i]) < j) {
          kmax = max(kmax, k);
        }
        if (A[j] + i < N and (k = index[A[j] + i]) < j) {
          kmax = max(kmax, k);
        }
      }
    }
  }

  vector<int> dp(N, N);
  for (int i = 1; i <= N; i++) {
    int pm = N;
    for (int j = 1; j < K and i - 1 - j >= 0; j++) {
      pm = min(pm, abs(A[i - 1] - A[i - 1 - j]));
      dp[i - 1 - j] = min(dp[i - 1 - j], pm);
    }

    for (auto j : by_r[i]) {
      ans[j] = dp[queries[j].first];
    }
  }

  for (auto e : ans) {
    cout << e << '\n';
  }
}
