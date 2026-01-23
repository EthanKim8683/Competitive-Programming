// #pragma GCC optimize("Ofast,unroll-loops")
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

const int SQRTN = 317;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

typedef complex<double> C;
typedef vc<double> vd;
void fft(vc<C> &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vc<complex<long double>> R(2, 1);
  static vc<C> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  typedef double T;
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        C z = rt[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}
vd conv(const vd &a, const vd &b) {
  if (a.empty() || b.empty()) return {};
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
  vc<C> in(n), out(n);
  copy(all(a), begin(in));
  rep(i, 0, sz(b)) in[i].imag(b[i]);
  fft(in);
  for (C &x : in) x *= x;
  rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
  return res;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:07
  // thinking done: 5:23
  // target impl time: 30 min
  // initial impl done: 5:40

  int N, Q;
  cin >> N >> Q;

  vi P(N);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  vi K(Q);
  for (auto &e : K) {
    cin >> e;
  }

  vc small(SQRTN, vi(SQRTN, 0));
  vc<vi> large;
  vc<bool> seen(N, false);
  rep(i, 0, N) {
    if (seen[i]) continue;

    vd A, B;
    for (int j = i; !seen[j]; j = P[j]) {
      A.pb(j + 1);
      B.pb(j + 1);
      seen[j] = true;
    }
    reverse(all(A));
    vd C = conv(A, B);

    vi sums(sz(A), 0);
    rep(j, 0, sz(C)) { sums[(2 * sz(A) - 1 - j) % sz(A)] += round(C[j]); }

    if (sz(A) < SQRTN) {
      rep(i, 0, sz(A)) { small[sz(A)][i] += sums[i]; }
    } else {
      large.pb(sums);
    }
  }

  for (auto e : K) {
    int ans = 0;
    rep(i, 1, SQRTN) { ans += small[i][e % i]; }
    for (auto &r : large) {
      ans += r[e % sz(r)];
    }
    cout << ans << '\n';
  }
}
