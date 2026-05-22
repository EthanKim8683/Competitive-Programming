#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto op = [&](pair<i64, int> a, pair<i64, int> b) -> i64 {
      auto [v1, e1] = a;
      auto [v2, e2] = b;
      if (v1 == 1) return v2 > 1 ? INF : 0;
      if (v2 == 1) return 0;
      while (v1 * v1 < v2) {
        v1 *= v1;
        e1++;
      }
      while (v2 <= v1) {
        v2 *= v2;
        e1--;
      }
      return max(e1 + e2 + 1, 0);
    };

    pair<i64, int> p = {A[0], 0};
    i64 ans = 0;
    bool ok = true;
    for (int i = 1; i < N; i++) {
      i64 e = op({A[i], 0}, p);
      if (e == INF) {
        ok = false;
        break;
      }
      ans += e;
      p = {A[i], e};
    }
    cout << (ok ? ans : -1) << '\n';
  }
}
