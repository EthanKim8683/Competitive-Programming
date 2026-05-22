#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, Q;
  cin >> N >> M >> Q;

  vector<int> D(N);
  for (auto &e : D) cin >> e;

  vector<int> E(N);
  for (auto &e : E) cin >> e;

  vector<set<int>> adj(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].insert(b);
    adj[b].insert(a);
  }

  int K = sqrt(M);

  set<int> big;
  for (int i = 0; i < N; i++) {
    if (adj[i].size() > K) {
      big.insert(i);
    }
  }

  vector<int> D_ = D, E_ = E;
  for (auto e : big) {
    for (auto b : adj[e]) {
      D_[e] += D[b];
      E_[e] += E[b];
    }
  }

  while (Q--) {
    string t;
    cin >> t;

    if (t == "add") {
      int n;
      string t_;
      int a;
      cin >> n >> t_ >> a;
      a--;

      if (t_ == "desk") {
        for (auto e : big) {
          if (!(e == a or adj[e].contains(a))) continue;
          D_[e] += n;
        }
        D[a] += n;
      } else {
        for (auto e : big) {
          if (!(e == a or adj[e].contains(a))) continue;
          E_[e] += n;
        }
        E[a] += n;
      }
    } else {
      int a;
      cin >> a;
      a--;

      int d, e;
      if (big.contains(a)) {
        d = D_[a];
        e = E_[a];
      } else {
        d = D[a];
        e = E[a];
        for (auto b : adj[a]) {
          d += D[b];
          e += E[b];
        }
      }
      cout << (d > e ? "desks" : d < e ? "monitors" : "same") << '\n';
    }
  }
}