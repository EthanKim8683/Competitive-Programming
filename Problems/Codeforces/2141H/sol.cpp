#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<set<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int x, y;
    cin >> x >> y;
    x--, y--;
    adj[x].insert(y);
    adj[y].insert(x);
  }

  set<int> unseen;
  for (int i = 0; i < N; i++) {
    unseen.insert(i);
  }
  auto dfs = [&](auto self, int a) -> int {
    int rv = 1;
    unseen.erase(a);
    auto it = unseen.begin();
    while (it != unseen.end()) {
      int b = *it;
      if (adj[a].contains(b)) {
        it++;
        continue;
      }
      rv += self(self, b);
      it = unseen.upper_bound(b);
    }
    return rv;
  };
  auto it = unseen.begin();
  int ans = INF;
  while (it != unseen.end()) {
    int r = *it, size = dfs(dfs, r);
    ans = min(ans, size);
    it = unseen.upper_bound(r);
  }
  if (ans == 1) {
    cout << "0 0\n";
  } else {
    cout << ans - 1 << ' ' << N - 1 << '\n';
  }
}
