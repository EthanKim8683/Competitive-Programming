#include <iterator>
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

int dp[155][36];

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string init;
  cin >> init;

  int n = sz(init);

  vi sizes(n);
  rep(i, 0, n) cin >> sizes[i];

  int d;
  cin >> d;
  vi ds(d);
  rep(i, 0, d) {
    int u;
    cin >> u;
    ds[i] = u - 1;
  }

  string create;
  cin >> create;

  map<char, int> counts;
  map<char, int> costs;

  // hack to init entries of map
  string sort = "AEIOU";
  for (char c : sort) counts[c] = 0, costs[c] = 0;

  for (char c : create) counts[c]++;
  rep(q, 0, n) {
    char c = init[q];
    counts[c]++;
    costs[c] += sizes[q];
    // cerr << " size " << q << " = " << q << endl;
  }

  for (int x : ds) {
    counts[init[x]]--;
    costs[init[x]] -= sizes[x];
    init[x] = 'X';
  }

  vi cv;
  for (auto [k, v] : counts) {
    cv.pb(v);
    // cerr << " count of " << k << " = " << v << " cost = " << costs[k] <<
    // endl;
  }
  vi costv;
  for (auto [_, v] : costs) costv.pb(v);

  memset(dp, 0x7f, sizeof dp);
  dp[0][0] = 0ll;

  for (int i = 0; i < n; ++i) {
    // build new one
    rep(m, 0, 32) {
      int curr = dp[i][m];
      dp[i + 1][m] = min(dp[i + 1][m], curr);
      rep(q, 0, 5) {
        if (!(m & (1ll << q))) {
          if (cv[q] + i <= n) {
            int ip = i + cv[q];
            int mp = m | (1ll << q);

            // build at this index
            // cost = sum of the costs - the ones i can keep
            int raw = costv[q];
            rep(j, 0, cv[q]) {
              if (init[i + j] == sort[q]) {
                raw -= sizes[i + j];
              }
            }
            // cerr << "org = " << costv[q] << " raw cost = " << raw
            //  << " to build " << sort[q] << " at " << i << endl;
            dp[ip][mp] = min(dp[ip][mp], raw + curr);
          }
        }
      }
    }
  }

  int final = dp[n][(1ll << 5) - 1];
  cout << final << endl;
}