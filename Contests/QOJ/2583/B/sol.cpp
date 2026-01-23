#pragma GCC optimize("Ofast,unroll-loops")
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

  int N, K, M, C;
  cin >> N >> K >> M >> C;

  vi A(M);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  vi P(N, 0);
  map<int, set<int>> by_P;
  rep(i, 0, N) { by_P[P[i]].insert(i); }
  auto sit = [&](int i) -> void {
    by_P[P[i]].erase(i);
    if (by_P[P[i]].empty()) {
      by_P.erase(P[i]);
    }
    P[i]++;
    if (P[i] < K) {
      by_P[P[i]].insert(i);
    }
  };

  auto better = [&](tuple<int, int, int> a, tuple<int, int, int> b) -> bool {
    auto [x1, y1, z1] = a;
    auto [x2, y2, z2] = b;
    if (y1 >= y2 + 32) return false;
    if (y2 >= y1 + 32) return true;
    x1 <<= max(y2 - y1, 0ll);
    x2 <<= max(y1 - y2, 0ll);
    return pii{x1, -z1} > pii{x2, -z2};
  };

  rep(i, 0, M) {
    tuple<int, int, int> best = {0, INF, INF};
    int j = 0;
    for (auto &[p, R] : by_P) {
      if (j == 32) break;
      j++;

      auto it = R.lower_bound(A[i]);
      pii nearest = {INF, -1};
      if (it != R.end()) {
        int k = *it;
        chmin(nearest, pii{k - A[i], k});
      }
      if (it != R.begin()) {
        int k = *prev(it);
        chmin(nearest, pii{A[i] - k, k});
      }

      auto [d, k] = nearest;
      tuple<int, int, int> cost = {C - d, p, k};
      if (better(cost, best)) {
        best = cost;
      }
    }

    auto [c, p, k] = best;
    cout << k + 1 << ' ';
    sit(k);
  }
}
