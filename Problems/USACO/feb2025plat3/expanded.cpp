// beginning of 'atcoder/internal_bit.hpp'
#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1

#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace atcoder {

namespace internal {

#if __cplusplus >= 202002L

using std::bit_ceil;

#else

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

#endif

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_BITOP_HPP
// end of 'atcoder/internal_bit.hpp'

// beginning of 'atcoder/internal_bit'
// #include "atcoder/internal_bit.hpp"
// end of 'atcoder/internal_bit'

// beginning of 'atcoder/segtree.hpp'
#ifndef ATCODER_SEGTREE_HPP
#define ATCODER_SEGTREE_HPP 1

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

// #include "atcoder/internal_bit"

namespace atcoder {

#if __cplusplus >= 201703L

template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif

  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder

#endif  // ATCODER_SEGTREE_HPP
// end of 'atcoder/segtree.hpp'

// beginning of 'main'
#include <bits/stdc++.h>

// #include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

using S = pair<i64, int>;
S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
S e() { return {0, 0}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<pair<int, int>> pairs(N);
  for (auto &[a, b] : pairs) {
    cin >> a >> b;
  }

  sort(pairs.begin(), pairs.end(), [&](auto a, auto b) {
    auto key = [&](pair<int, int> p) -> pair<int, int> {
      return {p.first + p.second, p.second};
    };
    return key(a) > key(b);
  });

  // if x are not correct (incorrect or skipped), the top x-k b values are added
  //
  // divide and conquer!

  vector<int> cc;
  for (auto [a, b] : pairs) {
    cc.push_back(b);
  }
  sort(cc.begin(), cc.end());
  cc.erase(unique(cc.begin(), cc.end()), cc.end());
  auto compress = [&](int x) -> int {
    return lower_bound(cc.begin(), cc.end(), x) - cc.begin();
  };

  i64 sum = 0, base = 0;
  for (auto [a, b] : pairs) {
    sum += a + b;
    base += b;
  }

  segtree<S, op, e> st(cc.size());
  int i = 0;
  vector<i64> ans(N + 1);
  auto dfs = [&](auto self, int l1, int r1, int l2, int r2) -> void {
    if (l1 > r1) return;
    int k = l1 + (r1 - l1) / 2;

    pair<i64, int> best = {0, 0};
    auto apply = [&]() -> void {
      int l = 0, r = cc.size();
      while (l < r) {
        int m = l + (r - l) / 2;
        st.prod(m, cc.size()).second <= i - k ? r = m : l = m + 1;
      }

      auto [sum3, count] = st.prod(l, cc.size());
      i64 sum2 = sum + sum3;
      if (l > 0) {
        sum2 += (i64) (i - k - count) * cc[l - 1];
      }
      best = max(best, {sum2, i});
    };

    for (; i - 1 >= max(k, l2); i--) {
      auto [a, b] = pairs[i - 1];
      auto [sum2, count] = st.get(compress(b));
      st.set(compress(b), {sum2 - b, count - 1});
      sum += a + b;
    }
    for (; i < r2; i++) {
      if (i >= max(k, l2)) {
        apply();
      }
      auto [a, b] = pairs[i];
      auto [sum2, count] = st.get(compress(b));
      st.set(compress(b), {sum2 + b, count + 1});
      sum -= a + b;
    }
    apply();
    ans[k] = best.first - base;

    int m = best.second;
    self(self, l1, k - 1, l2, m);
    self(self, k + 1, r1, m, r2);
  };
  dfs(dfs, 0, N, 0, N);

  while (Q--) {
    int k;
    cin >> k;

    cout << ans[k] << '\n';
  }
}
// end of 'main'