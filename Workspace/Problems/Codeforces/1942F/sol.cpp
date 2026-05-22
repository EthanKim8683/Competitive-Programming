#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<i64> A(N);
  for (auto &e : A) cin >> e;

  vector<pair<int, i64>> queries(Q);
  for (auto &[k, x] : queries) {
    cin >> k >> x;
    k--;
  }

  // let v[n+1] <= floor(f(n))
  // v_i = v_{i+1}^2 - a_i
  // there must exist i s.t. v_i <= 0
  //
  // v_{i+1}^2 - 1e18 > v_{i+1}
  // if v_{i+1}^2 > 1e9, v_i is can only be greater than v_{i+1} and there
  // will never exist i s.t. v_i <= 0

  if (0) {
    // d_0 = 1
    i64 d = 1;
    for (int i = 1; i < 100; i++) {
      // assume v is minimal s.t. d is minimal as well
      i64 v = 1;
      d = 2 * v * d + d * d;
      cout << d << ' ';
    }
    cout << '\n';
    // d_5 > 1e9
    //
    // for subarrays of length k > 5, v_{k+1} > floor(f(k))*, evaluated on the
    // subarray alone, will never yield i s.t. v_i <= 0 anywhere in the
    // entire array
  }

  if (0) {
    // d_0 = -1, d_1 = -3 assuming v[n+1] > 1
    i64 d = -3;
    for (int i = 2; i < 100; i++) {
      // assume v is minimal s.t. d is minimal as well
      i64 v = -d;
      d = 2 * v * d + d * d;
      cout << d << ' ';
    }
    cout << '\n';
    // d_6 < -1e18
    //
    // assuming floor(f(k))* > 1, for subarrays of length k > 6, v_{k+1} <
    // floor(f(k)), evaluated on the subarray alone will always yield i s.t.
    // v_i <= 0 within the subarray
    //
    // if floor(f(k))* = 1, then d_0 can be 0 or -1
    // if it's -1, v_{k+1} = 0 so the above still holds true
  }

  // * unlike in the full array, if v_{i} <= 0 isn't found in the subarray,
  // that doesn't count as failure, and v_1 is just passed onto the next
  // subarray

  auto solve_naively = [&]() -> int {
    auto check = [&](i64 v_N) -> bool {
      i64 v = v_N;
      for (int i = N - 1; i >= 0; i--) {
        v = v * v - A[i];
        if (v <= 0) return true;
        if (v > 1e9) return false;
      }
      return false;
    };
    int l = 0, r = 1e9;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    return l;
  };

  if (N <= 100) {
    for (auto [k, x] : queries) {
      A[k] = x;
      cout << solve_naively() << '\n';
    }
  } else {
    int K = sqrt(N);

    auto solve = [&](int L, int R) -> pair<i64, i64> {
      assert(R - L >= 10);

      i64 v_0;
      auto check = [&](i64 v_K) -> bool {
        i64 v = v_K;
        for (int i = R - 1; i >= L; i--) {
          v = v * v - A[i];
          if (v <= 0) return true;
          if (v > 1e9) return false;
        }
        v_0 = v;
        return true;
      };
      int l = 0, r = 1e9;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        check(m) ? l = m : r = m - 1;
      }
      v_0 = -1;
      check(l);
      return {l, v_0};
    };

    vector<pair<int, int>> ranges(N);
    for (int i = 0; i + K <= N; i += K) {
      if (i + 2 * K > N) {
        fill(ranges.begin() + i, ranges.begin() + N, make_pair(i, N));
      } else {
        fill(ranges.begin() + i, ranges.begin() + i + K, make_pair(i, i + K));
      }
    }

    vector<pair<i64, i64>> blocks((N - 1) / K);
    for (int i = 0; i + K <= N; i += K) {
      auto [L, R] = ranges[i];
      blocks[i / K] = solve(L, R);
    }
    for (auto [k, x] : queries) {
      A[k] = x;

      auto [L, R] = ranges[k];
      blocks[L / K] = solve(L, R);

      auto check = [&](i64 v_N) -> bool {
        i64 v = v_N;
        for (int i = (N - 1) / K - 1; i >= 0; i--) {
          auto [f_K, v_] = blocks[i];
          if (v < f_K) return true;
          if (v > f_K) return false;
          if (v_ == -1) return true;
          v = v_;
        }
        return false;
      };
      int l = 0, r = 1e9;
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        check(m) ? l = m : r = m - 1;
      }
#ifdef ETHANKIM8683
      assert(l == solve_naively());
#endif
      cout << l << '\n';
    }
  }
}
