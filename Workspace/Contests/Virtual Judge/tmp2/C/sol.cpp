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

  // pair b with smallest possible that is good
  //
  // the rest get paired in sorted order
  //
  // they both get paired in sorted order
  //
  // sort both
  //
  // pick min a, and first b greater
  //
  // 2 3 4
  // 1 2 4
  //
  // 2 3 4
  // 2 1 4
  //
  // find the minimum and maximum
  //
  // anything in between is possible?
  //
  // minimum is, for each a, pick min b >= a
  //
  // maximum is, for each b, pick min a > b

  int T;
  cin >> T;

  while (T--) {
    int N, X;
    cin >> N >> X;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;
  }
}
