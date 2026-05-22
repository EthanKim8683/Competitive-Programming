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

  int N, Q;
  cin >> N >> Q;

  vc<pii> ops(Q);
  for (auto &[i, x] : ops) {
    cin >> i >> x;
    i--;
  }

  vi deltas(N, 0), min_deltas(N, 0);
  for (auto [i, x] : ops) {
    deltas[i] += x;
    chmin(min_deltas[i], deltas[i]);
    deltas[i + 1] -= x;
    chmin(min_deltas[i + 1], deltas[i + 1]);
  }

  vi A(N);
  int e = 0;
  rep(i, 0, N) {
    e += -min_deltas[i] + 1;
    A[i] = e;
  }
  cout << accumulate(all(A), 0ll) << '\n';
}
