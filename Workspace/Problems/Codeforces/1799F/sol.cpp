#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, B, K1, K2;
    cin >> N >> B >> K1 >> K2;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
    sort(A.rbegin(), A.rend());

    auto op1 = [&](int x) -> int { return (x + 1) / 2; };
    auto op2 = [&](int x) -> int { return max(x - B, 0); };

    vector<i64> ps1(N + 1), ps2(N + 1), ps3(N + 1);
    for (int i = 0; i < N; i++) {
      ps1[i + 1] = ps1[i] + op1(A[i]) - A[i];
      ps2[i + 1] = ps2[i] + op2(A[i]) - A[i];
      ps3[i + 1] = ps3[i] + op2(op1(A[i])) - A[i];
    }
    auto query = [&](vector<i64> &ps, int l, int r) -> i64 {
      l = clamp(l, 0, N);
      r = clamp(r, l, N);
      return ps[r] - ps[l];
    };

    i64 sum = accumulate(A.begin(), A.end(), 0ll), ans = INF;
    for (int i = 0; i <= min(K1, K2); i++) {
      for (int j = 0; j <= K1 - i; j++) {
        int i1 = 0, i2 = i1 + i, i3 = i2 + j, i4 = i3 + K2 - i,
            i5 = i4 + K1 - i - j;
        ans = min(ans, sum + query(ps3, i1, i2) + query(ps1, i2, i3) +
                           query(ps2, i3, i4) + query(ps1, i4, i5));
      }
    }
    cout << ans << '\n';
  }
}
