#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int MAXK = 5e4;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int P, S;
    cin >> P >> S;

    int x = 1, s, p, w, h;
    bool found = false;
    for (; x * S <= MAXK; x++) {
      s = x * S;
      p = x * P;
      if (p % 2 != 0) continue;

      w = p / 2 / 2;
      h = p / 2 - w;
      if (w + h - 1 <= s and s <= w * h) {
        found = true;
        break;
      }
    }
    if (!found) {
      cout << -1 << '\n';
      continue;
    }

    vector dist(w, vector<int>(h, INF));
    queue<pair<int, int>> q;
    auto push = [&](int i, int j, int d) -> void {
      if (i < 0 or i >= w or j < 0 or j >= h) return;
      if (d >= dist[i][j]) return;
      dist[i][j] = d;
      q.push({i, j});
    };
    for (int i = 0; i < w; i++) {
      push(i, i, 0);
      push(i, i + 1, 0);
    }
    vector<pair<int, int>> ans;
    int count = 0;
    while (q.size() > 0) {
      auto [i, j] = q.front();
      q.pop();

      ans.push_back({i, j});
      count++;
      if (count == s) break;

      for (auto [di, dj] :
           (pair<int, int>[]) {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        push(i + di, j + dj, dist[i][j] + 1);
      }
    }

    cout << ans.size() << '\n';
    for (auto [i, j] : ans) {
      cout << i << ' ' << j << '\n';
    }
  }
}