#include <bits/stdc++.h>

#include "atcoder/dsu.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> D(N);
    for (auto &e : D) cin >> e;

    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return D[a] > D[b]; });

    dsu d(N);
    for (auto i : order) {
      if (d.size(i) > 1) continue;
      for (int j = 0; j < D[i]; j++) {
        cout << "? " << i + 1 << endl;
        int k;
        cin >> k;
        k--;
        if (d.size(k) > 1) {
          d.merge(i, k);
          break;
        }
        d.merge(i, k);
      }
    }
    cout << "! ";
    for (int i = 0; i < N; i++) {
      cout << d.leader(i) + 1 << ' ';
    }
    cout << endl;
  }
}
