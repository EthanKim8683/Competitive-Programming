#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int MAXM = 2e5;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> B(N);
  for (auto &e : B) cin >> e;

  vector<tuple<int, int, int>> sizes = {{-1, N, 0}};
  vector<pair<int, int>> stack1 = {{0, 0}};
  int s = min_element(B.begin(), B.end()) - B.begin();
  for (int i = 1; i <= N; i++) {
    int delta = B[(s + i) % N] - B[(s + i + N - 1) % N];
    if (delta > 0) {
      stack1.emplace_back(i - 1, delta);
    } else {
      delta = -delta;
      while (delta > 0) {
        auto &[l, total] = stack1.back();
        int d = min(delta, total);
        sizes.emplace_back(l, i - 1, d);
        delta -= d;
        total -= d;
        if (total == 0) {
          stack1.pop_back();
        }
      }
    }
  }
  sort(sizes.begin(), sizes.end(),
       [&](tuple<int, int, int> a, tuple<int, int, int> b) -> bool {
         auto key = [&](tuple<int, int, int> size) -> pair<int, int> {
           auto [l, r, d] = size;
           return {r, -l};
         };
         return key(a) < key(b);
       });
  vector<vector<int>> adj(sizes.size());
  vector<int> stack2;
  for (int i = 0; i < sizes.size(); i++) {
    auto [l1, r1, d1] = sizes[i];
    while (stack2.size() > 0) {
      int j = stack2.back();
      auto [l2, r2, d2] = sizes[j];
      if (r2 < l1) break;
      stack2.pop_back();
      adj[i].push_back(j);
    }
    stack2.push_back(i);
  }

  auto dfs = [&](auto self, int a) -> void {
    for (auto b : adj[a]) {
    }
  };
}
