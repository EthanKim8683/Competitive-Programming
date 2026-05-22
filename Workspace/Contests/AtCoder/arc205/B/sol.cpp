#include <bits/stdc++.h>

#include <numeric>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> adj(N, 0);
  for (int i = 0; i < M; i++) {
    int U, V;
    cin >> U >> V;
    U--, V--;
    (adj[U] += 1) %= 2;
    (adj[V] += 1) %= 2;
  }

  for (int i = 0; i < N; i++) {
    adj[i] += (N - 1 - adj[i]) / 2 * 2;
  }
  cout << accumulate(adj.begin(), adj.end(), 0ll) / 2;
}