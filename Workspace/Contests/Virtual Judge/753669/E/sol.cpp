#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, D;
    cin >> N >> D;

    vector<int> C(N);
    for (auto &e : C) cin >> e;

    auto isqrt = [&](i64 x) -> int {
      int l = 0, r = 1e9;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        (i64) m *m <= x ? l = m : r = m - 1;
      }
      return l;
    };

    auto floor_div = [&](i64 a, i64 b) -> i64 {
      if (a < 0) {
        return a / b - (a % b != 0);
      } else {
        return a / b;
      }
    };

    auto overestimate = [&](i64 x) -> bool {
      i64 width = 0;
      for (int i = 0; i < N; i++) {
        // C[i] * (2 * (length[i] - 1) + 1) <= x
        // 2 * (length[i] - 1) + 1 <= x / C[i]
        // length[i] - 1 <= (x / C[i] - 1) / 2
        // length[i] <= (x / C[i] - 1) / 2 + 1
        i64 length = floor_div((x / C[i] - 1), 2) + 1;
        width += length;
      }
      return width >= D;
    };

    i64 l = 1, r = 1e12;
    while (l < r) {
      i64 m = l + (r - l) / 2;
      overestimate(m) ? r = m : l = m + 1;
    }
    i64 x = l - 1;

    vector<int> length(N, 0);
    int width = 0;
    i64 ans = 0;
    for (int i = 0; i < N; i++) {
      length[i] = floor_div((x / C[i] - 1), 2) + 1;
      width += length[i];
      ans += (i64) C[i] * length[i] * length[i];
    }

    priority_queue<pair<i64, int>> pq;
    auto push = [&](int i) -> void {
      pq.push({(i64) -C[i] * (2 * length[i] + 1), i});
    };
    for (int i = 0; i < N; i++) {
      push(i);
    }
    while (width < D) {
      auto [cost, i] = pq.top();
      pq.pop();
      ans += -cost;
      width++;
      length[i]++;
      push(i);
    }
    cout << ans << '\n';
  }
}