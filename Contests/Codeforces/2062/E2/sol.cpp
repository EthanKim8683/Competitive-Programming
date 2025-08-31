#include "ethankim8683/euler_tour.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> W(N);
    for (auto &e : W)
      cin >> e;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<vector<int>> by_W(N + 1);
    for (int i = 0; i < N; i++) {
      by_W[W[i]].push_back(i);
    }

    euler_tour et(adj, 0);
    for (int i = N; i >= 1; i--) {
    }
  }
}
