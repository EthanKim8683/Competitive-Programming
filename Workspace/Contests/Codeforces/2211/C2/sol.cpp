#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/dsu.hpp"
using namespace atcoder;

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

  // if it differs from K ago, B K ago must've been the old one and B now must
  // be the new one
  //
  // if it remains the same, replace what was lost
  //
  // is this it?
  // probably

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    dsu d(2 * N);
    rep(i, K, N) {
      if (A[i] != A[i - K]) {
        d.merge(i - K, N + i - K);
        d.merge(i, N + i);
      } else {
        d.merge(N + i - K, N + i);
      }
    }
    bool ok = true;
    vi values(2 * N, -1);
    auto assign = [&](int i, int x) -> void {
      if (values[i] != -1) {
        ok = ok and values[i] == x;
        return;
      }
      values[i] = x;
    };
    rep(i, 0, N) {
      assign(d.leader(i), A[i]);
      if (B[i] != -1) {
        assign(d.leader(N + i), B[i]);
      }
    }
    if (!ok) {
      cout << "NO\n";
      continue;
    }
    map<int, int> counts1, counts2;
    rep(i, 0, K) {
      counts1[values[d.leader(i)]] += 1;
      int x = values[d.leader(N + i)];
      if (x != -1) {
        counts2[x] += 1;
      }
    }
    for (auto [k, v] : counts2) {
      ok = ok and v <= counts1[k];
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
