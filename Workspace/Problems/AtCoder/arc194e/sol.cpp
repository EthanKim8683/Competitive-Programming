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

  // 000111001
  // 000110011
  // 000100111
  // 000001111
  //
  // if Y = 1, the 1's would just have to match deltas modulo X
  //
  // if Y > 1, groups of Y 1's would have to match deltas modulo X in
  // 1-delimited ranges
  //
  // 7 2 2
  // 0011100
  // 0010011
  // 1100100
  //
  // 1's modulo X are the same
  // 0's modulo Y are the same
  //
  //

  int N, X, Y;
  cin >> N >> X >> Y;

  string S;
  cin >> S;

  string T;
  cin >> T;

  auto key = [&](string S) -> string {

  };
  cout << (key(S) == key(T) ? "Yes" : "No") << '\n';
}
