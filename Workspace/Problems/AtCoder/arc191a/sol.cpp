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

  int N, M;
  cin >> N >> M;

  string S;
  cin >> S;

  string T;
  cin >> T;

  auto use = [&](string t) -> string {
    sort(all(t));
    reverse(all(t));
    string rv = S;
    int i = 0;
    for (auto &e : rv) {
      if (i == sz(t)) break;
      if (e >= t[i]) continue;
      e = t[i];
      i++;
    }
    return rv;
  };
  auto ans = use(T);
  if (find(all(ans), T.back()) == ans.end()) {
    ans = use(T.substr(0, M - 1)).substr(0, N - 1) + T.back();
  }
  cout << ans << '\n';
}
