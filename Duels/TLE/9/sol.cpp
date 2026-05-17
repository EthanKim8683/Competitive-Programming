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

  // (( -> 0
  // )) -> 0
  // )( -> 0
  // () -> 1
  //
  // determine 1, and the rest can be determined
  //
  // can we binary search for the first ()? yes
  //
  // (( -> 2
  // )) -> 0
  // )( -> 1
  // () -> 1
  //
  // (( )) (( )) (( -> 5
  // )) )) )) )) )) -> 0
  // )( )) )( )) )( -> 2
  // () )) () )) () -> 3

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto query = [&](vi I) -> int {
      cout << "? " << sz(I);
      for (auto e : I) {
        cout << ' ' << e + 1;
      }
      cout << endl;
      int rv;
      cin >> rv;
      return rv;
    };

    auto answer = [&](string S) -> void { cout << "! " << S << endl; };

    auto check = [&](int x) -> bool {
      vi I(x);
      iota(all(I), 0);
      return query(I) > 0;
    };
    int l = 2, r = N;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    int open, close;
    if (check(l)) {
      open = l - 2;
      close = l - 1;
    } else {
      open = N - 1;
      close = 0;
    }
    string ans;
    for (int i = 0; i < N; i += 2) {
      if (i + 2 <= N) {
        int t =
            query({i, i + 1, close, close, i, i + 1, close, close, i, i + 1});
        if (t == 5) {
          ans += "((";
        } else if (t == 0) {
          ans += "))";
        } else if (t == 2) {
          ans += ")(";
        } else if (t == 3) {
          ans += "()";
        } else {
          assert(false);
        }
      } else {
        int t = query({i, close});
        if (t == 1) {
          ans += "(";
        } else if (t == 0) {
          ans += ")";
        } else {
          assert(false);
        }
      }
    }
    answer(ans);
  }
}
