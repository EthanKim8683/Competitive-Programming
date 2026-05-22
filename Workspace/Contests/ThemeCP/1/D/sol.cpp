#include <bits/stdc++.h>

#include "ethankim8683/graph.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<string> access(N);
  for (auto &e : access) cin >> e;

  vector<string> sets(M, "");
  for (auto s : access) {
    for (int i = 0; i < M; i++) {
      sets[i] += s[i];
    }
  }

  vector<string> usets = sets;
  sort(usets.begin(), usets.end());
  usets.erase(unique(usets.begin(), usets.end()), usets.end());
  int M_ = usets.size();

  auto is_subset = [&](string a, string b) -> bool {
    for (int i = 0; i < N; i++) {
      if (a[i] > b[i]) return false;
    }
    return true;
  };

  std::vector<std::vector<int>> adj(M_);
  for (int i = 0; i < M_; i++) {
    for (int j = 0; j < M_; j++) {
      if (i == j) continue;
      if (is_subset(usets[i], usets[j])) {
        adj[j].push_back(i);
      }
    }
  }
  auto chains = get_chains(adj);

  int K = chains.size();
  vector<int> dgroups(M), dlevels(M);
  vector plevels(N, vector<int>(K, 0));
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < K; j++) {
      for (int k = 0; k < chains[j].size(); k++) {
        if (usets[chains[j][k]] == sets[i]) {
          dgroups[i] = j;
          dlevels[i] = k + 1;
          goto FOUND;
        }
      }
    }
  FOUND:
    for (int j = 0; j < N; j++) {
      if (sets[i][j] == '1') {
        int &t = plevels[j][dgroups[i]];
        t = max(t, dlevels[i]);
      }
    }
  }

  cout << K << '\n';
  for (auto e : dgroups) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
  for (auto e : dlevels) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
  for (auto r : plevels) {
    for (auto e : r) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
/*

*/
