#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

using S = i64;
S op(S a, S b) { return max(a, b); }
S e() { return 0; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<vector<int>> divs(2e5 + 1);
  for (int i = 1; i <= 2e5; i++) {
    for (int j = 2 * i; j <= 2e5; j += i) {
      divs[j].push_back(i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    int M = 0;
    for (auto d : divs[N]) {
      M += d;
    }
    segtree<S, op, e> st(M);

    int t = 0;
    for (int i = 0; i < divs[N].size(); i++) {
      int d = divs[N][i];
      for (int j = 0; j < d; j++) {
        i64 sum = 0;
        for (int k = 0; k < N; k += d) {
          sum += (i64) A[j + k] * d;
        }
        st.set(t++, sum);
      }
    }

    cout << st.all_prod() << '\n';

    while (Q--) {
      int p, x;
      cin >> p >> x;
      p--;

      int t = 0;
      for (int i = 0; i < divs[N].size(); i++) {
        int d = divs[N][i], j = p % d;
        st.set(t + j, st.get(t + j) + (i64) (x - A[p]) * d);
        t += d;
      }
      A[p] = x;

      cout << st.all_prod() << '\n';
    }
  }
}
