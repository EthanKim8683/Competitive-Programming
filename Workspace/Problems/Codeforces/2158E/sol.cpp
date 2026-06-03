#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "ethankim8683/data_structures.hpp"
using namespace ethankim8683;

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

  // merge adjacent equal cells
  //
  // number of holes = number of components with no lesser adjacent components
  //
  // offline connectivity

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc A(N, vi(M));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    int Q;
    cin >> Q;

    while (Q--) {
      int r, c, x;
      cin >> r >> c >> x;
      r--, c--;
    }

    dsu_with_rollbacks d(N * M);
  }
}
