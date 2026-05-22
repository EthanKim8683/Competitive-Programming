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
  cin.exceptions(cin.failbit);

  string N, M;
  cin >> N >> M;

  set<string> seen;
  rep(i, 1, 101 + 1) {
    if (seen.contains(N)) break;
    seen.insert(N);

    if (i == 101) {
      cout << "I'm bored";
      exit(0);
    }

    if (N == M) {
      cout << i;
      exit(0);
    }

    string N_;
    rep(j, '0', '9' + 1) {
      int n = count(all(N), j);
      if (n == 0) continue;
      N_ += to_string(n) + (char) j;
    }
    N = N_;
  }
  cout << "Does not appear";
}