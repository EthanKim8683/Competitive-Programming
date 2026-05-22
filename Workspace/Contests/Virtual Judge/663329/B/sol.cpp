#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> coords(N);
  for (auto &[x, y] : coords) {
    cin >> x >> y;
  }

  // if n > 6, there must be a triple of colinear points

  vector<bool> popped(N, false);
  int triples = 0, searches = 0;
  for (int i = 0; i < N; i++) {
    if (!popped[i]) {
      searches++;
      if (searches > 10) break;
    }

    auto get_ratio = [&](int j) -> pair<int, int> {
      auto [x1, y1] = coords[i];
      auto [x2, y2] = coords[j];
      int dx = x2 - x1, dy = y2 - y1;
      int g = gcd(abs(dx), abs(dy));
      dx /= g;
      dy /= g;
      if (dy < 0 or (dy == 0 and dx < 0)) {
        dx = -dx;
        dy = -dy;
      }
      return {dx, dy};
    };

    map<pair<int, int>, int> seen;
    for (int j = 0; j < N; j++) {
      if (j == i) continue;
      if (popped[i] and popped[j]) continue;

      auto ratio = get_ratio(j);
      if (seen.contains(ratio)) {
        popped[i] = true;
        for (int k = 0; k < N; k++) {
          if (k == i) continue;
          if (popped[k]) continue;

          auto ratio_ = get_ratio(k);
          if (ratio_ == ratio) {
            popped[k] = true;
          }
        }

        searches = 0;
        triples++;
        if (triples == 3) {
          goto SKIP;
        }
      } else {
        seen[ratio] = j;
      }
    }
  }
SKIP:

  int remaining = 0;
  for (auto e : popped) {
    if (e) continue;
    remaining++;
  }

  cout << ((remaining + 1) / 2 <= 3 - triples ? "possible" : "impossible");
}