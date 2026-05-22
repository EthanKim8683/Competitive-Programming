#include <bits/stdc++.h>

#include "ethankim8683/trees.hpp"

using namespace std;

using i64 = long long;

const i64 BASE = 6969;
const i64 MOD = (1ll << 61) - 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj1(N);
    for (int i = 0; i < N - 1; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj1[a].push_back(b);
      adj1[b].push_back(a);
    }

    vector<vector<int>> adj2(N);
    for (int i = 0; i < N - 1; i++) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj2[a].push_back(b);
      adj2[b].push_back(a);
    }

    cout << (tree_hash(adj1, 0) == tree_hash(adj2, 0) ? "YES" : "NO") << '\n';
  }
}
