#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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
typedef vector<int> vi;

const int MOD = 998244353;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, K;
  cin >> N >> K;

  vi P(N);
  for (auto &e : P) cin >> e;

  vi S(N);
  for (auto &e : S) cin >> e;

  if (K == 1) {
    cout << "0\n";
    exit(0);
  }

  vc<pii> athletes(N);
  for (int i = 0; i < N; i++) {
    athletes[i] = {P[i], S[i]};
  }
  sort(all(athletes), [&](pii a, pii b) -> bool {
    auto key = [&](pii x) -> pii { return {x.fs, -x.sd}; };
    return key(a) < key(b);
  });

  vi fact(N + 1);
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = fact[i - 1] * i % MOD;
  }

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
      if (y & 1) {
        (rv *= x) %= MOD;
      }
    }
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  auto binom = [&](int n, int k) -> int {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return fact[n] * mod_inv(fact[k] * fact[n - k]) % MOD;
  };

  int ans = 0;
  rep(i, 0, N) {
    int count = 0;
    for (int j = i - 1; j >= 0; j--) {
      auto [p1, s1] = athletes[i];
      auto [p2, s2] = athletes[j];
      if (p2 <= p1 and s2 >= s1) {
        (ans += binom(count + j, K - 2)) %= MOD;
      } else if (s2 <= s1) {
        count++;
      }
    }
  }
  cout << ans << '\n';
}
