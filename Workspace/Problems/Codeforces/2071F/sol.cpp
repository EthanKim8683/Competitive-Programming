#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"

using namespace std;
using namespace atcoder;

const int MAXA = 1e9;
const int INF = 1e9 + 2e5;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // binary search for p
  // checker function tries each i
  // as i increases, j > i become bad at most once
  // store number of bad j for each i
  // return whether there exists and i with no more than K bad j

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto check = [&](int p) -> bool {
      auto solve_right = [&](vector<int> A) -> vector<int> {
        using S = int;
        auto op = [&](S a, S b) -> S { return min(a, b); };
        auto e = [&]() -> S { return INF; };
        using F = int;
        auto mapping = [&](F f, S x) -> S {
          if (x == INF) return x;
          return f + x;
        };
        auto composition = [&](F f, F g) -> F { return f + g; };
        auto id = [&]() -> F { return 0; };
        lazy_segtree<S, op, e, F, mapping, composition, id> st(N);
        for (int i = 0; i < N; i++) {
          st.set(i, A[i] + i);
        }

        vector<int> rv(N, 0);
        int count = 0;
        for (int i = 0; i < N; i++) {
          while (true) {
            int j = st.max_right(i + 1, [&](S x) -> bool { return x >= p; });
            if (j == N) break;

            st.set(j, INF);
            st.apply(j + 1, N, -1);
            count++;
          }
          rv[i] = count;

          if (st.get(i) == INF) {
            count--;
          } else {
            st.apply(i + 1, N, -1);
          }
        }
        return rv;
      };

      auto cost1 = solve_right(A);

      auto A2 = A;
      reverse(A2.begin(), A2.end());
      auto cost2 = solve_right(A2);
      reverse(cost2.begin(), cost2.end());

      for (int i = 0; i < N; i++) {
        if (A[i] < p) continue;
        if (cost1[i] + cost2[i] <= K) return true;
      }
      return false;
    };
    auto A2 = A;
    sort(A2.begin(), A2.end());
    int l = A2[K], r = A2[K] + N;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << l << '\n';
  }
}
