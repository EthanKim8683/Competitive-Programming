#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    // I just need min_left-ish method

    // vector<vector<int>> T(N);
    // vector<int> S;
    // for (int i = 0; i < N; i++) {
    //   for (auto &e : S) {
    //     if (e > A[i] - i) {
    //       e--;
    //     }
    //   }
    //   S.push_back(A[i] - i);
    //   for (auto e : S) {
    //     T[i].push_back(e + i);
    //   }
    // }
    // S.clear();
    // for (int i = N - 1; i >= 0; i--) {
    //   for (auto &e : S) {
    //     if (e > A[i] + i) {
    //       e--;
    //     }
    //   }
    //   for (auto e : S) {
    //     T[i].push_back(e - i);
    //   }
    //   S.push_back(A[i] + i);
    // }
    // int ans = 0;
    // for (auto r : T) {
    //   sort(r.begin(), r.end());
    //   ans = max(ans, r[K]);
    // }
    // cout << ans << '\n';

    auto f = [&](auto &cut, int x) -> int {
      return x - cut.order_of_key({x + 1, -1});
    };
    auto g = [&](auto &cut, int x) -> int {
      int l = x, r = x + cut.size();
      while (l < r) {
        int m = l + (r - l) / 2;
        f(cut, m) >= x ? r = m : l = m + 1;
      }
      return l;
    };

    int t = 0;
    ordered_set<pair<int, int>> cut, cost;
    vector<pair<int, int>> cuts(N), costs(N);
    for (int i = N - 1; i >= 0; i--) {
      cut.insert(cuts[i] = {g(cut, A[i] + i) + 1, t++});
      cost.insert(costs[i] = {g(cut, A[i] + i), t++});
    }

    ordered_set<pair<int, int>> cut2, cost2;
    int ans = 0;
    for (int i = 0; i < N; i++) {
      int l = 0, r = A[i];
      while (l < r) {
        int m = l + (r - l + 1) / 2;
        cost.order_of_key({g(cut, m + i - 1), -1}) +
                    cost2.order_of_key({g(cut2, m - i - 1), t}) <=
                K
            ? l = m
            : r = m - 1;
      }
      ans = max(ans, l);

      cut2.insert({g(cut2, A[i] - i) + 1, t++});
      cost2.insert({g(cut2, A[i] - i), t++});
      cut.erase(cuts[i]);
      cost.erase(costs[i]);
    }
    cout << ans << '\n';
  }
}
