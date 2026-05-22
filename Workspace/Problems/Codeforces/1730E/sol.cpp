#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>
struct sparse_fenwick_tree {
 private:
  int n;
  std::unordered_map<int, T> data;

  T safe_data(int i) const {
    auto it = data.find(i);
    if (it != data.end()) return it->second;
    return 0;
  }

  T sum(int i) const {
    T rv = 0;
    for (; i > 0; i -= i & -i) {
      rv += safe_data(i);
    }
    return rv;
  }

 public:
  sparse_fenwick_tree(int _n) : n(_n) {}

  void add(int i, T x) {
    assert(0 <= i and i < n);
    for (i++; i <= n; i += i & -i) {
      data[i] += x;
    }
  }

  T sum(int l, int r) const {
    assert(0 <= l and l <= r and r <= n);
    return sum(r) - sum(l);
  }
};

struct range_add_range_sum {
 private:
  sparse_fenwick_tree<i64> ft1, ft2;

  i64 sum(int i) const { return ft1.sum(0, i) * (i - 1) - ft2.sum(0, i); }

 public:
  range_add_range_sum(int n) : ft1(n + 1), ft2(n + 1) {}

  void add(int l, int r, int x) {
    ft1.add(l, x);
    ft2.add(l, (i64) x * (l - 1));
    ft1.add(r, -x);
    ft2.add(r, (i64) -x * (r - 1));
  }

  int sum(int l, int r) const { return sum(r) - sum(l); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<vector<int>> divs(1e6 + 1);
  for (int i = 1; i <= 1e6; i++) {
    for (int j = i; j <= 1e6; j += i) {
      divs[j].push_back(i);
    }
  }
  // 240

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;
  }
}
