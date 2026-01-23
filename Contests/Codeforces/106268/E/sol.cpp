#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using i128 = __int128;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int A, B, C;
    cin >> A >> B >> C;

    int K;
    cin >> K;

    auto less = [&](pair<i64, i64> a, pair<i64, i64> b) -> bool {
      auto [n1, d1] = a;
      auto [n2, d2] = b;
      return n1 * d2 < n2 * d1;
    };
    auto chmax = [&](pair<i64, i64> &a, pair<i64, i64> b) -> void {
      if (less(a, b)) {
        a = b;
      }
    };
    auto solve = [&](i64 d) -> pair<i64, i64> {
      auto check = [&](i64 x) -> bool {
        auto sign = [&](i64 x) -> int { return (x > 0) - (x < 0); };
        i128 a = (i128) A * x / d, b = (i128) B * x / d, c = (i128) C * x / d;
        if (a == 0 or b == 0 or c == 0) return false;
        return a >= K or b >= K or c >= K or a * b >= K or a * c >= K or
               b * c >= K or a * b * c >= K;
      };
      i64 l = 1, r = K * d;
      while (l < r) {
        i64 m = l + (r - l) / 2;
        check(m) ? r = m : l = m + 1;
      }
      return {d, l};
    };
    pair<i64, i64> ans = {0, 1};
    chmax(ans, solve(A));
    chmax(ans, solve(B));
    chmax(ans, solve(C));
    auto [p, q] = ans;
    i64 g = gcd(p, q);
    p /= g;
    q /= g;
    cout << p << ' ' << q << '\n';
  }
}
