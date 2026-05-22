#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int H, W, C;
  cin >> H >> W >> C;

  if (H <= 5 and W <= 5 and C <= 5) {
    auto insert_row = [&](int h, int w, string s, int i, char c) -> string {
      string r = string(w, c) + '\n';
      s.insert(s.begin() + i * (w + 1), r.begin(), r.end());
      return s;
    };
    auto insert_col = [&](int h, int w, string s, int i, char c) -> string {
      for (int j = 0; j < h; j++) {
        s.insert(s.begin() + j * (w + 2) + i, c);
      }
      return s;
    };

    vector dp(H, vector<set<string>>(W));
    for (int i = 0; i < H; i++) {
      dp[i][0].insert(string(i, '\n'));
    }
    for (int i = 0; i < W; i++) {
      dp[0][i].insert("");
    }
    auto dfs = [&](auto self, int h, int w) -> void {
      if (!dp[h][w].empty()) return;

      self(self, h - 1, w);
      self(self, h, w - 1);

      for (auto e : dp[h - 1][w]) {
        for (int i = 0; i < h; i++) {
          for (char j = '1'; j <= '0' + C; j++) {
            dp[h][w].insert(insert_row(h - 1, w, e, i, j));
          }
        }
      }
      for (auto e : dp[h][w - 1]) {
        for (int i = 0; i < w; i++) {
          for (char j = '1'; j <= '0' + C; j++) {
            dp[h][w].insert(insert_col(h, w - 1, e, i, j));
          }
        }
      }
    };
    dfs(dfs, H - 1, W - 1);

    set<string> ans;
    for (auto e : dp[H - 1][W - 1]) {
      for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
          for (char k = '1'; k <= '0' + C; k++) {
            ans.insert(
                insert_col(H, W - 1, insert_row(H - 1, W - 1, e, i, k), j, k));
          }
        }
      }
    }

    // for (auto e : ans) {
    //   cerr << e << '\n';
    // }
    cerr << ans.size() << '\n';
  }

  // I'm so salty because I came up with something almost identical to the
  // editorial, but I just couldn't get it to work for whatever reason.
}
