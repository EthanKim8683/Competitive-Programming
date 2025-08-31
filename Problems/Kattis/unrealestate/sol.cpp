#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<tuple<int, int, int, int>> rects(N);
  for (auto &rect : rects) {
    f64 x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1 = 1e5 + x1 * 100 + 0.5;
    y1 = 1e5 + y1 * 100 + 0.5;
    x2 = 1e5 + x2 * 100 + 0.5;
    y2 = 1e5 + y2 * 100 + 0.5;
    rect = {x1, y1, x2, y2};
  }

  vector<vector<tuple<int, int, int>>> events(2e5 + 1);
  for (auto [l1, l2, r1, r2] : rects) {
    events[l1].push_back({l2, r2, 1});
    events[r1].push_back({l2, r2, -1});
  }

  cover_query<int, int> cq(2e5);
  f64 ans = 0;
  for (auto eventsi : events) {
    for (auto [l, r, dv] : eventsi) {
      cq.add(l, r, dv);
    }
    ans += cq.cover();
  }
  ans /= 100 * 100;
  cout << setprecision(2) << fixed << ans;
}
