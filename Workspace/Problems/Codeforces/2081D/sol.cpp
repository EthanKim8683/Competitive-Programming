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

    vector<int> P(N);
    for (auto &e : P) cin >> e;
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());

    vector<pair<int, int>> occ(P.back() + 1, {-1, -1});
    for (auto e : P) {
      occ[e] = {e, 0};
    }
    vector<tuple<int, int, int>> edges;
    for (int i = P.back(); i - 1 >= 0; i--) {
      auto [a, d] = occ[i];
      if (occ[i - 1].first == -1) {
        occ[i - 1] = {a, d + 1};
      } else {
        edges.push_back({d + 1, i - 1, a});
      }
    }
    for (auto e : P) {
      for (int i = e; i <= P.back(); i += e) {
        auto [a, d] = occ[i];
        edges.push_back({d, e, a});
      }
    }
    sort(edges.begin(), edges.end());
    dsu d(P.back() + 1);
    int ans = 0;
    for (auto [w, a, b] : edges) {
      if (d.same(a, b)) continue;
      d.merge(a, b);
      ans += w;
    }
    cout << ans << '\n';
  }
}
