#include <bits/stdc++.h>

using namespace std;

const int MAXD = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<pair<int, int>> beavers(N);
    for (auto &[x, y] : beavers) {
      cin >> x >> y;
    }
    sort(beavers.begin(), beavers.end());

    vector<pair<int, int>> flipped;
    for (auto [x, y] : beavers) {
      flipped.emplace_back(y, x);
    }
    sort(flipped.begin(), flipped.end());

    auto check = [&](int x) -> bool {
      auto check_simple = [&](vector<pair<int, int>> beavers) -> bool {
        int ymax = 0;
        for (int l = 0, r = 0; r < N; r++) {
          while (l < r and beavers[l].first <= beavers[r].first - x) {
            ymax = max(ymax, beavers[l].second);
            l++;
          }
          if (ymax - beavers[r].second >= x) return true;
        }
        return false;
      };
      return check_simple(beavers) or check_simple(flipped);
    };
    int l = 0, r = MAXD;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << l << '\n';
  }
}
