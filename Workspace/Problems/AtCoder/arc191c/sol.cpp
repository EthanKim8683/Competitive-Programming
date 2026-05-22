#include <bits/stdc++.h>

#include "ethankim8683/algebra.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    i64 M;
    for (M = N + 1; M <= (i64) 1e18 and !is_prime(M); M += N);
    i64 k = (M - 1) / N, A = mod_pow(primitive_root(M), k, M);
    cout << A << ' ' << M << '\n';
  }
}
/*
A^n - 1 = 0 \mod M
A^n = 1 \mod M
Assume M is prime
r^{kn} = r^0 \mod M
kn = 0 \mod M - 1
n = (M - 1) / gcd(k, M - 1)
n must be a factor of M - 1

Solve now, prove later ;)
*/
