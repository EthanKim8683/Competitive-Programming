#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<i64> A(N);
  for (auto &e : A) cin >> e;

  map<i64, int> inv_A;
  for (int i = 0; i < N; i++) {
    inv_A[A[i]] = i;
  }

  vector<int> P(N), inv_P(N);
  iota(P.begin(), P.end(), 0);
  iota(inv_P.begin(), inv_P.end(), 0);
  auto dfs = [&](auto self, vector<int> S, int i) -> void {
    if (S.size() <= 1) return;

    vector<vector<int>> parts(2);
    for (auto e : S) {
      parts[A[e] >> i & 1].push_back(e);
    }

    self(self, parts[0], i + 1);
    self(self, parts[1], i + 1);
    for (auto e : parts[1]) {
      int j = inv_P[inv_A[A[P[e]] ^ 1ll << i]];
      swap(P[e], P[j]);
      swap(inv_P[P[j]], inv_P[P[e]]);
    }
  };
  vector<int> S(N);
  iota(S.begin(), S.end(), 0);
  dfs(dfs, S, 0);
  for (auto e : P) {
    cout << A[e] << '\n';
  }
}
