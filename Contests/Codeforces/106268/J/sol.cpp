#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<string> grid(N);
    for (auto &e : grid) cin >> e;

    auto transpose = [&](vector<string> &g) -> void {
      vector<string> t(g[0].size());
      for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
          t[j] += g[i][j];
        }
      }
      g = t;
    };

    auto alternate1 = [&](string &s, char c1, char c2, bool apply) -> bool {
      for (int i = 0; i < s.size(); i++) {
        char c = i % 2 == 0 ? c1 : c2;
        if (s[i] == '?') {
          if (apply) {
            s[i] = c;
          }
        } else {
          if (s[i] != c) {
            assert(!apply);
            return false;
          }
        }
      }
      return true;
    };

    auto alternate2 = [&](vector<string> &g, char c1, char c2, char c3, char c4,
                          bool apply) -> bool {
      for (int i = 0; i < g.size(); i++) {
        char c5 = i % 2 == 0 ? c1 : c2, c6 = i % 2 == 0 ? c3 : c4;
        if (alternate1(g[i], c5, c6, false)) {
          if (apply) {
            alternate1(g[i], c5, c6, true);
          }
        } else if (alternate1(g[i], c6, c5, false)) {
          if (apply) {
            alternate1(g[i], c6, c5, true);
          }
        } else {
          assert(!apply);
          return false;
        }
      }
      return true;
    };

    auto alternate3 = [&](vector<string> &g, bool apply) -> bool {
      if (alternate2(g, 'C', 'C', 'I', 'P', false)) {
        if (apply) {
          alternate2(g, 'C', 'C', 'I', 'P', true);
        }
      } else if (alternate2(g, 'C', 'C', 'P', 'I', false)) {
        if (apply) {
          alternate2(g, 'C', 'C', 'P', 'I', true);
        }
      } else if (alternate2(g, 'I', 'C', 'P', 'C', false)) {
        if (apply) {
          alternate2(g, 'I', 'C', 'P', 'C', true);
        }
      } else if (alternate2(g, 'C', 'I', 'C', 'P', false)) {
        if (apply) {
          alternate2(g, 'C', 'I', 'C', 'P', true);
        }
      } else {
        assert(!apply);
        return false;
      }
      return true;
    };

    auto alternate4 = [&](vector<string> &g, bool apply) -> bool {
      if (alternate3(g, false)) {
        if (apply) {
          alternate3(g, true);
        }
      } else {
        auto t = g;
        transpose(t);
        if (alternate3(t, false)) {
          if (apply) {
            transpose(g);
            alternate3(g, true);
            transpose(g);
          }
        } else {
          assert(!apply);
          return false;
        }
      }
      return true;
    };

    if (alternate4(grid, false)) {
      alternate4(grid, true);
      cout << "yes\n";
      for (auto e : grid) {
        cout << e << '\n';
      }
    } else {
      cout << "no\n";
    }
  }
}
