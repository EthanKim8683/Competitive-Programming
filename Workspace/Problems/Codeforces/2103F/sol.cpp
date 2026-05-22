#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"

using namespace std;
using namespace atcoder;

using S = int;
S op(S a, S b) { return 0; }
S e() { return 0; }
using F = int;
S mapping(F f, S x) { return max(f, x); }
F composition(F f, F g) { return max(f, g); }
F id() { return 0; }

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N, K;
    if (argc > 1) {
      N = 1000;
      K = 17;
    } else {
      cin >> N >> K;
    }

    vector<int> A(N);
    if (argc > 1) {
      for (auto &e : A) {
        e = rng() % (1 << K);
      }
    } else {
      for (auto &e : A) cin >> e;
    }

    if (argc > 1) {
      cerr << N << ' ' << K << '\n';
      for (auto e : A) {
        cerr << e << ' ';
      }
      cerr << '\n';
    }

    auto nor = [&](int x, int y) -> int {
      return (x ^ ((1 << K) - 1)) & (y ^ ((1 << K) - 1));
    };

    lazy_segtree<S, op, e, F, mapping, composition, id> st(N);
    vector<int> prev(K, -1);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < K; j++) {
        if (~A[i] >> j & 1) continue;
        prev[j] = i;
      }

      vector<tuple<int, int, int>> ranges[2];
      for (int j = 0; j < K; j++) {
        int k = prev[j];
        ranges[0].emplace_back(i - (i - k) / 2 * 2 + 1, i, 1 << j);
        if (k != -1) {
          if ((i - k) % 2 == 0) {
            ranges[1].emplace_back(k, k + 1, 1 << j);
          } else {
            ranges[1].emplace_back(i % 2, k, 1 << j);
            ranges[0].emplace_back(1 - i % 2, k, 1 << j);
          }
        }
      }

      for (auto subranges : ranges) {
        vector<int> cc;
        for (auto [l, r, w] : subranges) {
          cc.push_back(l);
          cc.push_back(r);
        }
        sort(cc.begin(), cc.end());
        cc.erase(unique(cc.begin(), cc.end()), cc.end());

        vector<int> ps(cc.size(), 0);
        for (auto [l, r, w] : subranges) {
          l = lower_bound(cc.begin(), cc.end(), l) - cc.begin();
          r = lower_bound(cc.begin(), cc.end(), r) - cc.begin();
          ps[l] += w;
          ps[r] -= w;
        }
        for (int j = 0; j + 1 < cc.size(); j++) {
          ps[j + 1] += ps[j];
        }

        for (int j = 0; j + 1 < cc.size(); j++) {
          st.apply(cc[j], i + 1, ps[j]);
        }
      }
    }
    vector<int> ans(N);
    for (int i = 0; i < N; i++) {
      ans[i] = max(ans[i], st.get(i));
    }

    if (argc > 1) {
      vector<int> brute(N, 0);
      for (int i = 0; i < N; i++) {
        vector<int> X(N - i);
        int x = A[i];
        X[0] = x;
        for (int j = i + 1; j < N; j++) {
          x = nor(x, A[j]);
          X[j - i] = x;
        }
        for (int j = N - i - 1; j - 1 >= 0; j--) {
          X[j - 1] = max(X[j - 1], X[j]);
        }
        for (int j = i; j < N; j++) {
          brute[j] = max(brute[j], X[j - i]);
        }
      }

      cerr << "ans:\t";
      for (auto e : ans) {
        cerr << e << ' ';
      }
      cerr << '\n';
      cerr << "brute:\t";
      for (auto e : brute) {
        cerr << e << ' ';
      }
      cerr << '\n';

      assert(ans == brute);
    } else {
      for (auto e : ans) {
        cout << e << ' ';
      }
      cout << '\n';
    }
  }
}
