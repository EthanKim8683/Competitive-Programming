#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

using S = pair<i64, int>;
S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
S e() { return {0, 0}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<pair<int, int>> pairs(N);
  for (auto &[a, b] : pairs) {
    cin >> a >> b;
  }

  sort(pairs.begin(), pairs.end(), [&](auto a, auto b) {
    auto key = [&](pair<int, int> p) -> pair<int, int> {
      return {p.first + p.second, p.second};
    };
    return key(a) > key(b);
  });

  // if x are not correct (incorrect or skipped), the top x-k b values are added
  //
  // divide and conquer!

  vector<int> cc;
  for (auto [a, b] : pairs) {
    cc.push_back(b);
  }
  sort(cc.begin(), cc.end());
  cc.erase(unique(cc.begin(), cc.end()), cc.end());
  auto compress = [&](int x) -> int {
    return lower_bound(cc.begin(), cc.end(), x) - cc.begin();
  };

  i64 sum = 0, base = 0;
  for (auto [a, b] : pairs) {
    sum += a + b;
    base += b;
  }

  segtree<S, op, e> st(cc.size());
  int i = 0;
  vector<i64> ans(N + 1);
  auto dfs = [&](auto self, int l1, int r1, int l2, int r2) -> void {
    if (l1 > r1) return;
    int k = l1 + (r1 - l1) / 2;

    pair<i64, int> best = {0, 0};
    auto apply = [&]() -> void {
      int l = 0, r = cc.size();
      while (l < r) {
        int m = l + (r - l) / 2;
        st.prod(m, cc.size()).second <= i - k ? r = m : l = m + 1;
      }

      auto [sum3, count] = st.prod(l, cc.size());
      i64 sum2 = sum + sum3;
      if (l > 0) {
        sum2 += (i64) (i - k - count) * cc[l - 1];
      }
      best = max(best, {sum2, i});
    };

    for (; i - 1 >= max(k, l2); i--) {
      auto [a, b] = pairs[i - 1];
      auto [sum2, count] = st.get(compress(b));
      st.set(compress(b), {sum2 - b, count - 1});
      sum += a + b;
    }
    for (; i < r2; i++) {
      if (i >= max(k, l2)) {
        apply();
      }
      auto [a, b] = pairs[i];
      auto [sum2, count] = st.get(compress(b));
      st.set(compress(b), {sum2 + b, count + 1});
      sum -= a + b;
    }
    apply();
    ans[k] = best.first - base;

    int m = best.second;
    self(self, l1, k - 1, l2, m);
    self(self, k + 1, r1, m, r2);
  };
  dfs(dfs, 0, N, 0, N);

  while (Q--) {
    int k;
    cin >> k;

    cout << ans[k] << '\n';
  }
}
