#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto contribution = [&](vector<int> A) -> mint {
      mint rv = 0, sum = 0;
      i64 ps = 0;
      map<i64, int> S;
      S[ps] += 1;
      for (int i = 0; i < N; i++) {
        ps += A[i];

        int count = 1;
        for (auto it = S.upper_bound(ps); it != S.end(); it = S.erase(it)) {
          auto [ps2, count2] = *it;
          sum -= (mint) ps2 * count2;
          count += count2;
        }
        sum += (mint) ps * count;
        S[ps] += count;

        rv += (mint) ps * (i + 1) - sum;
      }
      return rv;
    };
    mint ans = 0;
    auto A2 = A;
    for (int i = 0; i < N; i += 2) {
      A2[i] = -A2[i];
    }
    ans += contribution(A2);
    for (auto &e : A2) {
      e = -e;
    }
    ans += contribution(A2);
    cout << ans.val() << '\n';
  }
}
