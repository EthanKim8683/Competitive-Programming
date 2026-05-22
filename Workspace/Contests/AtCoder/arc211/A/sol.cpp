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

  // we can put same elements (other than 5) next to each other
  //
  // must have at least A[5] - 1 non-5's
  //
  // if we have just two elements that sum up to 10, get a 5 to put between them
  //
  // otherwise, we can always avoid sum 10

  int T;
  cin >> T;

  while (T--) {
    vi A(9 + 1);
    rep(i, 1, 9 + 1) cin >> A[i];

    if (A[5] > 0) {
      cout << max((A[5] - 1) - (accumulate(A.begin() + 1, A.end(), 0ll) - A[5]),
                  0ll)
           << '\n';
    } else {
      cout << (9 - count(A.begin() + 1, A.end(), 0) == 2 ? 1 : 0) << '\n';
    }
  }
}
