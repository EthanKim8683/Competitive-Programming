#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<array<int, 4>> pairs(N);
    for (auto &[r1, c1, r2, c2] : pairs) {
      cin >> r1 >> c1 >> r2 >> c2;
      r1--, c1--, r2--, c2--;
    }

    // the division just needs to be symmetrical and span the entire grid; if
    // they aren't connected, we can erase the problematic dividers and still
    // have an answer
    //
    // effectively, we just want a path from the center to a boundary
    //
    // we can use BFS with edge weights

    map<tuple<int, int, int, int>, int> costs;
    for (auto [r1, c1, r2, c2] : pairs) {
      if (r1 != r2) {
        r1 = r2 = max(r1, r2);
        c2++;
      } else {
        c1 = c2 = max(c1, c2);
        r1++;
      }

      costs[make_tuple(r1, c1, r2, c2)]++;
      costs[make_tuple(r2, c2, r1, c1)]++;
    }

    vector dist(K + 1, vector<int>(K + 1, INF));
    priority_queue<tuple<int, int, int>> pq;
    int ans = INF;
    auto push = [&](int d, int i, int j) -> void {
      if (i < 0 or i > K or j < 0 or j > K) return;
      if (d >= dist[i][j]) return;
      if (i == 0 or i == K or j == 0 or j == K) {
        ans = min(ans, d);
      }
      dist[i][j] = d;
      pq.push({-d, i, j});
    };
    push(0, K / 2, K / 2);
    while (pq.size() > 0) {
      auto [d, i, j] = pq.top();
      pq.pop();
      if ((d = -d) != dist[i][j]) continue;
      for (auto [di, dj] :
           (pair<int, int>[]) {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        int i2 = i + di, j2 = j + dj;
        push(d + costs[make_tuple(i, j, i2, j2)] +
                 costs[make_tuple(K - i, K - j, K - i2, K - j2)],
             i2, j2);
      }
    }
    cout << N - ans << '\n';
  }
}
