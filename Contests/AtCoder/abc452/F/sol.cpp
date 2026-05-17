#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/fenwicktree.hpp"
using namespace atcoder;

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

  // two pointers
  // lb: gt -> advance
  // ub: ge -> advance

  int N, K;
  cin >> N >> K;

  vi P(N);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  auto solve = [&](auto cmp) -> int {
    fenwick_tree<int> ft(N);
    int rv = 0, sum = 0, j = 0;
    rep(i, 0, N) {
      sum += ft.sum(P[i] + 1, N);
      ft.add(P[i], 1);
      while (j < i + 1 and cmp(sum, K)) {
        ft.add(P[j], -1);
        sum -= ft.sum(0, P[j]);
        j++;
      }
      rv += j;
    }
    return rv;
  };
  cout << solve([&](int a, int b) -> bool { return a >= b; }) -
              solve([&](int a, int b) -> bool { return a > b; })
       << '\n';
}
