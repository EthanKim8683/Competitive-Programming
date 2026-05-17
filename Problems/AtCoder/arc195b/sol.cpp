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

  // savings per sum

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(N);
  for (auto &e : B) cin >> e;

  unordered_map<int, int> counts1, counts2;
  int replace1 = 0, replace2 = 0;
  for (auto e : A) {
    if (e == -1) {
      replace1 += 1;
    } else {
      counts1[e] += 1;
    }
  }
  for (auto e : B) {
    if (e == -1) {
      replace2 += 1;
    } else {
      counts2[e] += 1;
    }
  }
  unordered_map<int, int> savings;
  for (auto [k1, count1] : counts1) {
    for (auto [k2, count2] : counts2) {
      savings[k1 + k2] += min(count1, count2);
    }
  }
  int kmin = 0;
  chmax(kmin, *max_element(all(A)));
  chmax(kmin, *max_element(all(B)));
  bool ok = N <= replace1 + replace2;
  for (auto [k, sum] : savings) {
    if (k < kmin) continue;
    ok = ok or N - sum <= replace1 + replace2;
  }
  cout << (ok ? "Yes" : "No") << '\n';
}
