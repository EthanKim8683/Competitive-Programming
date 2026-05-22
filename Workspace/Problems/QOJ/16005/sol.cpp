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

const int INF = 1e9;

struct lis {
  vc<pair<int, int>> undos;
  vi dp;
  int i = 0;

  lis(int n) : undos(n), dp(n, INF) {}

  void push(int x) {
    int j = ::lower_bound(all(dp), x) - dp.begin();
    undos[i] = {j, dp[j]};
    dp[j] = x;

    i++;
  }

  void pop() {
    i--;

    auto [j, x] = undos[i];
    dp[j] = x;
  }

  int size() { return i; }

  int get(int i) { return dp[i]; }

  int lower_bound(int x) { return ::lower_bound(all(dp), x) - dp.begin(); }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vi M(N);
  for (auto &e : M) cin >> e;

  lis L(N), R(N);
  int i = N;
  while (i > 0) {
    i--;
    R.push(M[i]);
  }
  while (Q--) {
    char t;
    cin >> t;

    if (t == '>') {
      R.pop();
      L.push(M[i]);
      i++;

    } else if (t == '<') {
      i--;
      L.pop();
      R.push(M[i]);
    } else {
      int v;
      cin >> v;

      R.pop();
      M[i] = v;
      R.push(M[i]);
    }
  }
}
