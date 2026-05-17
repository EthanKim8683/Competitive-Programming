#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/matrix.hpp"
using namespace ethankim8683;

using mint = modint998244353;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // 2 3 5 7 11 13
  //
  // for each X, count divisors individually
  //
  // first k of a prime factor of X is in divisor
  //
  // try various k
  //
  // 2^6
  //
  // matrix exponentiaion

  int N, M;
  cin >> N >> M;

  vi primes = {2, 3, 5, 7, 11, 13};
  vc A((1 << sz(primes)) + 1, vc<mint>((1 << sz(primes)) + 1, 0));
  rep(i, 0, 1 << sz(primes)) {
    rep(j, 0, 1 << sz(primes)) {
      if ((i & j) != i) continue;
      int sum = 0;
      rep(k, 1, M + 1) {
        int prod = 1;
        rep(l, 0, sz(primes)) {
          if (!((i >> l & 1) == 0 and (j >> l & 1) == 1)) continue;
          int count = 0;
          for (int m = k; m % primes[l] == 0; m /= primes[l]) {
            count += 1;
          }
          prod *= count;
        }
        sum += prod;
      }
      A[j][i] = sum;
      A[1 << sz(primes)][i] += sum;
    }
  }
  A[1 << sz(primes)][1 << sz(primes)] = 1;
  vc b((1 << sz(primes)) + 1, vc<mint>(1, 0));
  b[0][0] = 1;
  cout << matmul(pow(A, N), b)[1 << sz(primes)][0].val() << '\n';
}
