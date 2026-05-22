#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;
    int logN = __lg(2 * N - 1);

    vector has(2, vector<bool>(1 << logN, false));
    int ans = 0;
    auto insert = [&](int t, int x0) -> void {
      auto dfs = [&](auto self, int x) -> void {
        if (has[t][x]) return;
        has[t][x] = true;

        if (has[!t][x]) {
          ans = max(ans, x);
        }

        for (int i = 0; i < logN; i++) {
          if ((x >> i & 1) == 1) {
            self(self, x ^ 1 << i);
          }
        }
      };
      dfs(dfs, x0);
    };
    while (Q--) {
      int e;
      cin >> e;
      int v = (e + ans) % N;

      insert(0, v);
      insert(1, v ^ ((1 << logN) - 1));

      cout << ans << ' ';
    }
    cout << '\n';
  }
}
