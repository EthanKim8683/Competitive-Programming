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

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    if (N % 2 == 1) {
      rep(i, 0, N) { cout << N - i << ' '; }
      cout << '\n';
      continue;
    }

    // subtract index and mod N -> all diff numbers
    //
    // 4 1 3 5 2
    // 3 4 0 1 2
    //
    // all even, can make pairs odd
    //
    // idk just guess for now

    cout << "-1\n";
  }
}
