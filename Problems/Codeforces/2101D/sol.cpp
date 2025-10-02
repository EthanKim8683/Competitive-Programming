#include <bits/stdc++.h>

#include "atcoder/lazysegtree"
#include "atcoder/segtree"
#include "ethankim8683/viz"

using namespace std;
using namespace atcoder;
using i64 = long long;
using S = int;
using F = int;

const int INF = 1e9;

S op_max(S a, S b) { return max(a, b); }
S e_max() { return -INF; }

S op_min(S a, S b) { return min(a, b); }
S e_min() { return INF; }

S mapping(F f, S x) { return max(f, x); }
F composition(F f, F g) { return max(f, g); }
F id() { return -INF; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
      cin >> A[i];
      A[i]--;
    }

    // sliding window should work

    vector<int> index(N);
    for (int i = 1; i <= N; i++) {
      index[A[i]] = i;
    }

    vector<int> L(N + 1), R(N + 1);
    {
      segtree<S, op_max, e_max> st(N);
      set<int> S;
      int l = 1;
      for (int r = 1; r <= N; r++) {
        for (; l < r; l++) {
          bool ok = true;
          auto it = S.upper_bound(A[r]);
          if (it != S.end()) {
            ok = ok and index[*it] == st.prod(A[r] + 1, N);
          }
          if (it != S.begin()) {
            ok = ok and index[*prev(it)] == st.prod(0, A[r]);
          }
          if (ok) break;
          st.set(A[l], e_max());
          S.erase(A[l]);
        }
        st.set(A[r], r);
        S.insert(A[r]);
        L[r] = l;
      }
    }
    {
      segtree<S, op_min, e_min> st(N);
      set<int> S;
      int r = N;
      for (int l = N; l >= 1; l--) {
        for (; l < r; r--) {
          bool ok = true;
          auto it = S.upper_bound(A[l]);
          if (it != S.end()) {
            ok = ok and index[*it] == st.prod(A[l] + 1, N);
          }
          if (it != S.begin()) {
            ok = ok and index[*prev(it)] == st.prod(0, A[l]);
          }
          if (ok) break;
          st.set(A[r], e_min());
          S.erase(A[r]);
        }
        st.set(A[l], l);
        S.insert(A[l]);
        R[l] = r;
      }
    }

    // for (int i = 1; i <= N; i++) {
    //   cerr << L[i] << ' ' << R[i] << '\n';
    // }
    // cerr << '\n';

    // vector fill(N + 1, vector<int>(N + 1, 0));
    // for (int i = 1; i <= N; i++) {
    //   for (int j = L[i]; j <= R[i]; j++) {
    //     for (int k = j; k <= R[i]; k++) {
    //       fill[j][k] = 1;
    //     }
    //   }
    // }

    // viz([&]() -> void {
    //   int $K = 20;

    //   ClearBackground(WHITE);
    //   for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) {
    //       if (fill[i][j]) {
    //         DrawRectangle((i - 1) * $K, (j - 1) * $K, $K, $K, BLACK);
    //       } else {
    //         DrawRectangleLines((i - 1) * $K, (j - 1) * $K, $K, $K, BLACK);
    //       }
    //     }
    //   }
    // });

    // int ans = 0;
    // for (int i = 1; i <= N; i++) {
    //   for (int j = 1; j <= N; j++) {
    //     ans += fill[i][j];
    //   }
    // }
    // cout << ans << '\n';

    lazy_segtree<S, op_max, e_max, F, mapping, composition, id> lst(N + 1);
    for (int i = 1; i <= N; i++) {
      lst.apply(L[i], R[i] + 1, R[i]);
    }

    // viz([&]() -> void {
    //   int $K = 20;

    //   ClearBackground(WHITE);
    //   for (int i = 1; i <= N; i++) {
    //     for (int j = 1; j <= N; j++) {
    //       if (i <= j and j <= lst.get(i)) {
    //         DrawRectangle((i - 1) * $K, (j - 1) * $K, $K, $K, BLACK);
    //       } else {
    //         DrawRectangleLines((i - 1) * $K, (j - 1) * $K, $K, $K, BLACK);
    //       }
    //     }
    //   }
    // });

    i64 ans = 0;
    for (int i = 1; i <= N; i++) {
      ans += max(lst.get(i) - i + 1, 0);
    }
    cout << ans << '\n';
  }
}