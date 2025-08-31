#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    int R;
    cin >> R;

    set<pair<int, int>> bad;
    for (int i = 0; i < R; i++) {
      int t, d, coord;
      cin >> t >> d >> coord;

      if (d == 1) {
        bad.insert({coord, t});
      } else {
        bad.insert({N + 1 + coord, t});
      }
    }

    vector dist(N + 1, vector(M + 1, vector<int>(R + 1, INF)));
    queue<tuple<int, int, int>> q;
    auto push = [&](int d, int i, int j, int s) -> void {
      if (i > N or j > M or s > R) return;
      if (bad.contains({i, d + s}) or bad.contains({N + 1 + j, d + s})) return;
      if (d >= dist[i][j][s]) return;
      dist[i][j][s] = d;
      q.push({i, j, s});
    };
    push(0, 0, 0, 0);
    while (q.size() > 0) {
      auto [i, j, s] = q.front();
      q.pop();
      int d = dist[i][j][s];
      push(d + 1, i + 1, j, s);
      push(d + 1, i, j + 1, s);
      push(d, i, j, s + 1);
    }
    int ans = INF;
    for (int i = 0; i <= R; i++) {
      ans = min(ans, dist[N][M][i] + i);
    }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
