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
typedef vc<int> vi;

const int MOD = 1e9 + 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:34
  // thinking done: 5:39
  // target impl time: 25 min
  // initial impl done: 5:57

  // it's just matrix exponentiation?

  int N, P, S, C;
  cin >> N >> P >> S >> C;

  vc<tuple<int, char, int, int, int>> problems(P);
  for (auto &[t, g, s, c, b] : problems) {
    cin >> t >> g >> s >> c >> b;
  }

  auto prod = [&](vc<vi> A, vc<vi> B) -> vc<vi> {
    vc rv(sz(A), vi(sz(B[0]), 0));
    rep(i, 0, sz(A)) {
      rep(j, 0, sz(B[0])) {
        rep(k, 0, sz(A[0])) { (rv[i][j] += A[i][k] * B[k][j]) %= MOD; }
      }
    }
    return rv;
  };
  auto pow = [&](vc<vi> X, int y) -> vc<vi> {
    vc rv(sz(X), vi(sz(X), 0));
    rep(i, 0, sz(X)) { rv[i][i] = 1; }
    for (; y; y >>= 1, X = prod(X, X)) {
      if (y & 1) {
        rv = prod(rv, X);
      }
    }
    return rv;
  };

  auto encode = [&](int s, int c) -> int { return s * (C + 1) + c; };

  vi x((S + 1) * (C + 1), 0);
  x[encode(S, C)] = 1;

  vc A1(S + 1, vi(S + 1, 0)), A2(C + 1, vi(C + 1, 0));
  rep(i, 0, S + 1) {
    if (i - 1 >= 0) {
      A1[i][i - 1] += i;
    }
    A1[i][i] += 1;
    if (i + 1 <= S) {
      A1[i][i + 1] += S - i;
    }
  }
  rep(i, 0, C + 1) {
    if (i - 1 >= 0) {
      A2[i][i - 1] += i;
    }
    A2[i][i] += 1;
    if (i + 1 <= C) {
      A2[i][i + 1] += C - i;
    }
  }

  auto transition = [&](vi x, int dt) -> vi {
    auto A3 = pow(A1, dt), A4 = pow(A2, dt);
    vi rv((S + 1) * (C + 1), 0);
    rep(i, 0, S + 1) {
      rep(j, 0, C + 1) {
        rep(k, 0, S + 1) {
          rep(l, 0, C + 1) {
            (rv[encode(k, l)] += x[encode(i, j)] * A3[i][k] % MOD * A4[j][l]) %=
                MOD;
          }
        }
      }
    }
    return rv;
  };

  int t0 = 1;
  for (auto [t, g, s, c, b] : problems) {
    x = transition(x, t - t0);

    rep(i, 0, S + 1) {
      rep(j, 0, C + 1) {
        int s2 = i, c2 = j;
        if (g == 'B') {
          s2 = S - i;
          c2 = C - j;
        }

        if (s2 < s or c2 < c or s2 + c2 < b) {
          x[encode(i, j)] = 0;
        }
      }
    }

    t0 = t;
  }
  x = transition(x, N - t0);
  cout << x[encode(S, C)] << '\n';
}
