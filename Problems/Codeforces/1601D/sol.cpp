#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"
#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

const int INF = 1e9;

using S = int;
S op(S a, S b) { return max(a, b); }
S e() { return -INF; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, D;
  cin >> N >> D;

  vector<pair<int, int>> people(N);
  for (auto &[s, a] : people) {
    cin >> s >> a;
  }

  // if s <= a then it would be the maximum number of non-intersecting ranges
  //
  // if s > a, either a is within (r, l], where r and l are the right and left
  // ends of two adjacent ranges, respectively, or a is within (l, r] of a range
  // and s >= r

  vector<int> cc;
  cc.push_back(D);
  for (auto [s, a] : people) {
    cc.push_back(s);
    cc.push_back(a);
  }
  sort(cc.begin(), cc.end());
  auto compress = [&](int x) -> int {
    return lower_bound(cc.begin(), cc.end(), x) - cc.begin();
  };

  D = compress(D);
  for (auto &[s, a] : people) {
    s = compress(s);
    a = compress(a);
  }

  vector<int> ps(cc.size() + 1, 0);
  fenwick_tree<int> ft(cc.size() + 1);
  for (auto [s, a] : people) {
    if (s > a) {
      ps[a] += 1;
      ft.add(a, -1);
      ft.add(s + 1, 1);
    }
  }
  for (int i = 0; i < cc.size(); i++) {
    ps[i + 1] += ps[i];
  }

  vector<tuple<int, int, int>> ranges;
  sort(people.begin(), people.end(), [&](auto a, auto b) {
    auto key = [&](pair<int, int> person) -> pair<int, int> {
      auto [s, a] = person;
      return {min(s, a), a - s};
    };
    return key(a) < key(b);
  });
  int w0 = ft.sum(D + 1, cc.size() + 1);
  for (auto [s, a] : people) {
    if (s <= a) {
      ranges.push_back({s, a, 1 + ft.sum(a + 1, cc.size() + 1)});
    } else {
      ft.add(a, 1);
      ft.add(s + 1, -1);
    }
  }

  segtree<S, op, e> st(cc.size());
  st.set(D, w0 - ps[D]);
  for (auto [l, r, w] : ranges) {
    st.set(r, max(st.get(r), st.prod(0, l + 1) + ps[l] + w - ps[r]));
  }
  cout << st.all_prod() + ps[cc.size()];
}
