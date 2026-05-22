#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<vector<int>> segs(2 * N);
    for (int i = 0; i < N; i++) {
      segs[i + N].push_back(A[i]);
    }
    for (int i = N - 1; i >= 1; i--) {
      merge(segs[i << 1].begin(), segs[i << 1].end(), segs[i << 1 | 1].begin(),
            segs[i << 1 | 1].end(), back_inserter(segs[i]));
    }
    auto all = [&](int l, int r, int l2, int r2) -> int {
      int rv = 0;
      auto use = [&](int i) -> void {
        rv += lower_bound(segs[i].begin(), segs[i].end(), r2) -
              lower_bound(segs[i].begin(), segs[i].end(), l2);
      };
      for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
          use(l);
          l++;
        }
        if (r & 1) {
          r--;
          use(r);
        }
      }
      return rv;
    };
    auto any = [&](int l, int r, int l2, int r2) -> int {
      int rv;
      auto use = [&](int i) -> void {
        auto it1 = lower_bound(segs[i].begin(), segs[i].end(), l2),
             it2 = lower_bound(segs[i].begin(), segs[i].end(), r2);
        if (it1 != it2) {
          rv = *it1;
        }
      };
      for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
          use(l);
          l++;
        }
        if (r & 1) {
          r--;
          use(r);
        }
      }
      return rv;
    };

    int Q;
    cin >> Q;

    while (Q--) {
      int l, r;
      cin >> l >> r;
      l--;

      vector<int> extra;
      int ans = 0;
      for (int i = 30 - 1; i >= 0; i--) {
        int l2 = ans, r2 = ans | 1 << i, count0 = all(l, r, l2, r2),
            count = count0;
        for (auto e : extra) {
          if ((e >> i & 1) == 0) {
            count++;
          }
        }
        if (count >= 2) {
          auto extra0 = extra;
          extra.clear();
          for (auto e : extra0) {
            if ((e >> i & 1) == 0) {
              extra.push_back(e);
            }
          }
        } else {
          ans |= 1 << i;
          if (count0 == 1) {
            extra.push_back(any(l, r, l2, r2));
          }
        }
      }
      cout << ans << '\n';
    }
  }
}
