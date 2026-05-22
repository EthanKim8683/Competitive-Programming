#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // mt19937 rng(time(nullptr));

  // int N = 100 + rng() % 100, M = 1e6;

  // vector<int> A(M + 1), P(M + 1);
  // P[0] = 0;
  // for (int i = 1; i <= N; i++) {
  //   A[i] = rng() % 2;
  //   P[i] = P[i - 1] ^ A[i];
  // }
  // for (int i = N + 1; i <= M; i++) {
  //   A[i] = P[i / 2];
  //   P[i] = P[i - 1] ^ A[i];
  // }
  // for (int i = 1; i <= M; i += 2) {
  //   cerr << P[i] << ' ';
  // }
  // cerr << '\n';
  // for (int i = 2; i <= M; i += 2) {
  //   cerr << P[i] << ' ' << P[i / 2] << '\n';
  // }
  // for (int i = 1; i <= M; i++) {
  //   cerr << A[i] << ' ' << P[i / 2] << '\n';
  // }
  // int j = 0;
  // for (int i = 1; i <= M; i++) {
  //   if (A[i] != P[i / 2]) {
  //     j = i;
  //   }
  // }
  // cerr << N << ' ' << j << '\n';

  int T;
  cin >> T;

  while (T--) {
    int N;
    i64 L, R;
    cin >> N >> L >> R;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
      cin >> A[i];
    }

    // p(m) = a_1 ^ ... ^ a_m
    //
    // p(m) = p(floor(m / 2)) ^ (p(floor((floor(m / 2) + 1) / 2)) ^
    // p(floor((floor(m / 2) + 2) / 2)) ^ ... ^ p(k) ^ p(k) ^ ... ^ p(floor(m /
    // 2)))
    //
    // p(m) = {
    //   p(m / 2) ^ c  if m % 2 == 0
    //   c             if m % 2 == 1
    // }
    //
    // a_m = p(m) ^ p(m - 1) = {
    //   (p(m / 2) ^ c) ^ c        if m % 2 == 0
    //   c ^ (p((m - 1) / 2) ^ c)  if m % 2 == 1
    // }
    //
    // a_m = p(floor(m / 2))

    int logN_ = __lg(2 * (N + 2) - 1), N_ = 1 << logN_;

    vector<int> A_(N_), P(N_);
    P[0] = 0;
    for (int i = 1; i <= N; i++) {
      A_[i] = A[i];
      P[i] = P[i - 1] ^ A_[i];
    }
    for (int i = N + 1; i < N_; i++) {
      A_[i] = P[i / 2];
      P[i] = P[i - 1] ^ A_[i];
    }

    int c = P[N_ - 1];

    auto solve = [&](i64 x) -> i64 {
      vector<int> digits;
      for (i64 i = x; i > 0; i /= 2) {
        digits.push_back(i % 2);
      }
      reverse(digits.begin(), digits.end());

      int K = digits.size();

      vector dp(K, vector(2, vector<i64>(2, 0)));
      for (int i = 0; i < K - 1; i++) {
        dp[i + 1][c][i > 0] += 1;
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < 2; k++) {
            for (int l = 0; l < 2; l++) {
              if (k or l <= digits[i]) {
                dp[i + 1][l ? c : j ^ c][k or l < digits[i]] += dp[i][j][k];
              }
            }
          }
        }
      }

      i64 ans = 0;
      if (1 < x) {
        ans += c;
      }
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          if (i or j < digits[K - 1]) {
            ans += dp[K - 1][1][i];
          }
        }
      }

      auto f = [&](i64 x) -> i64 {
        return __builtin_ctzll(x >> 1) % 2 == 0 ? c : 0;
      };

      for (int i = 1; i < N_ and i < x; i++) {
        ans += A_[i] - f(i);
      }

      for (int i = N_ / 2; i < N_; i++) {
        int p = P[i];
        for (i64 j = 2 * i; j < x; j *= 2) {
          for (i64 k = j; k < min(j + 2, x); k++) {
            ans += p - f(k);
          }
          p ^= c;
        }
      }

      return ans;
    };
    cout << solve(R + 1) - solve(L) << '\n';
  }
}
