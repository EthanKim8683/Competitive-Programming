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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vi A(N);
  for (auto &e : A) {
    cin >> e;
    if (e != -1) {
      e--;
    }
  }

  // while (Q--) {
  //   int l, r;
  //   cin >> l >> r;
  //   l--;

  //   bool ans = true;
  //   map<int, int> ranges;
  //   rep(i, l, r) {
  //     if (A[i] == -1) continue;
  //     int k = i - l + A[i];
  //     chmax(ranges[k], abs(k - 2 * (i - l)));
  //   }
  //   int p = 0;
  //   for (auto [k, d] : ranges) {
  //     int f = k - d, s = k + d;
  //     ans = ans and p <= f;
  //     p = s + 1;
  //   }
  //   ans = ans and p < 2 * (r - l);
  //   cout << (ans ? "YES" : "NO") << '\n';
  // }

  // while (Q--) {
  //   int l, r;
  //   cin >> l >> r;
  //   l--;

  //   bool ans = true;
  //   map<int, int> ranges;
  //   rep(i, l, r) {
  //     if (A[i] == -1) continue;
  //     chmax(ranges[A[i] + i], abs(A[i] - i + l));
  //   }
  //   int x = l;
  //   for (auto [k, d] : ranges) {
  //     int f = k - d, s = k + d;
  //     ans = ans and x <= f;
  //     x = s + 1;
  //   }
  //   ans = ans and x < 2 * r - l;
  //   cout << (ans ? "YES" : "NO") << '\n';
  // }

  // adjacent ones are valid within a certain range of l's
  //
  // some kind of range query data structure

  vc<pii> queries(Q);
  for (auto &[l, r] : queries) {
    cin >> l >> r;
    l--;
  }
}
