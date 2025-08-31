#include <bits/stdc++.h>

#include "atcoder/fenwicktree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

// My first DMOJ contest! Hope I do alright!
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  auto check = [&](int G) -> bool {
    deque<i64> dp;
    i64 ps = 0;
    dp.push_front(-INF - ps);
    for (auto e : A) {
      if (e == -1) {
        ps += G;
        dp.push_front(-INF - ps);
      } else {
        int l = 0, r = dp.size();
        while (l < r) {
          int m = l + (r - l) / 2;
          dp[m] + ps + G > e ? r = m : l = m + 1;
        }
        if (l == dp.size()) {
          dp.push_back(e - ps);
        } else {
          dp[l] = min(dp[l], (i64) e - ps);
        }
      }
    }
    return dp.size() - 1 >= K;
  };

  int l = -1, r = 1e9 + 1;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  if (l > 1e9) {
    cout << "Infinity";
  } else {
    cout << l;
  }
}
