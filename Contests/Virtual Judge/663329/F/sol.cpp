#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
    sort(A.begin(), A.end());

    map<int, int> limits;
    for (int i = 0; i < K; i++) {
      int x, y;
      cin >> x >> y;
      limits[x] = y;
    }
    limits[-1] = 0;

    auto solve = [&]() -> int {
      map<int, int> counts;
      for (auto e : A) {
        counts[e]++;
      }
      for (auto [x, y] : limits) {
        if (counts[x] > y) {
          return 1;
        }
      }

      set<int> leaders;
      for (auto [x, y] : limits) {
        if (y != 0) continue;
        leaders.insert(x);
      }

      map<int, map<int, int>> limits_;
      for (auto [x, y] : limits) {
        int l = *prev(leaders.upper_bound(x));
        limits_[l][x] = y;
      }

      sort(A.begin(), A.end());
      map<int, pair<int, int>> states;
      int moves = 0;
      for (auto e : A) {
        int l = *prev(leaders.upper_bound(e));
        if (!states.contains(l)) {
          states[l] = {l + 1, 0};
        }
        auto &[i, j] = states[l];
        int e_;
        while (limits_[l].contains(i) and j == limits_[l][i]) {
          i++;
          j = 0;
        }
        e_ = i;
        j++;
        if (e_ <= e) {
          moves += e - e_;
        } else {
          return 1;
        }
      }
      return moves % 2 == 0;
    };

    cout << (string[]) {"Pico", "FuuFuu"}[solve()] << '\n';
  }
}