#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int MAXN = 3000;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    mint ans = 0;
    for (int i = 1; i <= N; i++) {
      int n1 = 0, n2 = 0, p1 = -1, p2 = i - 1;
      mint count = 1;
      for (int j = 0; j < N; j++) {
        if (P[j] < 0) {
          n1 += 1;
          n2 += 1;
        } else if (P[j] < i) {
          int k = (P[j] - 1) - p1, w = max(n1 - n2, 0);
          count *= binom<mint>(n1 - w, k - w);
          n2 -= k - w;
          n1 = 0;
          p1 = P[j];
        } else {
          int k = (P[j] - 1) - p2, w = max(n2 - n1, 0);
          count *= binom<mint>(n2 - w, k - w);
          n1 -= k - w;
          n2 = 0;
          p2 = P[j];
        }
      }
      {
        int k = (i - 1) - p1, w = max(n1 - n2, 0);
        count *= binom<mint>(n1 - w, k - w);
        n2 -= k - w;
        n1 = 0;
      }
      {
        int k = (N - 1) - p2, w = max(n2 - n1, 0);
        count *= binom<mint>(n2 - w, k - w);
        n1 -= k - w;
        n2 = 0;
      }
      ans += count;
    }
    bool ok = true;
    for (int i = 0; i < N; i++) {
      ok = ok and (P[i] < 0 or P[i] == i);
    }
    if (ok) {
      ans -= N - 1;
    }
    cout << ans.val() << '\n';
  }
}
