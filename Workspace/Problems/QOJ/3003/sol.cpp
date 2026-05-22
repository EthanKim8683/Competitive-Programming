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

const int K = 15;
const double LOGP = log2(1e6);
const double INF = 1.L / 0;
const double EPSILON = 1e-4;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

typedef vc<double> vd;
const double eps = 1e-9;
int solveLinear(vc<vd> A, vd b, vd &x, vc<bool> &is_unique) {
  int n = sz(A), m = sz(x), rank = 0, br, bc;
  if (n) assert(sz(A[0]) == m);
  vi col(m);
  iota(all(col), 0);
  rep(i, 0, n) {
    double v, bv = 0;
    rep(r, i, n) rep(c, i, m) if ((v = fabs(A[r][c])) > bv) br = r, bc = c,
                                                            bv = v;
    if (bv <= eps) {
      rep(j, i, n) assert(fabs(b[j]) < eps);
      break;
    }
    swap(A[i], A[br]);
    swap(b[i], b[br]);
    swap(col[i], col[bc]);
    rep(j, 0, n) swap(A[j][i], A[j][bc]);
    bv = 1 / A[i][i];
    rep(j, 0, n) if (j != i) {
      double fac = A[j][i] * bv;
      b[j] -= fac * b[i];
      rep(k, i + 1, m) A[j][k] -= fac * A[i][k];
    }
    rank++;
  }
  fill(all(is_unique), false);
  rep(i, 0, rank) {
    rep(j, rank, m) if (fabs(A[i][j]) > eps) goto fail;
    x[col[i]] = b[i] / A[i][i];
    is_unique[col[i]] = true;
  fail:;
  };
  return rank;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // price(A, x) = price(A, 0) * inflationcdf(x) * modifier(A)^x

  mt19937 rng(time(nullptr));

  int Y, C, Q;
  cin >> Y >> C >> Q;

  vd R(Y - 1);
  for (auto &e : R) cin >> e;

  vc P(Y, vd(C));
  for (auto &r : P) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vc<bool> is_degenerate(C, false);
  rep(i, 0, C) {
    int count = 0;
    rep(j, 0, Y) {
      if (P[j][i] < 0) continue;
      count += 1;
    }
    is_degenerate[i] = count < 2;
  }

  vc<vd> A;
  vd b, x(1 + Y - 1 + C - 1 + C);
  vc<bool> is_unique(1 + Y - 1 + C - 1 + C);
  rep(i, 0, Y - 1) {
    if (R[i] < 0) continue;
    vd Ai(1 + Y - 1 + C - 1 + C, 0);
    Ai[1 + i] = 1;
    double bi = log(R[i]);
    A.pb(Ai);
    b.pb(bi);
  }
  rep(i, 0, C) {
    if (is_degenerate[i]) {
      if (i < C - 1) {
        vd Ai(1 + Y - 1 + C - 1 + C, 0);
        Ai[1 + Y - 1 + i] = 1;
        double bi = 0;
        A.pb(Ai);
        b.pb(bi);
      }
    } else {
      rep(j, 0, Y) {
        if (P[j][i] < 0) continue;
        vd Ai(1 + Y - 1 + C - 1 + C, 0);
        Ai[0] = 1;
        rep(k, 0, j) { Ai[1 + k] = 1; }
        rep(k, 0, i) { Ai[1 + Y - 1 + k] = 1; }
        Ai[1 + Y - 1 + C - 1 + i] = j;
        double bi = log(P[j][i]);
        A.pb(Ai);
        b.pb(bi);
      }
    }
  }

  auto random = [&](double l, double r) -> double {
    return (double) rng() / RAND_MAX * (r - l) + l;
  };

  double nil = NAN;
  auto solve = [&]() -> vc<vd> {
    auto A2 = A;
    auto b2 = b;
    solveLinear(A2, b2, x, is_unique);
    rep(i, 0, 1 + Y - 1 + C - 1) {
      if (is_unique[i]) continue;
      vd Ai(1 + Y - 1 + C - 1 + C, 0);
      Ai[i] = 1;
      double bi = random(0, LOGP);
      A2.pb(Ai);
      b2.pb(bi);
      solveLinear(A2, b2, x, is_unique);
    }

    vc rv(C, vd(Y, nil));
    rep(i, 0, C) {
      rep(j, 0, Y) {
        if (!is_unique[1 + Y - 1 + C - 1 + i]) continue;
        double e = 0;
        e += x[0];
        rep(k, 0, j) { e += x[1 + k]; }
        rep(k, 0, i) { e += x[1 + Y - 1 + k]; }
        e += j * x[1 + Y - 1 + C - 1 + i];
        rv[i][j] = e;
      }
    }
    return rv;
  };
  vc<vc<vd>> trial;
  rep(i, 0, K) { trial.pb(solve()); }

  cout << setprecision(10) << fixed;
  while (Q--) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    if (is_degenerate[a]) {
      cout << P[b][a] << '\n';
      continue;
    }
    bool ok = true;
    double emin = INF;
    rep(i, 0, K) {
      double e = trial[i][a][b];
      ok = ok and !isnan(e);
      ok = ok and e - emin < EPSILON;
      chmin(emin, e);
    }
    if (!ok) {
      cout << "-1.0\n";
      continue;
    }
    cout << exp(emin) << '\n';
  }
}
