#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int MAXN = 1e7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<int> sieve(MAXN + 1), primes;
  vector<i64> f(MAXN + 1);
  iota(sieve.begin(), sieve.end(), 0);
  f[1] = 1;
  for (int i = 2; i <= MAXN; i++) {
    if (sieve[i] == i) {
      primes.push_back(i);
      f[i] = 1 - i + (i64) i * i;
    }
    for (auto e : primes) {
      if (i * e > MAXN) break;
      sieve[i * e] = e;
      if (i % e == 0) {
        f[i * e] = f[i] + (f[i] - f[i / e]) * e * e;
        break;
      } else {
        f[i * e] = f[i] * f[e];
      }
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    cout << f[N] << '\n';
  }
}
