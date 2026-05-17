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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    map<pii, int> by_r;
    rep(i, 0, N) {
      int g = gcd(A[i], B[i]);
      by_r.insert({{A[i] / g, B[i] / g}, i});
    }
    if (sz(by_r) == 1) {
      cout << "No\n";
      continue;
    }

    auto less = [&](pii a, pii b) -> bool { return a.fs * b.sd < b.fs * a.sd; };

    int i1 = by_r.begin()->sd, i2 = by_r.rbegin()->sd;
    if (less({A[i1], B[i1]}, {A[i2], B[i2]})) {
      swap(i1, i2);
    }

    vi X(N, 0);
    X[i1] = A[i2] + B[i2];
    X[i2] = -(A[i1] + B[i1]);

    cout << "Yes\n";
    for (auto e : X) {
      cout << e << ' ';
    }
    cout << '\n';

    // int Asum = 0, Bsum = 0;
    // rep(i, 0, N) {
    //   Asum += A[i] * X[i];
    //   Bsum += B[i] * X[i];
    // }
    // cerr << Asum << ' ' << Bsum << '\n';
    // assert(Asum > 0 and Bsum < 0);
  }
}
