#ifndef L
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

const int MAXK = 60;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vector<pair<int, int>> sums(MAXK + 1);
  sums[0] = {0, 0};
  for (int i = 0; i < MAXK; i++) {
    auto [a, b] = sums[i];
    if (i % 2 == 0) {
      a += 1 << i;
    } else {
      b += 1 << i;
    }
    sums[i + 1] = {a, b};
  }

  int T;
  cin >> T;

  while (T--) {
    int A, B;
    cin >> A >> B;

    auto check = [&](int x) -> bool {
      auto [a, b] = sums[x];
      return (a <= A and b <= B) or (b <= A and a <= B);
    };
    int l = 0, r = MAXK;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << l << '\n';
  }
}
