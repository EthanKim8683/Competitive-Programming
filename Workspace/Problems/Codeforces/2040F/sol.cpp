#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int MAXD = 3e6;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<bool> is_prime(MAXD + 1, true);
  vector<int> primes, mu(MAXD + 1);
  mu[1] = 1;
  for (int i = 2; i <= MAXD; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      mu[i] = -1;
    }

    for (auto e : primes) {
      if (i * e > MAXD) break;
      is_prime[i * e] = false;

      if (i % e == 0) {
        mu[i * e] = 0;
        break;
      } else {
        mu[i * e] = mu[i] * mu[e];
      }
    }
  }

  vector<int> sieve(MAXD + 1);
  iota(sieve.begin(), sieve.end(), 0);
  for (int i = 2; i * i <= MAXD; i++) {
    if (sieve[i] != i) continue;
    for (int j = i * i; j <= MAXD; j += i) {
      sieve[j] = min(sieve[j], i);
    }
  }

  vector<mint> sum(MAXD + 1, 0);
  for (int i = 1; i <= MAXD; i++) {
    mint contribution = (mint) mu[i] / i;
    for (int j = i; j <= MAXD; j += i) {
      sum[j] += contribution;
    }
    sum[i] *= i;
  }

  vector<mint> counts(MAXD + 1);

  int T;
  cin >> T;

  while (T--) {
    int A, B, C, K;
    cin >> A >> B >> C >> K;

    vector<int> D(K);
    for (auto &e : D) cin >> e;

    int d = 0;
    for (auto e : D) {
      d = gcd(d, e);
    }

    auto divisors = [&](int x) -> vector<int> {
      vector<pair<int, int>> primes;
      for (int i = x; i > 1; i /= sieve[i]) {
        if (primes.empty() or primes.back().first != sieve[i]) {
          primes.emplace_back(sieve[i], 0);
        }
        primes.back().second++;
      }

      vector<int> rv;
      auto dfs = [&](auto self, int i, int d) -> void {
        if (i == primes.size()) {
          rv.push_back(d);
          return;
        }

        auto [p, count] = primes[i];
        for (int j = 0; j <= count; j++) {
          self(self, i + 1, d);
          d *= p;
        }
      };
      dfs(dfs, 0, 1);
      return rv;
    };

    for (auto n : divisors(d)) {
      counts[n] = fact<mint>(A * B * C / n);
      for (auto e : D) {
        counts[n] /= fact<mint>(e / n);
      }
    }

    auto divisors1 = divisors(A), divisors2 = divisors(B),
         divisors3 = divisors(C);
    mint ans = 0;
    for (auto a : divisors1) {
      for (auto b : divisors2) {
        for (auto c : divisors3) {
          int n = lcm(a, lcm(b, c));
          if (d % n != 0) continue;
          ans += sum[a] * sum[b] * sum[c] * counts[n];
        }
      }
    }
    ans /= A * B * C;
    cout << ans.val() << '\n';
  }
}
