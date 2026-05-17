#ifndef U
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
typedef vc<int> vi;

const int MAXA = 10000;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // 3 3
  // 13

  // 2 3, 3 3
  // 2 2 3, 13

  // 2 3, 2 3 3
  // 2 2 3, 13

  // make up for the missing stuff before the comma
  // fix the greatest prime each time

  vi sieve(MAXA + 1);
  iota(all(sieve), 0);
  for (int i = 2; i * i <= MAXA; i++) {
    if (sieve[i] != i) continue;
    for (int j = i * i; j <= MAXA; j += i) {
      chmin(sieve[j], i);
    }
  }

  int A, B;
  cin >> A >> B;

  auto factorize = [&](int x) -> vi {
    vi rv;
    for (int i = x; i > 1; i /= sieve[i]) {
      rv.pb(sieve[i]);
    }
    return rv;
  };

  vi delta(MAXA + 1, 0);
  for (auto e : factorize(A)) {
    delta[e] -= 1;
  }
  for (auto e : factorize(B)) {
    delta[e] += 1;
  }

  auto sign = [&](int x) -> int { return (x > 0) - (x < 0); };

  auto encode = [&](int d) -> int { return d == 1 ? 0 : 1; };

  vc seen(2, vc<char>(MAXA + 1, false));
  auto insert = [&](int p, int d) -> void {
    if (seen[encode(d)][p]) {
      delta[p] += d;
    } else {
      seen[encode(d)][p] = true;
      for (auto e : factorize(p - 1)) {
        delta[e] += d;
      }
    }
  };

  vi ans(2, 1);
  for (int i = MAXA; i >= 2; i--) {
    if (sieve[i] != i) continue;
    if (delta[i] == 0) continue;
    int d = sign(delta[i]);
    if (delta[i] % 2 == 0) {
      ans[encode(d)] *= i;
      insert(i, d);
      insert(i, d);
    }
    while (delta[i] != 0) {
      ans[encode(-d)] *= i;
      insert(i, -d);
      insert(i, -d);
    }
  }
  cout << ans[0] << ' ' << ans[1] << '\n';
}
