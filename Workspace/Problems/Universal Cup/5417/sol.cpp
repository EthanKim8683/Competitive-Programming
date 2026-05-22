#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;

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

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAXX = 1e9 + (2e5 - 1) * 1e9 + 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 5:20
  // thinking done: 5:23
  // target impl time: 25 min
  // initial impl done: 5:38

  // binary search?
  // merge sort tree

  int N, K, M, C, D;
  cin >> N >> K >> M >> C >> D;
  K--;

  vi A(N);
  for (auto &e : A) cin >> e;

  auto f = [&](int i) -> pii { return {A[i] + i * D, i}; };
  Tree<pii> prefix, infix, suffix;
  rep(i, 0, M) { infix.insert(f(i)); }
  rep(i, M, N) { suffix.insert({A[i], i}); }

  int ans = 0;
  rep(i, 0, N - M + 1) {
    auto count = [&](int x) -> int {
      // A[j] + j * D - i * D + C < x
      // A[j] + j * D < x + i * D - C
      return prefix.order_of_key({x, 0}) +
             infix.order_of_key({x + i * D - C, 0}) +
             suffix.order_of_key({x, 0});
    };
    int l = 0, r = MAXX;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      count(m) <= N - 1 - K ? l = m : r = m - 1;
    }
    chmax(ans, l);

    if (i + M < N) {
      suffix.erase({A[i + M], i + M});
      infix.insert(f(i + M));
      infix.erase(f(i));
      prefix.insert({A[i], i});
    }
  }
  cout << ans << '\n';
}
