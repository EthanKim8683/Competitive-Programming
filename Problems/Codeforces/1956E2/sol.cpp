#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using i128 = __int128;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // auto length = [&](int k) -> int {
  //   vector<int> V0(k, 0);
  //   for (int n = 1;; n++) {
  //     i64 v = accumulate(V0.begin(), V0.end(), 0ll) + 1;
  //     if (v > 1e9) return n;
  //     vector<int> V(k);
  //     V[0] = v;
  //     for (int i = 1; i < k; i++) {
  //       V[i] = V[i - 1] - V0[i - 1];
  //     }
  //     V0 = V;
  //   }
  // };

  // for (int k = 2; k <= 100; k++) {
  //   cout << k << ": " << length(k) << '\n';
  // }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    auto brute = [&]() -> void {
      for (int i = 0; i < N; i++) {
        A[(i + 1) % N] = max(A[(i + 1) % N] - A[i], 0);
      }
    };
    for (int i = 0; i < 100; i++) {
      brute();
    }

    vector<int> ans;
    auto split = [&](auto finish, int l, int r) -> void {
      int j = l;
      for (int i = l; i < r; i++) {
        if (A[i % N] == 0) {
          if (j < i) {
            finish(finish, j, i);
          }
          j = i + 1;
        }
      }
      if (j < r) {
        finish(finish, j, r);
      }
    };
    auto finish = [&](auto self, int l, int r) -> void {
      if (r - l == 1) {
        ans.push_back(l % N);
        return;
      }

      auto binom = [&](int n, int k) -> i128 {
        i128 rv = 1;
        for (int i = n - k + 1; i <= n; i++) {
          rv *= i;
        }
        for (int i = 1; i <= k; i++) {
          rv /= i;
        }
        return rv;
      };
      auto sum = [&](int i, int k) -> i128 {
        i128 rv = 0;
        for (int j = l; j <= i; j++) {
          rv += A[j % N] * binom(k - 1 + i - j, i - j) *
                (j % 2 == i % 2 ? 1 : -1);
        }
        return rv;
      };
      auto check = [&](int k) -> bool {
        for (int i = l; i < r; i++) {
          if (sum(i, k) <= 0) return true;
        }
        return false;
      };
      int l_ = 1, r_ = 1e9;
      while (l_ < r_) {
        int m = l_ + (r_ - l_) / 2;
        check(m) ? r_ = m : l_ = m + 1;
      }

      for (int i = r - 1; i >= l; i--) {
        A[i % N] = max(sum(i, l_), (i128) 0);
      }

      split(self, l, r);
    };
    int j = find(A.begin(), A.end(), 0) - A.begin();
    for (int i = 0; i < j; i++) {
      A[i + 1] = max(A[i + 1] - A[i], 0);
    }
    split(finish, j, j + N);

    cout << ans.size() << '\n';
    sort(ans.begin(), ans.end());
    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
