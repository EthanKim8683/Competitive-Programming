#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // obviously, if the graph is connected and isn't bipartite, Alice can't win
  //
  // there must be at least as many black nodes as white ones
  //
  // Alice can "cheat" by filling single node components, but only if there are
  // an odd number of them
  //
  // if Alice cheats, the graph must be winnable regardless of which node is
  // then turned white/removed
  //
  // if Alice colors a node in a component with size at least 3 (before Bob),
  // she would probably lose
  //
  // if a component has size 6 or more, Alice can't even cheat
  //
  // if a component has size 3 to 5, Alice needs to cheat
  //
  //
}
