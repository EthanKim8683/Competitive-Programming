#include <bits/stdc++.h>

using namespace std;

const int MAXX = 300;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  auto encode = [&](int x1, int y1, int x2, int y2) -> pair<int, int> {
    if (x2 < x1) {
      swap(x1, x2);
      swap(y1, y2);
    }
    return {x2 - x1, MAXX + y2 - y1};
  };

  auto decode = [&](int i, int j) -> tuple<int, int, int, int> {
    int y1 = 0, y2 = j - MAXX;
    if (y2 < 0) {
      y1 += -y2;
      y2 += -y2;
    }
    return {0, y1, i, y2};
  };

  // southwest 6:20 terminal 2 d4
  // united 7:10 terminal 2 d5
  // southwest 7:25 terminal d3
  // united 10:40 terminal 2 d5

  vector dp(MAXX + 1, vector<int>(2 * MAXX + 1, -1));
  auto dfs = [&](auto self, int i, int j) -> int {
    if (dp[i][j] != -1) return dp[i][j];
    auto [x1, y1, x2, y2] = decode(i, j);
    vector<int> games;
    for (int x = y1 == y2 and x2 < x1 ? x2 + 1 : 0; x < x1; x++) {
      auto [k, m] = encode(x, y1, x2, y2);
      games.push_back(self(self, k, m));
    }
    for (int y = x1 == x2 and y2 < y1 ? y2 + 1 : 0; y < y1; y++) {
      auto [k, m] = encode(x1, y, x2, y2);
      games.push_back(self(self, k, m));
    }
    for (int x = y1 == y2 and x1 < x2 ? x1 + 1 : 0; x < x2; x++) {
      auto [k, m] = encode(x1, y1, x, y2);
      games.push_back(self(self, k, m));
    }
    for (int y = x1 == x2 and y1 < y2 ? y1 + 1 : 0; y < y2; y++) {
      auto [k, m] = encode(x1, y1, x2, y);
      games.push_back(self(self, k, m));
    }
    sort(games.begin(), games.end());
    dp[i][j] = 0;
    for (auto e : games) {
      if (dp[i][j] != e) continue;
      dp[i][j]++;
    }
    return dp[i][j];
  };
  for (int i = 0; i < MAXX + 1; i++) {
    for (int j = 0; j < 2 * MAXX + 1; j++) {
      dfs(dfs, i, j);
    }
  }

  int N;
  cin >> N;

  while (N--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--, y1--, x2--, y2--;

    int ans = 0;
    for (int x = y1 == y2 and x2 < x1 ? x2 + 1 : 0; x < x1; x++) {
      auto [i, j] = encode(x, y1, x2, y2);
      if (dp[i][j] != 0) continue;
      ans++;
    }
    for (int y = x1 == x2 and y2 < y1 ? y2 + 1 : 0; y < y1; y++) {
      auto [i, j] = encode(x1, y, x2, y2);
      if (dp[i][j] != 0) continue;
      ans++;
    }
    for (int x = y1 == y2 and x1 < x2 ? x1 + 1 : 0; x < x2; x++) {
      auto [i, j] = encode(x1, y1, x, y2);
      if (dp[i][j] != 0) continue;
      ans++;
    }
    for (int y = x1 == x2 and y1 < y2 ? y1 + 1 : 0; y < y2; y++) {
      auto [i, j] = encode(x1, y1, x2, y);
      if (dp[i][j] != 0) continue;
      ans++;
    }
    cout << ans << '\n';
  }
}
