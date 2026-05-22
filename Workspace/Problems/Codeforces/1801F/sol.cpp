#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  f64 ans_ = 0;
  auto dfs = [&](auto self, int i, f64 v, f64 k) -> void {
    if (i == N) {
      if (k >= K) {
        ans_ = max(ans_, v);
      }
      return;
    }
    for (int b = 1; b <= A[i]; b++) {
      self(self, i + 1, v * (A[i] / b) / A[i], k * b);
    }
  };
  dfs(dfs, 0, K, 1);
  cerr << setprecision(10) << fixed << ans_ << '\n';

  // If we log the problem, we get:
  // 1. sum(log(B[i])) >= log(K)
  // 2. Maximize sum(log(floor(A[i]/B[i])) - log(A[i])) + log(K)
  //
  // We can increment B[i], choosing i such that the ratio of quantity 2 lost
  // versus quantity 1 gained is minimal.

  vector<int> B(N, 1);
  auto next = [&](int a, int b) -> int {
    int l = b + 1, r = a;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      a / m == a / (b + 1) ? l = m : r = m - 1;
    }
    return l;
  };
  auto delta = [&](int a, int b) -> pair<f64, f64> {
    return {logl(b), logl(a / b) - logl(a)};
  };
  priority_queue<tuple<f64, int, int>> pq;
  f64 q1 = 0, q2 = logl(K);
  multiset<tuple<f64, f64, int>> rest;
  auto set = [&](int i, int b) -> void {
    auto [dq1, dq2] = delta(A[i], B[i]);
    auto [dq1_, dq2_] = delta(A[i], b);
    q1 += dq1_ - dq1;
    q2 += dq2_ - dq2;
    tuple<f64, f64, int> key = {dq1_ - dq1, dq2_ - dq2, i};
    if (rest.contains(key)) {
      rest.erase(key);
    }
    B[i] = b;
    int b_ = next(A[i], b);
    if (b_ <= A[i]) {
      auto [dq1, dq2] = delta(A[i], b);
      auto [dq1_, dq2_] = delta(A[i], b_);
      pq.push({dq2_ / dq1_, i, b_});
      rest.insert({dq1_ - dq1, dq2_ - dq2, i});
    }
  };
  for (int i = 0; i < N; i++) {
    auto [dq1, dq2] = delta(A[i], B[i]);
    q1 += dq1;
    q2 += dq2;
    set(i, 1);
  }
  f64 ans = 0;
  auto check = [&]() -> void {
    while (rest.size() > 0) {
      auto [dq1, dq2, i] = *prev(rest.end());
      if (q1 + dq1 < logl(K)) break;
      ans = max(ans, expl(q2 + dq2));
      rest.erase(prev(rest.end()));
    }
  };
  check();
  while (pq.size() > 0 and q1 < logl(K)) {
    auto [w, i, b] = pq.top();
    pq.pop();
    set(i, b);
    check();
  }
  cout << setprecision(10) << fixed << ans;
}
