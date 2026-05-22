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

  // at most K * K * 4 ifs

  // if f(x, y), add an edge from x to y
  // reflexive: trivial
  // symmetric: trivial
  // transitive: for all x, y, if there is no direct edge from x to y and the
  // shortest path from x to y has two edges, contribute the number of shortest
  // paths from x to y

  int N, K;
  cin >> N >> K;
}
