#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  i64 N;
  int P, K;
  cin >> N >> P >> K;

  // I had to look at the editorial for this one--and good thing I did! I
  // learned about Gaussian binomial coefficients from Endagorion's solution.
  //
  // Notably, I actually ran into this function during my initial attempt: I
  // wrote a simple DP to find the number of length N non-decreasing sequences
  // with maximum value K for each sequence sum.
  //
  // In the output of the DP below, the groups are by N, rows by K and columns
  // by sum (starting with K). If we match up the numbers with the Wikipedia
  // page for Gaussian binomial coefficients, we'll see that the coefficient of
  // the ith term of \dbinom{N-1+K}{K}_q seems to correspond to the mumber of
  // ways to form length N non-decreasing sequences with maximum value K and
  // sequence sum K+i (zero-indexed).
  //
  // So applying this to the problem, we basically want to evaluate, for each r,
  // \dbinom{n}{k}_q, where n = N-1, k = r, q = P, which we then multiply by
  // P^N-P^i for each i = 0..r-1, to give us our answer for r.
  //
  // Looking at the formula for the coefficients, it looks like we can keep a
  // running value for \dbinom{n}{k}_q and the rest follows pretty naturally.
  // According to the editorial, we should define 0^{-1} = 0. They leave it to
  // the reader to figure out why this works, but I'm lazy so maybe next time.

  // int N_ = 10;
  // vector dp(N_ + 1, vector(N_ + 1, vector<i64>(N_ * N_ + 1, 0)));
  // dp[0][0][0] = 1;
  // for (int i = 0; i <= N_; i++) {
  //   for (int j = 0; j <= N_; j++) {
  //     for (int k = j; k <= i * j; k++) {
  //       cerr << dp[i][j][k] << ' ';
  //     }
  //     cerr << '\n';
  //   }
  //   if (i + 1 <= N_) {
  //     for (int j = 0; j <= N_; j++) {
  //       for (int k = 0; k <= i * j; k++) {
  //         dp[i + 1][j][k + j] += dp[i][j][k];
  //         if (j + 1 <= N_) {
  //           dp[i][j + 1][k] += dp[i][j][k];
  //         }
  //       }
  //     }
  //   }
  // }

  // auto gbc = [&](int n, int k, int q) -> mint {
  //   if (k > n) return 0;
  //   mint rv = 1;
  //   for (int i = 0; i < k; i++) {
  //     rv *= 1 - mint(q).pow(n - i);
  //     rv /= 1 - mint(q).pow(i + 1);
  //   }
  //   return rv;
  // };
  // for (int r = 0; r <= K; r++) {
  //   mint ans = gbc(N, r, P);
  //   for (int i = 0; i < r; i++) {
  //     ans *= mint(P).pow(N) - mint(P).pow(i);
  //   }
  //   cout << ans.val() << ' ';
  // }

  mint ans = 1;
  for (int r = 0; r <= K; r++) {
    cout << ans.val() << ' ';
    if (r <= N) {
      ans *= 1 - mint(P).pow(N - r);
      mint d = 1 - mint(P).pow(r + 1);
      ans *= d == 0 ? 0 : 1 / d;
      ans *= mint(P).pow(N) - mint(P).pow(r);
    }
  }
}
