#include <bits/stdc++.h>

#include "ethankim8683/data_structures.hpp"

using namespace std;

using i64 = long long;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;
  K--;

  vector<int> L(N);
  for (auto &e : L) cin >> e;
  sort(L.rbegin(), L.rend());

  queue<tuple<int, int, int, int>> q;
  int t = 0;
  q.push({0, 1, -1, -1});
  range_add_fenwick_tree<i64> ft(1e6 + 1);
  ft.add(0, 1, 1);
  int ans = INF;
  while (q.size() > 0) {
    auto [d, s, i, j] = q.front();
    q.pop();
    // 1: white node
    // 2: white node, root
    if (s == 1) {
      if (t < N) {
        q.push({d + 1, 2, t, L[t] / 2});
        t++;
      }
    } else {
      ft.add(d - 1, d, -1);
      ft.add(d + 1, d + L[i] / 2 + 1, 1);
      ft.add(d + 1, d + L[i] - L[i] / 2, 1);
      int l = 0, r = 1e6;
      while (l < r) {
        int m = l + (r - l) / 2;
        ft.sum(0, m + 1) > K ? r = m : l = m + 1;
      }
      if (ft.sum(0, l + 1) > K) {
        ans = min(ans, l);
      }
      if (i == N - 1) break;
    }
    if (i != -1) {
      if (j <= L[i] / 2) {
        if (j - 1 >= 0) {
          q.push({d + 1, 1, i, j - 1});
        }
      }
      if (j >= L[i] / 2) {
        if (j + 1 < L[i]) {
          q.push({d + 1, 1, i, j + 1});
        }
      }
    }
  }
  cout << (ans == INF ? -1 : ans);
}
