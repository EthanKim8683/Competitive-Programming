#pragma GCC optimize("trapv")
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
typedef vector<int> vi;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  auto read_tree = [&]() -> pair<int, map<int, vi>> {
    string line;
    getline(cin, line);
    stringstream sin(line);

    map<int, vi> adj;
    auto read_node = [&](auto self) -> int {
      int r;
      sin >> r;

      char c;
      while (sin >> c) {
        if (c != '(') break;
        adj[r].pb(self(self));
      }
      sort(all(adj[r]));
      return r;
    };
    return {read_node(read_node), adj};
  };
  cout << (read_tree() == read_tree() ? "Yes" : "No");
}