#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    sort(A.begin(), A.end());

    vector<i64> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + A[i];
    }

    auto solve = [&](int i2, int r) -> i64 {
      int i1 = min((i64) r * K, (i64) i2), i3 = i2 + 1 + r;
      i64 rv = 0;
      rv += (i64) i1 * A[i2];
      rv += ps[i2] - ps[i1];
      rv += (i64) (i3 - i2) * A[i2];
      rv += ps[N] - ps[i3];
      return rv;
    };

    i64 ans = accumulate(A.begin(), A.end(), 0ll);
    for (int i2 = 0; i2 < N; i2++) {
      int l = 0, r = N - i2 - 1;
      while (l < r) {
        int m = l + (r - l) / 2;
        solve(i2, m + 1) < solve(i2, m) ? r = m : l = m + 1;
      }
      ans = max(ans, solve(i2, l));
    }
    cout << ans << '\n';
  }
}
