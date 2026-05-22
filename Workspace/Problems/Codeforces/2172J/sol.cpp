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

struct Node {
  int depth, Y, L, R;
  Node *a, *b;
  bool has_children;

  Node(int y, int l, int r)
      : depth(0),
        Y(y),
        L(l),
        R(r),
        a(nullptr),
        b(nullptr),
        has_children(false) {}

  void apply_children() {
    if (has_children) return;
    has_children = true;

    int m = L + (R - L) / 2;
    if (L < m) {
      a = new Node(Y, L, m);
    }
    if (m < R) {
      b = new Node(Y, m, R);
    }
  }

  void apply_lazy() {
    assert(has_children);
    if (a != nullptr) {
      a->depth += depth;
    }
    if (b != nullptr) {
      b->depth += depth;
    }
    depth = 0;
  }

  void traverse(auto visit) {
    if (has_children) {
      apply_lazy();
      if (a != nullptr) {
        a->traverse(visit);
      }
      if (b != nullptr) {
        b->traverse(visit);
      }
    }
    visit(this);
  }

  void deepen(int l, int r, int x) {
    if (r <= L or R <= l) return;
    if (l <= L and R <= r) {
      depth += x;
      return;
    }

    apply_children();
    if (a != nullptr) {
      a->deepen(l, r, x);
    }
    if (b != nullptr) {
      b->deepen(l, r, x);
    }
  }

  Node *replace(int y, int l, int r, auto visit) {
    if (r <= L or R <= l) return this;
    if (l <= L and R <= r) {
      traverse(visit);
      return new Node(y, L, R);
    }

    apply_children();
    apply_lazy();
    if (a != nullptr) {
      a = a->replace(y, l, r, visit);
    }
    if (b != nullptr) {
      b = b->replace(y, l, r, visit);
    }
    return this;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 7:14
  // thinking done: 7:23
  // target impl time: 1 hr
  // initial impl done: 8:00

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi H(N);
  H[0] = N;
  rep(i, 1, N) { cin >> H[i]; }

  vi st(2 * N, 0);
  auto add = [&](int l, int r, int x) -> void {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
      if (l & 1) st[l++] += x;
      if (r & 1) st[--r] += x;
    }
  };
  auto get = [&](int i) -> int {
    int rv = 0;
    for (i += N; i > 0; i >>= 1) {
      rv += st[i];
    }
    return rv;
  };

  Node *root = new Node(N, 0, N);
  for (int i = N - 1; i >= 0; i--) {
    root->deepen(0, A[i], 1);

    vc<Node *> nodes;
    root =
        root->replace(i, 0, H[i], [&](Node *node) -> void { nodes.pb(node); });
    for (auto e : nodes) {
      add(e->Y - e->depth, e->Y, e->R - e->L);
      delete e;
    }
  }

  rep(i, 0, N) { cout << get(i) << ' '; }
}
