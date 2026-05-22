#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<bool> full(K, false);
  vector<set<int>> adj(K);
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    if (a == b) {
      full[a] = true;
    } else {
      adj[a].insert(b);
      adj[b].insert(a);
    }
  }
}