#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // epic subarrays have a range of i's
  // store lefts (can take ge A[l], can take le A[r])

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    using S1 = int;
    auto op1 = [&](S1 a, S1 b) -> S1 { return min(a, b); };
    auto e1 = [&]() -> int { return INF; };
    sparse_table<S1, op1, e1> st1(A);
    using S2 = int;
    auto op2 = [&](S2 a, S2 b) -> S2 { return max(a, b); };
    auto e2 = [&]() -> int { return -INF; };
    sparse_table<S2, op2, e2> st2(A);
    map<int, i64> ge, le;
    i64 ans = 0;
    for (int i = 0; i < N; i++) {
      {
        int l = i + 1, r = N;
        while (l < r) {
          int m = l + (r - l + 1) / 2;
          st2.prod(i + 1, m) < A[i] ? l = m : r = m - 1;
        }
        ans += (l - i) * (ge[K - A[i]] + le[K - A[i]]);
      }

      {
        auto begin = ge.upper_bound(A[i]);
        for (auto it = begin; it != ge.end(); it = ge.erase(it)) {
          le[it->first] += it->second;
        }
      }

      {
        auto begin = le.upper_bound(K - A[i]);
        for (auto it = begin; it != le.end(); it = le.erase(it)) {
        }
      }

      {
        int l = 0, r = i;
        while (l < r) {
          int m = l + (r - l) / 2;
          st1.prod(m, i) > A[i] ? r = m : l = m + 1;
        }
        ge[A[i]] += i + 1 - l;
      }
    }
    cout << ans << '\n';
  }
}
