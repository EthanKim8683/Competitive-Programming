#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

using I = int;
using Lli = long long int;

unordered_map<I, vector<I>> x_locs;
unordered_map<I, vector<I>> y_locs;
unordered_set<I> x_viss;
unordered_set<I> y_viss;
queue<pair<I, Lli>> x_stts;
queue<pair<I, Lli>> y_stts;

I main(void) {
  freopen("lasers.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("lasers.out", "w", stdout);
#endif
  I n, l_x, l_y, b_x, b_y;
  cin >> n >> l_x >> l_y >> b_x >> b_y;
  if (l_x == b_x || l_y == b_y) {
    printf("0\n");
    return 0;
  }
  while (n--) {
    I x, y;
    cin >> x >> y;
    x_locs[x].push_back(y);
    y_locs[y].push_back(x);
  }
  x_stts.push({l_x, 0});
  y_stts.push({l_y, 0});
  x_viss.insert(l_x);
  y_viss.insert(l_y);
  Lli res = 1e18;
  while (!x_stts.empty() || !y_stts.empty()) {
    if (!x_stts.empty()) {
      auto [a, dst] =  x_stts.front();
      x_stts.pop();
      dst++;
      for (const auto b : x_locs[a]) {
        if (y_viss.find(b) == y_viss.end()) {
          if (b == b_y) {
            printf("%lli\n", dst);
            return 0;
          }
          y_viss.insert(b);
          y_stts.push({b, dst});
        }
      }
    }
    if (!y_stts.empty()) {
      auto [a, dst] =  y_stts.front();
      y_stts.pop();
      dst++;
      for (const auto b : y_locs[a]) {
        if (x_viss.find(b) == x_viss.end()) {
          if (b == b_x) {
            printf("%lli\n", dst);
            return 0;
          }
          x_viss.insert(b);
          x_stts.push({b, dst});
        }
      }
    }
  }
  printf("-1\n");
  return 0;
}