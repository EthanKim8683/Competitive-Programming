#include <bits/stdc++.h>

using namespace std;

// My first DMOJ contest! Hope I do alright!
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<string> adj(N);
  for (auto &r : adj) cin >> r;

  // solve for max cc's
  // solve on mostly fully connected graph

  if (K == 1) {
    pair<int, int> ans = {-1, -1};
    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        if (adj[i][j] == '0') {
          ans = {i, j};
          goto FOUND1;
        }
      }
    }
  FOUND1:
    if (ans == make_pair(-1, -1)) {
      cout << "IMPOSSIBLE";
      exit(0);
    }
    auto [a, b] = ans;
    for (int i = 0; i < N; i++) {
      if (adj[a][i] == '1') {
        adj[a][i] = '2';
        adj[i][a] = '2';
      }
    }
    cout << "POSSIBLE\n";
    for (auto r : adj) {
      cout << r << '\n';
    }
  } else {
    tuple<int, int, int, int> ans = {-1, -1, -1, -1};
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          for (int l = 0; l < N; l++) {
            if (i == j or i == k or i == l or j == k or j == l or k == l)
              continue;
            if (adj[i][j] == '0' and adj[i][k] == '0' and adj[i][l] == '0' and
                adj[j][k] == '0' and adj[j][l] == '0' and adj[k][l] == '0') {
              ans = {i, j, k, l};
            }
          }
        }
      }
    }
  FOUND2:
    if (ans == make_tuple(-1, -1, -1, -1)) {
      cout << "IMPOSSIBLE";
      exit(0);
    }
    auto [a, b, c, d] = ans;
    for (int i = 0; i < N; i++) {
      if (adj[a][i] == '1') {
        adj[a][i] = '2';
        adj[i][a] = '2';
      }
      if (adj[c][i] == '1') {
        adj[c][i] = '2';
        adj[i][c] = '2';
      }
    }
    cout << "POSSIBLE\n";
    for (auto r : adj) {
      cout << r << '\n';
    }
  }
}
