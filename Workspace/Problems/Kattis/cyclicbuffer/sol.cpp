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

const int INF = 1e18;

struct RURQ {
  using T = tuple<int, int, int>;
  using S = tuple<bool, int, int>;
  T e = {-1, 0, 0};
  S id = {false, INF, INF};
  T op(T u, T v) {
    if (u == e) return v;
    if (v == e) return u;
    return e;
  }
  T use(T u, S v) {
    auto [i, a1, b1] = u;
    auto [r, a2, b2] = v;
    if (r) return {i, a2, b2};
    return {i, min(a1, a2), min(b1, b2)};
  }
  S lazyop(S u, S v) {
    auto [r1, a1, b1] = u;
    auto [r2, a2, b2] = v;
    if (r2) return v;
    return {r1, min(a1, a2), min(b1, b2)};
  }
  int logn, n;
  vc<T> segs;
  vc<S> lazy;
  RURQ(int nb)
      : logn(__lg(2 * nb - 1)), n(1 << logn), segs(2 * n, e), lazy(2 * n, id) {
    for (int i = n - 1; i > 0; i--) {
      segs[i] = op(segs[i << 1], segs[i << 1 | 1]);
    }
  }
  void apply(int i, S v) {
    segs[i] = use(segs[i], v);
    if (i < n) lazy[i] = lazyop(lazy[i], v);
  }
  void down(int i) {
    if (lazy[i] == id) return;
    apply(i << 1, lazy[i]);
    apply(i << 1 | 1, lazy[i]);
    lazy[i] = id;
  }
  void push(int i) {
    for (int j = logn; j > 0; j--) {
      down((i + n) >> j);
    }
  }
  void pull(int i) {
    for (i += n; i >>= 1;) {
      segs[i] = use(op(segs[i << 1], segs[i << 1 | 1]), lazy[i]);
    }
  }
  void update(int l, int r, S v) {
    if (l >= r) return;
    int l0 = l, r0 = r;
    push(l0), push(r0 - 1);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) apply(l++, v);
      if (r & 1) apply(--r, v);
    }
    pull(l0), pull(r0 - 1);
  }
  T query(int l, int r) {
    if (l >= r) return e;
    T lv = e, rv = e;
    push(l), push(r - 1);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, segs[l++]);
      if (r & 1) rv = op(segs[--r], rv);
    }
    return op(lv, rv);
  }
  void assign(int i, T v) {
    push(i);
    segs[i + n] = v;
    pull(i);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 10:54
  // thinking done: 10:58
  // target impl time: 30 min
  // initial impl done: 11:22

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vi index(N);
    rep(i, 0, N) { index[A[i]] = i; }

    RURQ rurq(N);
    auto assign = [&](int i, int v) -> void {
      rurq.assign(i, {i, v - i, v + i});
    };
    auto query = [&](int i) -> int {
      auto [i2, a, b] = rurq.query(i, i + 1);
      return min(a + i, b - i);
    };
    auto invalidate = [&](int l, int r) -> void {
      int vl = query((l + N - 1) % N), vr = query(r % N);
      if (r > N) {
        rurq.update(l, N, {true, vl + 1 - l, vr + 1 + r - 1});
        rurq.update(0, r - N, {true, vl + 1 - (l - N), vr + 1 + r - 1 - N});
      } else {
        rurq.update(l, r, {true, vl + 1 - l, vr + 1 + r - 1});
      }
    };

    rep(i, 0, N) { assign(i, min(i, N - i)); }
    for (auto e : index) {
      invalidate(e + 1, N + e - (K - 1));
    }
    int ans = INF;
    rep(i, 0, N) { chmin(ans, query(i)); }
    cout << ans << '\n';
  }
}
