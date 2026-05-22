#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vector<int> P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    vector<int> index(N);
    for (int i = 0; i < N; i++) {
      index[P[i]] = i;
    }

    while (Q--) {
      int l, r, k;
      cin >> l >> r >> k;
      l--, r--, k--;

      int need_gt = 0, need_lt = 0, replace_gt = 0, replace_lt = 0;
      bool found = false;
      while (l <= r) {
        int m = (l + r) / 2;
        if (index[k] == m) {
          found = true;
          break;
        } else if (index[k] > m) {
          if (P[m] > k) {
            replace_gt++;
          }
          need_lt++;
          l = m + 1;
        } else if (index[k] < m) {
          if (P[m] < k) {
            replace_lt++;
          }
          need_gt++;
          r = m - 1;
        }
      }
      if (!found or need_lt > k or need_gt > N - 1 - k) {
        cout << -1 << ' ';
      } else {
        cout << 2 * max(replace_lt, replace_gt) << ' ';
      }
    }
    cout << '\n';
  }
}