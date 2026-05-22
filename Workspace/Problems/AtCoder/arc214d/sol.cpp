#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

#include "ethankim8683/combinatorics.hpp"
using namespace ethankim8683;

using mint = modint1000000007;

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

  // stripes?
  //
  // powers along diagonal
  //
  // 0 1 4 12 32
  // 0 2 8 24 64
  // 0 4 16 48 96
  // 0 8 32 64 128
  // 0 16 32 64 128
  //
  // residue classes along diagonal
  // here = 3
  // 0 0 0
  // 1 3 9
  // 2 6 128
  // any path is a string in base 3
  // nvm this fucked
  //
  // i have no idea what this is dawg
  //
  // rip ucsd fallen star 2026

  // binomial encoding
  //
  // if there's a 1 here, add number of codes with 0 here

  int N;
  cin >> N;

  // vc A(N, vi(N));
  // rep(i, 0, N) {
  //   rep(j, 0, N) {
  //     if (i - 1 < 0 or j + 1 >= N) {
  //       A[i][j] = 0;
  //     } else {
  //       // i-1, j chose 1
  //       A[i][j] = A[i - 1][j + 1] +
  //                 binom<mint>(((N - 1) - (i - 1)) + ((N - 1) - (j + 1)),
  //                             (N - 1) - (i - 1))
  //                     .val();
  //     }
  //   }
  // }
  // for (auto r : A) {
  //   for (auto e : r) {
  //     cout << e << ' ';
  //   }
  //   cout << '\n';
  // }

  vc A(N, vi(N, 0)), counts(N, vi(N, 0));
  counts[0][0] = 1;
  rep(i, 0, 2 * N - 1) {
    rep(j, 0, N) {
      int k = i - j;
      if (!(0 <= k and k < N)) continue;
      if (j + 1 < N and k - 1 >= 0) {
        A[j + 1][k - 1] = A[j][k] + counts[j][k - 1];
      }
      if (j + 1 < N) {
        counts[j + 1][k] += counts[j][k];
      }
      if (k + 1 < N) {
        counts[j][k + 1] += counts[j][k];
      }
    }
  }
  for (auto r : A) {
    for (auto e : r) {
      cout << e << ' ';
    }
    cout << '\n';
  }

  // vc dp(N, vc<set<int>>(N));
  // dp[0][0].insert(A[0][0]);
  // rep(i, 0, N) {
  //   rep(j, 0, N) {
  //     for (auto e : dp[i][j]) {
  //       if (i + 1 < N) {
  //         dp[i + 1][j].insert(e + A[i + 1][j]);
  //       }
  //       if (j + 1 < N) {
  //         dp[i][j + 1].insert(e + A[i][j + 1]);
  //       }
  //     }
  //   }
  // }
  // assert(sz(dp[N - 1][N - 1]) == binom<mint>(2 * N - 2, N - 1).val());
  // assert(*dp[N - 1][N - 1].rbegin() <= 6000000);
}
