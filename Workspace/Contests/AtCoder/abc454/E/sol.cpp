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
    int N, A, B;
    cin >> N >> A >> B;
    A--, B--;

    if (N % 2 != 0 or (A + B) % 2 != 1) {
      cout << "No\n";
      continue;
    }

    cout << "Yes\n";
    if (B % 2 == 0) {
      rep(i, 0, B) {
        rep(j, 0, N - 1) { cout << (i % 2 == 0 ? 'D' : 'U'); }
        cout << 'R';
      }
      rep(i, 0, A) {
        cout << (i % 2 == 0 ? 'R' : 'L');
        cout << (B % 2 == 0 ? 'D' : 'U');
      }
      rep(i, A + 1, N) {
        cout << (B % 2 == 0 ? 'D' : 'U');
        cout << (i % 2 == 0 ? 'L' : 'R');
      }
      rep(i, B + 2, N) {
        cout << 'R';
        rep(j, 0, N - 1) { cout << (i % 2 == 0 ? 'U' : 'D'); }
      }
    } else {
      rep(i, 0, B - 1) {
        rep(j, 0, N - 1) { cout << (i % 2 == 0 ? 'D' : 'U'); }
        cout << 'R';
      }
      rep(i, 0, A) {
        cout << (i % 2 == 0 ? 'R' : 'L');
        cout << (B % 2 == 0 ? 'U' : 'D');
      }
      rep(i, A + 1, N) {
        cout << (B % 2 == 0 ? 'U' : 'D');
        cout << (i % 2 == 0 ? 'L' : 'R');
      }
      rep(i, B + 1, N) {
        cout << 'R';
        rep(j, 0, N - 1) { cout << (i % 2 == 0 ? 'U' : 'D'); }
      }
    }
    cout << '\n';
  }
}
