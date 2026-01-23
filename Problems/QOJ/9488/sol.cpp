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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, K;
  cin >> N >> M >> K;

  vc<pii> edges(M);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  vc A(2 * N, vi(2 * N, 0));
  for (auto [u, v] : edges) {
    A[u][v] = A[v][u] = 1;
  }
  rep(i, 0, N) {
    rep(j, 0, N) { (A[i][N + i] += A[i][j]) %= MOD; }
    (A[i][N + i] += MOD - 1) %= MOD;
    A[N + i][i] = MOD - 1;
  }

  auto prod = [&](vc<vi> A, vc<vi> B) -> vc<vi> {
    assert(sz(A[0]) == sz(B));
    vc rv(sz(A), vi(sz(B[0]), 0));
    rep(i, 0, sz(A)) {
      rep(j, 0, sz(B[0])) {
        rep(k, 0, sz(B)) { (rv[i][j] += A[i][k] * B[k][j]) %= MOD; }
      }
    }
    return rv;
  };

  auto pow = [&](vc<vi> X, int y) -> vc<vi> {
    assert(sz(X) == sz(X[0]));
    vc rv(sz(X), vi(sz(X), 0));
    rep(i, 0, sz(X)) { rv[i][i] = 1; }
    for (; y; y >>= 1, X = prod(X, X)) {
      if (y & 1) {
        rv = prod(rv, X);
      }
    }
    return rv;
  };

  vc X(1, vi(2 * N, 0));
  rep(i, 0, N) { X[0][i] = A[0][i]; }
  rep(i, 0, N) { (X[0][N] += A[0][i]) %= MOD; }
  cout << prod(X, pow(A, K - 1))[0][N - 1] << '\n';
}
