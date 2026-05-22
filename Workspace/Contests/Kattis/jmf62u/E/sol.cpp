#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int K, N;
  cin >> K >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<i64> ps(2 * N + 1, 0);
  for (int i = 0; i < 2 * N; i++) {
    ps[i + 1] = ps[i] + A[i % N];
  }

  if (ps[N] % K != 0) {
    cout << "NO";
    exit(0);
  }
  i64 sum = ps[N] / K;

  tuple<int, int, int> best = {INF, -1, -1};
  for (int i = 0; i < N; i++) {
    auto it = lower_bound(ps.begin(), ps.end(), ps[i] + sum);
    if (it == ps.end()) continue;
    if (*it != ps[i] + sum) continue;
    int j = it - ps.begin();
    best = min(best, {j - i, i, j});
  }
  auto [n, l, r] = best;
  if (n == INF) {
    cout << "NO";
    exit(0);
  }

  auto query = [&](int l, int r) -> i64 {
    l %= N;
    r %= N;
    if (r < l) {
      r += N;
    }
    return ps[r] - ps[l];
  };

  for (int i = l; i < r; i++) {
    int i_ = i;
    bool ok = true;
    for (int j = 0; j < K; j++) {
      i_ %= N;
      auto it = lower_bound(ps.begin(), ps.end(), ps[i_] + sum);
      if (it == ps.end()) {
        ok = false;
        break;
      }
      if (*it != ps[i_] + sum) {
        ok = false;
        break;
      }
      i_ = it - ps.begin();
    }
    if (ok) {
      cout << "YES";
      exit(0);
    }
  }
  cout << "NO";
}