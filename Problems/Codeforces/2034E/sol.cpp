#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // vector<int> P(7);
  // iota(P.begin(), P.end(), 1);
  // do {
  //   vector<int> P_(P.size());
  //   for (int i = 0; i < P.size(); i++) {
  //     P_[i] = i + 1 + P[i];
  //   }
  //   sort(P_.begin(), P_.end());
  //   bool ok = true;
  //   for (int i = 0; i + 1 < P_.size(); i++) {
  //     ok = ok and P_[i] + 1 == P_[i + 1];
  //   }
  //   if (ok) {
  //     for (int i = 1; i <= P.size(); i++) {
  //       cout << i << ' ';
  //     }
  //     cout << '\n';
  //     for (auto e : P) {
  //       cout << e << ' ';
  //     }
  //     cout << '\n';
  //     for (int i = 0; i < P.size(); i++) {
  //       cout << 3 * ((int) P.size() + 1) / 2 - P[i] - (i + 1) << ' ';
  //     }
  //     cout << '\n';
  //     cout << '\n';
  //   }
  // } while (next_permutation(P.begin(), P.end()));

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    // stacking solutions yield additional solutions
    // even K always have solutions
    // we need to solve for the minimum odd K given N
    //
    // sum_c = K(N(N + 1)/2)/N = K(N + 1)/2
    // K is odd, so N + 1 must be even
    // if N is even, N + 1 is odd, so no odd K exist
    //
    // 1 2 3 4 5 6 7
    // 4 7 3 6 2 5 1
    // 7 3 6 2 5 1 4
    //
    // problems like these aren't hard, they're just a massive pain in the ass

    vector ans(K, vector<int>(N, -1));

    if (N == 1) {
      if (K == 1) {
        ans[0][0] = 1;
      }
      goto PRINT;
    }

    if (K == 1) {
      goto PRINT;
    }

    if (K % 2 == 0) {
      vector<int> P(N);
      iota(P.begin(), P.end(), 1);
      int i = 0;
      do {
        if (i == K) break;
        vector<int> Q(N);
        for (int j = 0; j < N; j++) {
          Q[j] = N + 1 - P[j];
        }
        if (P > Q) break;
        for (int j = 0; j < N; j++) {
          ans[i][j] = P[j];
          ans[i + 1][j] = Q[j];
        }
        i += 2;
      } while (next_permutation(P.begin(), P.end()));
      goto PRINT;
    }

    if (N % 2 == 0) {
      goto PRINT;
    }

    {
      int sum_c = 3 * (N + 1) / 2;
      for (int i = 0; i < N; i++) {
        ans[0][i] = N - i;
      }
      int q = sum_c - N - 1;
      for (int i = 0; i < N; i++) {
        int p = sum_c - N + i - q;
        ans[1][i] = p;
        ans[2][i] = q;
        q = p;
      }
      vector<int> P(N);
      iota(P.begin(), P.end(), 1);
      int i = 3;
      do {
        if (i == K) break;
        vector<int> Q(N);
        for (int j = 0; j < N; j++) {
          Q[j] = N + 1 - P[j];
        }
        if (P > Q) break;
        bool ok = true;
        for (int j = 0; j < 3; j++) {
          ok = ok and P != ans[j];
          ok = ok and Q != ans[j];
        }
        if (!ok) continue;
        for (int j = 0; j < N; j++) {
          ans[i][j] = P[j];
          ans[i + 1][j] = Q[j];
        }
        i += 2;
      } while (next_permutation(P.begin(), P.end()));
      goto PRINT;
    }

  PRINT:
    bool ok = true;
    for (auto r : ans) {
      for (auto e : r) {
        ok = ok and e != -1;
      }
    }
    if (ok) {
      cout << "YES\n";
      for (auto r : ans) {
        for (auto e : r) {
          cout << e << ' ';
        }
        cout << '\n';
      }
#ifdef ETHANKIM8683

      for (int i = 0; i < K; i++) {
        auto r = ans[i];
        sort(r.begin(), r.end());
        bool ok = r[0] == 1;
        for (int j = 0; j + 1 < N; j++) {
          ok = ok and r[j] + 1 == r[j + 1];
        }
        if (!ok) {
          cerr << "row " << i << " is not a permutation\n";
          goto SKIP;
        }
      }

      {
        int sum_c = K * (N + 1) / 2;
        for (int i = 0; i < N; i++) {
          int sum = 0;
          for (int j = 0; j < K; j++) {
            sum += ans[j][i];
          }
          if (sum != sum_c) {
            cerr << "col " << i << " does not have sum " << sum << '\n';
            goto SKIP;
          }
        }
      }

      for (int i = 0; i < K; i++) {
        for (int j = i + 1; j < K; j++) {
          if (ans[i] == ans[j]) {
            cerr << "rows " << i << " and " << j << " are equal\n";
            goto SKIP;
          }
        }
      }
    SKIP:;
#endif
    } else {
      cout << "NO\n";
    }
  }
}
