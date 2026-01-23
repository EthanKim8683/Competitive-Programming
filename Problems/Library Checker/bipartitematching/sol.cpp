#include <bits/stdc++.h>

#include "ethankim8683/graph.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int L, R, M;
  cin >> L >> R >> M;

  mbm_graph g(L, R);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }

  cout << g.match() << '\n';
  for (auto [c, d] : g.matching()) {
    cout << c << ' ' << d << '\n';
  }
}
