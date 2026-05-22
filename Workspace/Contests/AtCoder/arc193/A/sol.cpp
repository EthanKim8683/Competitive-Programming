#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> W(N);
  for (auto &e : W) cin >> e;

  vector<pair<int, int>> ranges(N);
  for (auto &[l, r] : ranges) {
    cin >> l >> r;
    l--;
  }

  vector<i64> pm(2 * N + 1, INF), sm(2 * N + 1, INF);
  for (int i = 0; i < N; i++) {
    auto [l, r] = ranges[i];
    pm[r] = min(pm[r], (i64) W[i]);
    sm[l] = min(sm[l], (i64) W[i]);
  }
  for (int i = 0; i < 2 * N; i++) {
    pm[i + 1] = min(pm[i + 1], pm[i]);
  }
  for (int i = 2 * N; i > 0; i--) {
    sm[i - 1] = min(sm[i - 1], sm[i]);
  }

  auto best = [&](int l, int r) -> i64 { return min(pm[l], sm[r]); };

  int Q;
  cin >> Q;

  while (Q--) {
    int S, T;
    cin >> S >> T;
    S--, T--;
    if (ranges[S] > ranges[T]) {
      swap(S, T);
    }

    auto [l1, r1] = ranges[S];
    auto [l2, r2] = ranges[T];
    if (r1 <= l2) {
      cout << W[S] + W[T] << '\n';
    } else {
      i64 ans = INF;
      ans = min(ans, W[S] + W[T] + best(l1, max(r1, r2)));
      ans = min(ans, W[S] + W[T] + best(l1, r1) + best(l2, r2));
      cout << (ans == INF ? -1 : ans) << '\n';
    }
  }
}
