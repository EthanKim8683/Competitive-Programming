#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

int op(int a, int b) { return max(a, b); }
int e() { return -1; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector P(3, vector<int>(N));
    for (auto &r : P) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    vector index(3, vector<int>(N));
    for (int i = 0; i < 3; i++) {
      vector<int> order(N);
      iota(order.begin(), order.end(), 0);
      sort(order.begin(), order.end(),
           [&](int a, int b) { return P[i][a] > P[i][b]; });

      for (int j = 0; j < N; j++) {
        index[i][order[j]] = j;
      }
    }

    vector st(3, segtree<int, op, e>(N));
    for (int i = 0; i < 3; i++) {
      st[i].set(index[i][0], 0);
    }
    vector<pair<int, int>> par(N, {-1, -1});
    for (int i = 1; i < N; i++) {
      for (int j = 0; j < 3; j++) {
        int p = st[j].prod(0, index[j][i]);
        if (p != -1) {
          par[i] = {p, j};
          for (int k = 0; k < 3; k++) {
            st[k].set(index[k][i], i);
          }
          break;
        }
      }
    }
    if (par[N - 1] == make_pair(-1, -1)) {
      cout << "NO\n";
      continue;
    }

    vector<pair<int, int>> ans;
    int a = N - 1;
    while (a != 0) {
      auto [a_, i] = par[a];
      ans.push_back({i, a});
      a = a_;
    }
    reverse(ans.begin(), ans.end());

    cout << "YES\n";
    cout << ans.size() << '\n';
    for (auto [i, a] : ans) {
      cout << "qkj"[i] << ' ' << a + 1 << '\n';
    }
  }
}
