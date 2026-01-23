#include <bits/stdc++.h>

using namespace std;

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
      N = 4, K = 5;
    } else {
      cin >> N >> K;
    }

    vector<int> A(N);
    if (argc > 1) {
      for (auto &e : A) {
        e = rng() % (K + 1);
      }
    } else {
      for (auto &e : A) cin >> e;
    }

    vector<tuple<int, int, int>> ans;
    auto op = [&](int i, int j, int x) -> void {
      assert(A[i] + A[j] == K);
      ans.emplace_back(i, j, x);
      A[i] -= x;
      A[j] += x;
    };

    map<int, vector<int>> stacks;
    pair<int, int> match = {-1, -1};
    for (int i = 0; i < N; i++) {
      auto &stack = stacks[K - A[i]];
      if (stack.size() > 0) {
        int j = stack.back();
        stack.pop_back();

        if (match != pair{-1, -1}) {
          auto [iprev, jprev] = match;
          op(jprev, iprev, K / 2 - A[iprev]);
        }
        match = {j, i};
      } else {
        stacks[A[i]].push_back(i);
      }
    }
    if (match == pair{-1, -1}) {
      cout << (is_sorted(A.begin(), A.end()) ? 0 : -1) << '\n';
      continue;
    }
    auto [iswap, jswap] = match;

    auto key = [&](int i) -> int {
      if (i == iswap) return K / 2;
      if (i == jswap) return K - K / 2;
      return A[i];
    };
    vector<int> order(N);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(),
         [&](int a, int b) -> bool { return key(a) < key(b); });

    vector<int> index(N);
    for (int i = 0; i < N; i++) {
      index[order[i]] = i;
    }

    if (index[iswap] == jswap or index[jswap] == iswap) {
      swap(iswap, jswap);
    }
    if (iswap != index[iswap]) {
      int i = index[iswap];
      op(jswap, iswap, A[i] - A[iswap]);
      index[iswap] = index[i];
      iswap = i;
    }
    if (jswap != index[jswap]) {
      int j = index[jswap];
      op(iswap, jswap, A[j] - A[jswap]);
      index[jswap] = index[j];
      jswap = j;
    }
    if (iswap > jswap) {
      swap(iswap, jswap);
    }

    vector<bool> seen(N, false);
    auto dfs = [&](auto self, int i) -> void {
      if (seen[i]) return;
      seen[i] = true;

      int t = A[i];
      self(self, index[i]);
      op(jswap, index[i], t - A[index[i]]);
    };
    for (int i = 0; i < N; i++) {
      if (i == iswap or i == jswap) continue;
      if (i == index[i]) continue;
      if (seen[i]) continue;

      op(jswap, iswap, A[i] - A[iswap]);
      dfs(dfs, i);
    }
    op(jswap, iswap, K / 2 - A[iswap]);
    assert(is_sorted(A.begin(), A.end()));

    cout << ans.size() << '\n';
    for (auto [i, j, x] : ans) {
      cout << i + 1 << ' ' << j + 1 << ' ' << x << '\n';
    }
  }
}
