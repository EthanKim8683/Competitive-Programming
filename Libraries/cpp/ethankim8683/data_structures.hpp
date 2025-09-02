#ifndef ETHANKIM8683_DATA_STRUCTURES
#define ETHANKIM8683_DATA_STRUCTURES 1

#include <assert.h>
#include <time.h>

#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <random>
#include <tuple>
#include <vector>

#include "ethankim8683/type_traits"

// The top two elements of a map whose entries are ordered by value
template <typename T, typename S>
struct top_two {
 private:
  struct element {
    T val;
    S from;
  };

  T nil_val;
  S nil_from;
  std::function<bool(T, T)> cmp;

 public:
  element first, second;

  top_two() {}
  top_two(T _nil_val, S _nil_from, const std::function<bool(T, T)> &_cmp)
      : nil_val(_nil_val),
        nil_from(_nil_from),
        cmp(_cmp),
        first(nil_val, nil_from),
        second(nil_val, nil_from) {}

  bool put(T val, S from) {
    if (cmp(val, first.val)) {
      if (from != first.from) {
        second = first;
      }
      first.val = val;
      first.from = from;
      return true;
    }

    if (from != first.from and cmp(val, second.val)) {
      second.val = val;
      second.from = from;
      return true;
    }

    return false;
  }

  bool merge(const top_two<T, S> &that) {
    bool f = put(that.first), s = put(that.second);
    return f or s;
  }
};

template <typename T>
struct sparse_table {
 private:
  int n;
  T nil;
  std::function<T(T, T)> op;
  std::vector<std::vector<T>> table;

 public:
  sparse_table() {}
  sparse_table(const std::vector<T> &v, T _nil,
               const std::function<T(T, T)> &_op)
      : n(v.size()),
        nil(_nil),
        op(_op),
        table(std::__lg(n) + 1, std::vector<T>(n, nil)) {
    std::copy(v.begin(), v.end(), table[0].begin());
    for (int i = 1; i < table.size(); i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        table[i][j] = op(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  T query(int l, int r) const {
    if (l >= r) return nil;

    int d = std::__lg(r - l);
    return op(table[d][l], table[d][r - (1 << d)]);
  }
};

// https://atcoder.jp/contests/abc328/editorial/7664
// DSU with edge voltages to measure node potentials
template <typename T>
struct dsu_with_potentials {
 private:
  std::function<T(T, T)> op;
  std::function<T(T)> inv;
  std::vector<int> par;
  std::vector<T> V;

 public:
  dsu_with_potentials() {}
  dsu_with_potentials(int n, T nil, const std::function<T(T, T)> &_op,
                      const std::function<T(T)> &_inv)
      : op(_op), inv(_inv), par(n, -1), V(n, nil) {}

  int leader(int a) {
    if (par[a] < 0) return a;
    int p = leader(par[a]);
    V[a] = op(V[a], V[par[a]]);
    return par[a] = p;
  }

  bool merge(int a, int b, T v) {
    int a_ = leader(a), b_ = leader(b);
    if (a_ == b_) return op(V[b], inv(V[a])) == v;
    if (par[a_] > par[b_]) {
      std::swap(a_, b_);
      std::swap(a, b);
      v = inv(v);
    }
    par[a_] += par[b_];
    par[b_] = a_;
    V[b_] = op(op(v, V[a]), inv(V[b]));
    return true;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -par[leader(a)]; }

  T potential(int a) {
    leader(a);
    return V[a];
  }

  T voltage(int a, int b) { return op(potential(b), inv(potential(a))); }
};

// https://usaco.guide/plat/RURQ#implementation
// Fenwick tree with range updates
template <typename T>
struct range_add_fenwick_tree {
 private:
  using T2 = double_width<T>::type;

  int n;
  std::vector<T> m;
  std::vector<T2> b;

 public:
  range_add_fenwick_tree() {}
  range_add_fenwick_tree(int _n) : n(_n), m(n + 1, 0), b(n + 1, 0) {}

  void add(int l, int r, T v) {
    assert(0 <= l and l <= r and r <= n);
    for (int i = l + 1; i <= n; i += i & -i) {
      m[i] += v;
      b[i] += (T2) v * l;
    }
    for (int i = r + 1; i <= n; i += i & -i) {
      m[i] -= v;
      b[i] -= (T2) v * r;
    }
  }

  T sum(int l, int r) {
    assert(0 <= l and l <= r and r <= n);
    T2 rv = 0;
    for (int i = l; i > 0; i -= i & -i) {
      rv -= (T2) m[i] * l - b[i];
    }
    for (int i = r; i > 0; i -= i & -i) {
      rv += (T2) m[i] * r - b[i];
    }
    return rv;
  }
};

// https://usaco.guide/adv/persistent#path-copying
// Persistent array with insertion and deletion
template <typename T>
struct persistent_vector {
 private:
  struct node {
    T v;
    node *l, *r;

    node() : v(), l(nullptr), r(nullptr) {}
    node(T _v) : v(_v), l(nullptr), r(nullptr) {}
    node(T _v, node *_l, node *_r) : v(_v), l(_l), r(_r) {}
  };

  int n;
  node *root;

  persistent_vector(int _n, node *_root) : n(_n), root(_root) {}

  static int middle(int l, int r) {
    return l + (1 << std::__lg(r - l + 1)) - 1;
  }

 public:
  persistent_vector() : n(0), root(nullptr) {}

  persistent_vector(const std::vector<T> &v) : n(v.size()) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (l > r) return nullptr;

      int m = middle(l, r);
      return new node(v[m], self(self, l, m - 1), self(self, m + 1, r));
    };
    root = dfs(dfs, 0, n - 1);
  }
  persistent_vector(int _n, T nil = T())
      : persistent_vector(std::vector<T>(_n, nil)) {}

  int size() const { return n; }
  bool empty() const { return n == 0; }

  persistent_vector<T> set(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      int m = middle(l, r);
      if (m == i) return new node(v, a->l, a->r);

      if (i < m) {
        return new node(a->v, self(self, a->l, l, m - 1), a->r);
      } else {
        return new node(a->v, a->l, self(self, a->r, m + 1, r));
      }
    };
    return {n, dfs(dfs, root, 0, n - 1)};
  }

