#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int INF = 1e9 + 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> ops(N);
  for (auto &[t, x] : ops) {
    cin >> t;
    if (t == 1 or t == 2) {
      cin >> x;
    }
  }

  vector<vector<pair<int, int>>> groups;
  groups.push_back({});
  bool close = false;
  for (auto [t, x] : ops) {
    groups.back().push_back({t, x});
    if (t == 2) {
      close = true;
    } else if (t == 3 and close) {
      groups.push_back({});
      close = false;
    }
  }
  if (groups.back().empty()) {
    groups.pop_back();
  }
}
