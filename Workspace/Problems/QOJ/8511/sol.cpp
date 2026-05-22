#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

const int MAXN = 1e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:04
  // thinking done: 5:20
  // target impl time:
  // initial impl time:

  // for each i, try all multiples j
  // let k be the product of all prime powers of i that don't appear in j / i
  // j / k * l for all divisors l of k

  int N;
  cin >> N;

  vi W(N + 1);
  rep(i, 1, N + 1) { cin >> W[i]; }

  vi sieve(N + 1);
  iota(all(sieve), 0);
  for (int i = 2; i * i <= N; i++) {
    if (sieve[i] != i) continue;
    for (int j = i * i; j <= N; j += i) {
      sieve[j] = min(sieve[j], i);
    }
  }

  int Wsum = accumulate(all(W), 0ll);
  vc<vi> divisors(N + 1);
  vc<vc<double>> P(N + 1);
  rep(i, 1, N + 1) {
    for (int j = i; j <= N; j += i) {
      divisors[j].pb(i);
    }

    P[i].resize(N / i + 1, 0);
    for (int j = 1; i * j <= N; j++) {
      for (auto k : divisors[i]) {
        P[i][j] += W[j * k];
      }
      P[i][j] /= Wsum;
    }
  }

  vc<pair<double, double>> dp(N + 1, {0, 0});
  dp[1] = {0, 1};
  double ans = 0;
  rep(i, 1, N + 1) {
    auto [sum, count] = dp[i];

    double f = 1 - P[i][1], c = P[i][1] / (1 - P[i][1]), rest = 1;
    for (int j = 2 * i; j <= N; j += i) {
      int k = i;
      for (int l = j / i; l != 1; l /= sieve[l]) {
        while (k % sieve[l] == 0) {
          k /= sieve[l];
        }
      }

      double p = P[k][j / k] / f;
      dp[j].fs += (sum + (c + 1) * count) * p;
      dp[j].sd += count * p;
      rest -= p;
    }
    ans += (sum + c * count) * rest;
  }
  cout << setprecision(10) << fixed << ans << '\n';
}