  T get(int i) const {
    node *a = root;
    int l = 0, r = n - 1;
    while (true) {
      int m = middle(l, r);
      if (m == i) return a->v;

      if (i < m) {
        a = a->l;
        r = m - 1;
      } else {
        a = a->r;
        l = m + 1;
      }
    }
  }

  // O(\log{N})
  persistent_vector<T> push_back(T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (l > r) return new node(v);

      int m = middle(l, r);
      if (m - l == r - m) return new node(v, a, nullptr);

      return new node(a->v, a->l, self(self, a->r, m + 1, r));
    };
    return {n + 1, dfs(dfs, root, 0, n - 1)};
  }

  // O(\log{N})
  persistent_vector<T> pop_back() {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      int m = middle(l, r);
      if (m == r) return a->l;

      return new node(a->v, a->l, self(self, a->r, m + 1, r));
    };
    return {n - 1, dfs(dfs, root, 0, n - 1)};
  }

  // O(\log{N+K})
  persistent_vector<T> insert(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r, bool check) -> node * {
      if (check) {
        if (l > r) return new node(v);
      } else {
        if (l > r) return nullptr;
        if (r < i) return a;
      }

      int m = middle(l, r);
      bool push = false;
      if (check) {
        push = m - l == r - m;
        check = push == false;
      }

      node *a_ = new node(a->v);
      a_->l = self(self, a->l, l, m - 1, false);
      if (m >= i) {
        a_->v = v;
        v = a->v;
      }
      a_->r = self(self, a->r, m + 1, r, check);

      if (push) {
        return new node(v, a_, nullptr);
      } else {
        return a_;
      }
    };
    return {n + 1, dfs(dfs, root, 0, n - 1, true)};
  }

  // O(\log{N+K})
  persistent_vector<T> erase(int i) {
    T v;
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (l > r) return nullptr;
      if (r < i) return a;

      int m = middle(l, r);
      if (m == n - 1) {
        v = a->v;
        return self(self, a->l, l, m - 1);
      }

      node *a_ = new node(a->v);
      a_->r = self(self, a->r, m + 1, r);
      if (m >= i) {
        a_->v = v;
        v = a->v;
      }
      a_->l = self(self, a->l, l, m - 1);
      return a_;
    };
    return {n - 1, dfs(dfs, root, 0, n - 1)};
  }
};

