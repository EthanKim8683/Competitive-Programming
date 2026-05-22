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

const int INF = 1e9;

template <class S, auto op, auto e>
struct segtree {
  int n;
  vi d;
  segtree(int n) : n(n), d(2 * n, e()) {}
  void set(int i, S x) {
    for (d[i += n] = x; i >>= 1;) {
      d[i] = op(d[i << 1], d[i << 1 | 1]);
    }
  }
  S prod(int l, int r) {
    S lv = e(), rv = e();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, d[l++]);
      if (r & 1) rv = op(d[--r], rv);
    }
    return op(lv, rv);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // store min right bound for left bounds
  // store max left bound for right bounds
  // take sum of size - 1 for all teams outside

  int N, Q;
  cin >> N >> Q;

  vi A(N);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  vc<set<int>> indices(N);
  using S1 = int;
  auto op1 = [&](S1 a, S1 b) -> S1 { return min(a, b); };
  auto e1 = [&]() -> S1 { return INF; };
  segtree<S1, op1, e1> st1(N);
  using S2 = int;
  auto op2 = [&](S2 a, S2 b) -> S2 { return max(a, b); };
  auto e2 = [&]() -> S2 { return -INF; };
  segtree<S2, op2, e2> st2(N);
  using S3 = int;
  auto op3 = [&](S3 a, S3 b) -> S3 { return max(a, b); };
  auto e3 = [&]() -> S3 { return -INF; };
  segtree<S3, op3, e3> st3(N);
  using S4 = int;
  auto op4 = [&](S4 a, S4 b) -> S4 { return a + b; };
  auto e4 = [&]() -> S4 { return 0; };
  segtree<S4, op4, e4> st4(N);
  auto erase_player = [&](int i) -> void {
    int t = A[i];

    auto it = indices[t].find(i);
    int j = -1, k = -1;
    if (it != indices[t].begin()) {
      j = *prev(it);
    }
    if (next(it) != indices[t].end()) {
      k = *next(it);
    }

    if (j != -1) {
      st1.set(j, e1());
      st2.set(i, e2());
    }
    if (k != -1) {
      st1.set(i, e1());
      st2.set(k, e2());
    }
    if (j != -1 and k != -1) {
      st1.set(j, k);
      st2.set(k, j);
    }

    indices[t].erase(i);
  };
  auto insert_player = [&](int i) -> void {
    int t = A[i];

    indices[t].insert(i);

    auto it = indices[t].find(i);
    int j = -1, k = -1;
    if (it != indices[t].begin()) {
      j = *prev(it);
    }
    if (next(it) != indices[t].end()) {
      k = *next(it);
    }

    if (j != -1 and k != -1) {
      st1.set(j, e1());
      st2.set(k, e2());
    }
    if (j != -1) {
      st1.set(j, i);
      st2.set(i, j);
    }
    if (k != -1) {
      st1.set(i, k);
      st2.set(k, i);
    }
  };
  auto erase_team = [&](int t) -> void {
    if (indices[t].empty()) return;

    int l = *indices[t].begin(), r = *indices[t].rbegin();
    st3.set(l, e3());
    st4.set(l, e4());
    st4.set(r, e4());
  };
  auto insert_team = [&](int t) -> void {
    if (indices[t].empty()) return;

    int l = *indices[t].begin(), r = *indices[t].rbegin(),
        n = indices[t].size();
    st3.set(l, r);
    st4.set(l, n - 1);
    st4.set(r, n - 1);
  };
  rep(i, 0, N) { insert_player(i); }
  rep(i, 0, N) { insert_team(i); }

  while (Q--) {
    int s;
    cin >> s;

    if (s == 1) {
      int t, i;
      cin >> t >> i;
      t--, i--;

      int t2 = A[i];
      if (t == t2) continue;

      erase_team(t);
      erase_team(t2);
      erase_player(i);
      A[i] = t;
      insert_player(i);
      insert_team(t);
      insert_team(t2);
    } else {
      int t;
      cin >> t;
      t--;

      if (indices[t].empty()) {
        cout << -1 << '\n';
        continue;
      }

      int l = *indices[t].begin(), r = *indices[t].rbegin();
      if (l > st1.prod(0, l) or r < st2.prod(r + 1, N) or r < st3.prod(0, l)) {
        cout << -1 << '\n';
        continue;
      }

      cout << st4.prod(0, l) + st4.prod(r + 1, N) << '\n';
    }
  }
}
