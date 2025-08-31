#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    i64 L, R;
    cin >> N >> L >> R;
    L--;

    vector<int> A(N + 1);
    A[0] = 0;
    for (int i = 1; i <= N; i++) {
      cin >> A[i];
    }

    auto is_pow_of_2 = [&](i64 x) -> bool {
      return __builtin_popcountll(x) == 1;
    };

    auto sum_of_px = [&](int px0, i64 ps, i64 n) -> i64 {
      if (ps % 2 == 0) {
        return px0 * n - px0 * ps * 2 + ps;
      } else {
        return px0 * n - px0 * ps * 2
      }
    };
  }
}
