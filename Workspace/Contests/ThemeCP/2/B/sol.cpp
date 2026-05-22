#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<bool> has(N, false);
    for (auto e : A) {
      if (e < N) {
        has[e] = true;
      }
    }
    vector<int> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + !has[i];
    }

    map<int, int> counts;
    for (auto e : A) {
      counts[e]++;
    }
    vector<pair<int, int>> cc;
    for (auto [v, count] : counts) {
      cc.push_back({count, v});
    }
    sort(cc.begin(), cc.end());
    auto comp = [&](int e) -> int {
      return lower_bound(cc.begin(), cc.end(), make_pair(counts[e], e)) -
             cc.begin();
    };

    fenwick_tree<int> ft1(cc.size()), ft2(cc.size());
    for (auto [v, count] : counts) {
      if (v > N) {
        ft1.add(comp(v), count);
        ft2.add(comp(v), 1);
      }
    }
    int ans = counts.size();
    for (int i = N; i > 0; i--) {
      if (counts.contains(i)) {
        ft1.add(comp(i), counts[i]);
        ft2.add(comp(i), 1);
      }

      if (ps[i] - ps[0] == 0) {
        ans = min<int>(ans, counts.size() - i);
      }

      if (ps[i] - ps[0] <= K) {
        int l = 0, r = cc.size();
        while (l < r) {
          int m = l + (r - l + 1) / 2;
          ft1.sum(0, m) <= K ? l = m : r = m - 1;
        }
        ans = min<int>(ans, counts.size() - i - ft2.sum(0, l) + ps[i] - ps[0]);
      }
    }
    cout << ans << '\n';
  }
}
