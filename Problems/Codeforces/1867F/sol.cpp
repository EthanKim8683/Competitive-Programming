#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<vector<int>> adj(N);
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // once you make a subtree that isn't isomorphic, add the remaining the nodes
  // on top
  //
  // find a tree with the least nodes that doesn't occur as a subtree in G
  //
  // according to OEIS, there can be at most 18 nodes in this tree:
  // https://oeis.org/A000055
  //
  // to construct a tree with k nodes that doesn't occur as a subtree of G, we
  // can try, for each node of each subtree, adding an adjacent node and
  // checking if it exists in G
}