// https://usaco.guide/adv/persistent#persistent-segment-tree
// https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp
// TODO: Implement min_left, min_right, etc.
template <class T, auto op, auto e>
struct persistent_segtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<T(T, T)>>,
                "op must work as T(T, T)");
  static_assert(std::is_convertible_v<decltype(e), std::function<T()>>,
                "e must work as T()");

 private:
  struct node {
    T v;
    node *l, *r;

    node(T _v) : v(_v), l(nullptr), r(nullptr) {}
    node(node *_l, node *_r) : v(e()), l(_l), r(_r) {
      if (l != nullptr) {
        v = op(v, l->v);
      }
      if (r != nullptr) {
        v = op(v, r->v);
      }
    }
  };

  int n;
  node *root;

  persistent_segtree(int _n, node *_root) : n(_n), root(_root) {}

 public:
  persistent_segtree() {}
  persistent_segtree(const std::vector<T> &v) : n(v.size()) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (r - l == 1) return new node(v[l]);

      int m = l + (r - l) / 2;
      return new node(self(self, l, m), self(self, m, r));
    };
    root = dfs(dfs, 0, n);
  }
  persistent_segtree(int _n) : persistent_segtree(std::vector<T>(_n, e())) {}

  persistent_segtree<T, op, e> set(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (r - l == 1) return new node(v);

      int m = l + (r - l) / 2;
      if (i < m) {
        return new node(self(self, a->l, l, m), a->r);
      } else {
        return new node(a->l, self(self, a->r, m, r));
      }
    };
    return {n, dfs(dfs, root, 0, n)};
  }

  T get(int i) const {
    node *a = root;
    int l = 0, r = n;
    while (r - l > 1) {
      int m = l + (r - l) / 2;
      if (i < m) {
        a = a->l;
        r = m;
      } else {
        a = a->r;
        l = m;
      }
    }
    return a->v;
  }

  T prod(int l, int r) const {
    auto dfs = [&](auto self, node *a, int l_, int r_) -> T {
      if (r <= l_ or r_ <= l) return e();
      if (l <= l_ and r_ <= r) return a->v;

      int m = l_ + (r_ - l_) / 2;
      return op(self(self, a->l, l_, m), self(self, a->r, m, r_));
    };
    return dfs(dfs, root, 0, n);
  }

  T all_prod() const { return root->v; }
};

// https://usaco.guide/adv/offline-del#dsu-with-rollback
struct dsu_with_rollbacks {
 private:
  std::vector<int> par;
  std::vector<std::tuple<int, int, int>> history;
  std::vector<int> saves;

 public:
  dsu_with_rollbacks() {}
  dsu_with_rollbacks(int n) : par(n, -1), saves({0}) {}

  // https://codeforces.com/blog/entry/90340?#comment-787571
  // O(\log{N})
  int leader(int a) {
    if (par[a] < 0) return a;
    return leader(par[a]);
  }

  int merge(int a, int b) {
    if ((a = leader(a)) == (b = leader(b))) return a;
    if (par[a] > par[b]) {
      std::swap(a, b);
    }
    history.push_back({a, b, par[b]});
    par[a] += par[b];
    par[b] = a;
    return a;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -par[leader(a)]; }

  void save() { saves.push_back(history.size()); }

  void rollback() {
    while (history.size() > saves.back()) {
      auto [a, b, size] = history.back();
      history.pop_back();
      par[a] -= size;
      par[b] = size;
    }
    saves.pop_back();
  }
};

// https://jilljenn.github.io/tryalgo/_modules/tryalgo/union_rectangles.html#union_rectangles
template <typename T, typename S>
struct cover_query {
 private:
  struct seg {
    S c;
    T s, w;
  };

  int n;
  std::vector<seg> data;

 public:
  cover_query() {}
  cover_query(const std::vector<T> &l)
      : n(1 << std::__lg(2 * l.size() - 1)), data(2 * n, {0, 0, 0}) {
    for (int i = 0; i < l.size(); i++) {
      data[n + i].w = l[i];
    }
    for (int i = n - 1; i > 0; i--) {
      data[i].w = data[i << 1].w + data[i << 1 | 1].w;
    }
  }
  cover_query(int _n) : cover_query(std::vector<T>(_n, 1)) {}

  T cover() { return data[1].s; }

  void add(int l, int r, S dc) {
    auto dfs = [&](auto self, int i, int sl, int sr) -> void {
      if (sr <= l or r <= sl) return;
      if (l <= sl and sr <= r) {
        data[i].c += dc;
      } else {
        int sm = sl + (sr - sl) / 2;
        self(self, i << 1, sl, sm);
        self(self, i << 1 | 1, sm, sr);
      }
      if (data[i].c == 0) {
        if (i >= n) {
          data[i].s = 0;
        } else {
          data[i].s = data[i << 1].s + data[i << 1 | 1].s;
        }
      } else {
        data[i].s = data[i].w;
      }
    };
    dfs(dfs, 1, 0, n);
  }
};

// https://cp-algorithms.com/data_structures/treap.html#implicit-treaps
// https://github.com/ShahjalalShohag/code-library/blob/main/Data%20Structures/Implicit%20Treap.cpp
// TODO: Generalize to support custom operations
template <typename T>
struct implicit_treap {
 private:
  static std::mt19937 rng;

