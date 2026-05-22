#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int MAXD = 1e7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<int> sieve(MAXD + 1), primes, mu(MAXD + 1);
  iota(sieve.begin(), sieve.end(), 0);
  mu[1] = 1;
  for (int i = 2; i <= MAXD; i++) {
    if (sieve[i] == i) {
      primes.push_back(i);
      mu[i] = -1;
    }
    for (auto e : primes) {
      if (i * e > MAXD) break;
      sieve[i * e] = e;
      if (i % e == 0) {
        mu[i * e] = 0;
        break;
      } else {
        mu[i * e] = mu[i] * mu[e];
      }
    }
  }

  vector<int> ps(MAXD + 2);
  ps[0] = 0;
  for (int i = 0; i <= MAXD; i++) {
    ps[i + 1] = ps[i] + mu[i];
  }

  int T;
  cin >> T;

  for (int t = 1; t <= T; t++) {
    int A, B, C, D, K;
    cin >> A >> B >> C >> D >> K;
    if (B > D) {
      swap(B, D);
    }

    i64 ans = 0;
    for (int i = 1; i <= MAXD;) {
      auto counts = [&](int d) -> pair<int, int> {
        return {B / K / d, D / K / d};
      };

      auto check = [&](int x) -> bool { return counts(x) == counts(i); };
      int l = i, r = MAXD;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        check(m) ? l = m : r = m - 1;
      }

      auto triangle = [&](int n) -> i64 { return n * (n + 1) / 2; };

      auto [n1, n2] = counts(l);
      ans += (triangle(n2) - triangle(n2 - n1)) * (ps[l + 1] - ps[i]);

      i = l + 1;
    }
    cout << "Case " << t << ": " << ans << '\n';
  }
}
