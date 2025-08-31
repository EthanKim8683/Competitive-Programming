#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<pair<int, int>> freqs(N);
  for (auto &[l, r] : freqs) {
    cin >> l >> r;
    l--;
  }

  vector<vector<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // https://codeforces.com/edu/course/2/lesson/7/3
}
