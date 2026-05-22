#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  range_add_fenwick_tree<i64> ft(N);
  for (int i = 0; i < N; i++) {
    ft.add(i, i + 1, A[i]);
  }

  while (Q--) {
    int t, x, y;
    cin >> t >> x >> y;

    if (t == 1) {
      x--;
      int i = x + 1;
      while (i > 0) {
        int y2 = ft.sum(i - 1, i);
        if (y2 > y) break;

        int l = 0, r = i - 1;
        while (l < r) {
          int m = l + (r - l) / 2;
          ft.sum(m, m + 1) == y2 ? r = m : l = m + 1;
        }
        ft.add(l, i, y - y2);
        i = l;
      }
    } else {
      x--;
      int i = x, ans = 0;
      while (y > 0) {
        int l = i, r = N;
        while (l < r) {
          int m = l + (r - l) / 2;
          ft.sum(m, m + 1) <= y ? r = m : l = m + 1;
        }
        i = l;
        if (i == N) break;

        l = i + 1;
        r = N;
        while (l < r) {
          int m = l + (r - l + 1) / 2;
          ft.sum(i, m) <= y ? l = m : r = m - 1;
        }
        ans += l - i;
        y -= ft.sum(i, l);
        i = l;
      }
      cout << ans << '\n';
    }
  }
}
