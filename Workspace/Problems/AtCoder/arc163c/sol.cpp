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

const int MAXN = 500;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // 0/1           1/1
  //        1/2
  //    1/3     2/3
  //  1/4 2/5 3/5 3/4
  //
  //  1/x-1/(x+1)
  // =((x+1)-x)/(x(x+1))
  // =1/(x(x+1))
  //
  // split the last one if end on a bad fraction
  //
  //  1/(x(x+1))
  // =1/(x(x+x+1))+1/((x+x+1)(x+1))
  // =((x+1)+x)/(x(x+1)(x+x+1))
  // =1/(x(x+1))

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    if (N == 2) {
      cout << "No\n";
      continue;
    }

    vi ans;
    rep(i, 1, N) { ans.pb(i * (i + 1)); }
    if (binary_search(all(ans), N)) {
      ans.pop_back();
      ans.pop_back();
      ans.pb((N - 2) * (N - 2 + N - 1));
      ans.pb((N - 2 + N - 1) * (N - 1));
      ans.pb(N - 1);
    } else {
      ans.pb(N);
    }
    cout << "Yes\n";
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';

    // long double sum = 0;
    // for (auto e : ans) {
    //   sum += 1.L / e;
    // }
    // cerr << sum << '\n';
  }
}
