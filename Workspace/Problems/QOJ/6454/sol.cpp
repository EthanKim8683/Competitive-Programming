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

struct top_k {
  int k, sum;
  multiset<int> top, bottom;

  top_k() : k(0), sum(0) {}

  void set_k(int k2) {
    k = max(k2, 0ll);
    fix();
  }

  int is_top_full() { return sz(top) == k; }

  int get_sum() { return sum; }

  void insert(int x) {
    sum += x;
    top.insert(x);
    fix();
  }

  void erase(int x) {
    if (bottom.contains(x)) {
      bottom.erase(bottom.find(x));
    } else {
      sum -= x;
      top.erase(top.find(x));
      fix();
    }
  }

  void fix() {
    while (sz(top) < k and sz(bottom) > 0) {
      auto it = bottom.begin();
      sum += *it;
      top.insert(*it);
      bottom.erase(it);
    }
    while (sz(top) > k) {
      auto it = prev(top.end());
      bottom.insert(*it);
      sum -= *it;
      top.erase(it);
    }
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // k = (ps + ceil(-psmin / 2) * 2) / 2 + ceil(-psmin / 2) * 2
  //   = ps / 2 + ceil(-psmin / 2) * 2
  // K > k
  //
  // psmin, ps, cost

  // given psmin, find min cost to get k > K

  int N, K;
  cin >> N >> K;

  string S;
  cin >> S;

  vi C(N);
  for (auto &e : C) cin >> e;

  int base = 0;
  rep(i, 0, N) {
    if (C[i] > 0) continue;
    base += C[i];
    S[i] ^= 1;
    C[i] *= -1;
  }

  if (N % 2 == 1) {
    cout << base << '\n';
    exit(0);
  }

  top_k tk;
  int ps = 0;
  rep(i, 0, N) {
    if (S[i] == '(') {
      ps += 1;
    } else {
      ps -= 1;
      tk.insert(C[i]);
    }
  }

  int psmin = 0, ans = INF;
  rep(i, 0, N + 1) {
    int k = ps / 2 - psmin;
    if (i % 2 == 1) {
      k += 1;
    }
    tk.set_k(K - k + 1);
    if (tk.is_top_full()) {
      chmin(ans, base + tk.get_sum());
    }

    if (i < N) {
      if (S[i] == '(') {
        psmin += 1;
        tk.insert(C[i]);
      } else {
        psmin -= 1;
        tk.erase(C[i]);
      }
    }
  }
  if (ans == INF) {
    cout << "?\n";
  } else {
    cout << ans << '\n';
  }
}
