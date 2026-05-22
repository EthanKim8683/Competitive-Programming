#include <bits/stdc++.h>

#include "atcoder/modint"
#include "ethankim8683/combinatorics"

using namespace std;
using namespace atcoder;
using mint = modint1000000007;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    // the minimum element outside the subsegment is the mex
    //
    // the number of ways to get the minimum value amongst all filled missing
    // elements outside the subsegment is a function of the number of missing
    // elements outside the subsegment

    vector<bool> is_missing(N, true);
    for (auto e : A) {
      if (e == -1) continue;
      is_missing[e] = false;
    }

    vector<int> missing;
    for (int i = 0; i < N; i++) {
      if (!is_missing[i]) continue;
      missing.push_back(i);
    }

    vector ps(missing.size() + 1, vector<mint>(N + 1, 0)),
        mps(missing.size() + 1, vector<mint>(N + 1, 0));
    for (int i = 0; i < missing.size(); i++) {
      for (int j = 0; j <= i; j++) {
        mint v = binom<mint>(i, j) * fact<mint>(j) * (missing.size() - i) *
                 fact<mint>(missing.size() - 1 - j);
        ps[i][missing[j] + 1] += v;
        mps[i][missing[j] + 1] += v * missing[j];
      }

      for (int j = 0; j < N; j++) {
        ps[i][j + 1] += ps[i][j];
        mps[i][j + 1] += mps[i][j];
      }
    }

    vector<int> pm(N, N), sm(N, N);
    for (int i = 0; i + 1 < N; i++) {
      pm[i + 1] = min(pm[i], A[i] == -1 ? N : A[i]);
    }
    for (int i = N - 1; i - 1 >= 0; i--) {
      sm[i - 1] = min(sm[i], A[i] == -1 ? N : A[i]);
    }

    mint ans = 0;
    for (int i = 0; i < N; i++) {
      int holes = 0;
      for (int j = i; j < N; j++) {
        if (A[j] == -1) {
          holes++;
        }

        int fixed = min(pm[i], sm[j]);
        if (holes == missing.size()) {
          ans += fixed * fact<mint>(missing.size());
        } else {
          ans += mps[holes][fixed] - mps[holes][0] +
                 fixed * (ps[holes][N] - ps[holes][fixed]);
        }
      }
    }
    cout << ans.val() << '\n';
  }
}