  struct node {
    T v;
    node *l, *r;
    int y, size;

    node(T _v, int _y) : v(_v), l(nullptr), r(nullptr), y(_y), size(0) {}
    node(T _v) : node(_v, rng()) {}
  };

  node *root;

  static int safe_size(node *a) { return a == nullptr ? 0 : a->size; }

  static node *safe_copy(node *a) {
    if (a == nullptr) return nullptr;
    node *a_ = new node(*a);
    a_->l = safe_copy(a->l);
    a_->r = safe_copy(a->r);
    return a_;
  }

  static void safe_free(node *a) {
    if (a == nullptr) return;
    safe_free(a->l);
    safe_free(a->r);
    free(a);
  }

  static void safe_pull(node *a) {
    if (a == nullptr) return;
    a->size = safe_size(a->l) + 1 + safe_size(a->r);
  }

  static node *merge(node *l, node *r) {
    auto dfs = [&](auto self, node *&a, node *l, node *r) -> void {
      if (l == nullptr) {
        a = r;
      } else if (r == nullptr) {
        a = l;
      } else if (l->y >= r->y) {
        self(self, l->r, l->r, r);
        a = l;
      } else {
        self(self, r->l, l, r->l);
        a = r;
      }
      safe_pull(a);
    };
    node *rv;
    dfs(dfs, rv, l, r);
    return rv;
  }

  static std::pair<node *, node *> split(node *a, int i) {
    auto dfs = [&](auto self, node *a, node *&l, node *&r, int i) -> void {
      if (a == nullptr) {
        l = r = nullptr;
        return;
      }
      if (i <= safe_size(a->l)) {
        self(self, a->l, l, a->l, i);
        r = a;
      } else {
        self(self, a->r, a->r, r, i - (1 + safe_size(a->l)));
        l = a;
      }
      safe_pull(a);
    };
    node *l, *r;
    dfs(dfs, a, l, r, i);
    return {l, r};
  }

  implicit_treap(node *_root) : root(_root) {}

  node *get_node(int i) {
    assert(0 <= i and i < size());
    auto dfs = [&](auto self, node *a, int i) -> node * {
      if (i == safe_size(a->l)) {
        return a;
      } else if (i < safe_size(a->l)) {
        return self(self, a->l, i);
      } else {
        return self(self, a->r, i - (1 + safe_size(a->l)));
      }
    };
    return dfs(dfs, root, i);
  };

 public:
  implicit_treap() : root(nullptr) {}

  implicit_treap(const std::vector<int> &v) {
    auto dfs_heapify = [&](auto self, node *a) -> void {
      if (a == nullptr) return;
      node *b = a;
      if (a->l != nullptr and a->l->y > b->y) {
        b = a->l;
      }
      if (a->r != nullptr and a->r->y > b->y) {
        b = a->r;
      }
      if (b != a) {
        std::swap(a->y, b->y);
        self(self, b);
      }
    };

    auto dfs_build = [&](auto self, int l, int r) -> node * {
      if (l == r) return nullptr;
      int m = l + (r - l) / 2;
      node *a = new node(v[m]);
      a->l = self(self, l, m);
      a->r = self(self, m + 1, r);
      dfs_heapify(dfs_heapify, a);
      safe_pull(a);
      return a;
    };
    root = dfs_build(dfs_build, 0, v.size());
  }

  implicit_treap(int n, T v) : implicit_treap(std::vector<T>(n, v)) {}

  ~implicit_treap() { safe_free(root); }

  int size() const { return safe_size(root); }

  void insert(int i, T v) {
    assert(0 <= i and i <= size());
    auto [l, r] = split(root, i);
    root = merge(merge(l, new node(v)), r);
  }

  void erase(int i) {
    assert(0 <= i and i < size());
    auto [l1, r1] = split(root, i);
    auto [l2, r2] = split(r1, 1);
    safe_free(l2);
    root = merge(l1, r2);
  }

  void set(int i, T v) { get_node(i)->v = v; }

  T get(int i) { return get_node(i)->v; }
};
template <typename T>
std::mt19937 implicit_treap<T>::rng(time(nullptr));

// https://codeforces.com/blog/entry/11080
template <typename T, typename Compare = std::less<T>>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;
template <typename T, typename S, typename Compare = std::less<T>>
using ordered_map =
    __gnu_pbds::tree<T, S, Compare, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

#endif  // ETHANKIM8683_DATA_STRUCTURES
