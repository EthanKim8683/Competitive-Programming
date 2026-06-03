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

  // i -> next i+1 is at same index
  //
  // if i+1 is not at same index, go until first i+1

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    int ans = 0;
    // max ub inclusive
    vi next1(N + 2, N), next2(N + 2, N), ub(N + 1, N);
    for (int i = N - 1; i >= 0; i--) {
      if (A[i] == B[i]) {
        if (next1[A[i] + 1] == next2[A[i] + 1]) {
          ub[i] = ub[next1[A[i] + 1]];
        }
      }
      if (next1[1] == next2[1]) {
        ans += ub[next1[1]] - i;
      } else {
        ans += min(next1[1], next2[1]) - i;
      }
      next1[A[i]] = i;
      next2[B[i]] = i;
    }
    cout << ans << '\n';
  }
}
