#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int L, N;
  cin >> L >> N;

  string S;
  cin >> S;

  vector<int> C(N);
  for (auto &e : C) cin >> e;

  auto min_plus = [&](const vector<i64> &A,
                      const vector<i64> &B) -> vector<i64> {
    vector<i64> rv(A.size() + B.size() - 1);
    int j = 0, k = 0;
    for (int i = 0; i < rv.size(); i++) {
      rv[i] = A[j] + B[k];
      if (j == A.size()) {
        k++;
      } else if (k == B.size()) {
        j++;
      } else {
        if (A[j + 1] + B[k] < A[j] + B[k + 1]) {
          j++;
        } else {
          k++;
        }
      }
    }
    return rv;
  };

  auto solve = [&](auto self, int l, int r) -> vector<vector<vector<i64>>> {
    vector rv(L, vector(L, vector<i64>((r - l) / L + 1, INF)));
    if (r - l <= 3) {
      vector<int> stack;
      auto dfs = [&](auto self_, int i) -> void {
        if (i == r - l) {
          auto S_ = stack;

          i64 cost = 0;
          for (int j = 0; j < i; j++) {
            cost += (S[l + j] != "MOO"[S_[j]]) * C[l + j];
          }

          int n = 0;
          for (int j = 0; j + L <= i; j++) {
            bool ok = true;
            for (int k = 0; k < L; k++) {
              ok = ok and S_[j + k] == k;
            }
            n += ok;
          }

          if (L == 3) {
            if (S_[0] == 1 and S_[1] != 2) {
              S_[0] = 0;
            }
            if (S_.back() == 1 and S_.end()[-2] != 0) {
              S_.back() = 2;
            }
          }

          int i_ = S_[0], j_ = S_.back();
          rv[i_][j_][n] = min(rv[i_][j_][n], cost);
          return;
        }

        for (int j = 0; j < L; j++) {
          stack.push_back(j);
          self_(self_, i + 1);
          stack.pop_back();
        }
      };
      dfs(dfs, 0);
      return rv;
    }

    int m = l + (r - l) / 2;
    auto A = self(self, l, m);
    auto B = self(self, m, r);

    for (int i = 0; i < L; i++) {
      for (int j = 0; j < L; j++) {
        for (int k = 0; k < L; k++) {
          for (int l = 0; l < L; l++) {
            auto dp = min_plus(A[i][k], B[l][j]);
            for (int m = 0; m < dp.size(); m++) {
              int m_ = m + (k + 1 == l);
              rv[i][j][m_] = min(rv[i][j][m_], dp[m]);
            }
          }
        }
      }
    }
    return rv;
  };
  auto ans = solve(solve, 0, N);

  vector<i64> ans_(N / L + 1, INF);
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < L; j++) {
      for (int k = 0; k < ans[i][j].size(); k++) {
        ans_[k] = min(ans_[k], ans[i][j][k]);
      }
    }
  }
  for (int i = 1; i <= N / L; i++) {
    cout << ans_[i] << '\n';
  }
}
