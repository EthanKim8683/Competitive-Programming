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

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b], e[b] = a;
    return true;
  }
};

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N, K, M;
  if (argc > 1) {
    N = 1000;
    K = rng() % N + 1;
    M = 1e9 + 7;
  } else {
    cin >> N >> K >> M;
  }

  vi A(K);
  if (argc > 1) {
    set<int> S;
    for (auto &e : A) {
      do {
        e = rng() % N + 1;
      } while (S.contains(e));
      S.insert(e);
    }
    sort(all(A));
  } else {
    for (auto &e : A) cin >> e;
  }

  set<int> pq;
  pq.insert(0);
  for (auto e : A) {
    pq.insert(e);
  }
  int n = 0, p = 2 * N, q = 0;
  while (sz(pq) > 0) {
    int r = *pq.rbegin();
    pq.erase(r);
    p = (r + 1) + (p - (r + 1)) % (p - q);
    q = r;
    if (2 * q > p) {
      pq.insert(p % (p - q));
    } else {
      n += (p + 1) / 2 - q;
    }
  }

  if (argc > 1) {
    UF uf(N);
    for (auto e : A) {
      rep(i, 0, e) { uf.join(i, e - 1 - i); }
    }
    int m = 0;
    rep(i, 0, N) {
      if (uf.find(i) != i) continue;
      m += 1;
    }
    assert(n == m);
  } else {
    auto mod_pow = [&](int x, int y) -> int {
      int rv = 1;
      for (x %= M; y; y >>= 1, (x *= x) %= M) {
        if (y & 1) {
          (rv *= x) %= M;
        }
      }
      return rv;
    };
    cout << mod_pow(2, n) << '\n';
  }
}
