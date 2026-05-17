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

const int N = 3;
const int M = 10;
const int K = 3;
const string CIRCLES = "ogrc";

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // load up what to give to next circle
  //
  // need to get groups of 3
  //
  // can swap in 5 ops
  //
  // can we solve in at most 48 swaps?
  //
  // counts per circle
  //
  // 10 swaps for first circle
  //
  // 10 swaps for remaining two circles
  //
  // move first bead to to position 1 in first circle
  //
  // move second bead to to position 4 in second circle
  //
  // rotate first bead to second circle
  //
  // move second circle once counter-clockwise
  //
  // rotate second bead to first circle

  vc<string> circles(N);
  for (auto &r : circles) {
    cin >> r;
    for (auto &e : r) {
      e = find(all(CIRCLES), e) - CIRCLES.begin();
    }
  }

  vc<pii> ans;
  auto op = [&](int i, int n) -> void {
    if (i == N) {
      n = (n % N + N) % N;
      if (n == 0) return;
      rep(j, 0, n) {
        rep(k, 0, N - 1) {
          rep(l, 0, K) { swap(circles[k][l], circles[k + 1][l]); }
        }
      }
    } else {
      n = (n % M + M) % M;
      if (n == 0) return;
      rep(j, 0, n) {
        for (int k = M - 2; k >= 0; k--) {
          swap(circles[i][k], circles[i][k + 1]);
        }
      }
    }
    ans.eb(i, n);
  };

  auto swap = [&](int i1, int j1, int i2, int j2) -> void {
    op(i1, -j1);
    op(i2, K - j2);
    op(N, i1 - i2);
    op(i2, -1);
    op(N, i2 - i1);
  };

  rep(i1, 0, N - 1) {
    while (true) {
      int j1 = -1;
      rep(i, 0, M) {
        if (circles[i1][i] == i1) continue;
        j1 = i;
      }
      if (j1 == -1) break;

      rep(i2, i1 + 1, N) {
        auto it = find(all(circles[i2]), i1);
        if (it == circles[i2].end()) continue;
        int j2 = it - circles[i2].begin();

        swap(i1, j1, i2, j2);
      }
    }
  }

  cout << sz(ans) << '\n';
  for (auto [i, n] : ans) {
    cout << CIRCLES[i] << n << '\n';
  }
}
