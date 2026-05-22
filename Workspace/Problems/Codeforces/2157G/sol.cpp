#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

const f64 INF = 1e300;

int main(int argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 30;
  } else {
    cin >> T;
  }

  f64 Q = 0;
  while (T--) {
    int N;
    if (argc > 1) {
      N = 100;
    } else {
      cin >> N;
      if (N == -2) exit(0);
    }

    vector<int> A;
    if (argc > 1) {
      A.resize(N);
      for (auto &e : A) {
        e = rng() % (1 << 30);
      }
    }

    map<pair<int, int>, int> memo;
    auto query = [&](int u, int v) -> int {
      pair<int, int> key = {u, v};
      if (memo.contains(key)) return memo[key];
      Q += 1.L / (v - u + 1);
      assert(Q <= 300);
      int rv;
      if (argc > 1) {
        int sum = 0;
        for (int i = u; i <= v; i++) {
          sum ^= A[i];
        }
        rv = sum == 0 ? -1 : __lg(sum);
      } else {
        cout << "? " << u + 1 << ' ' << v + 1 << endl;
        cin >> rv;
        if (rv == -2) exit(0);
      }
      memo[key] = rv;
      return rv;
    };

    auto answer = [&](vector<vector<int>> ans) -> void {
      if (argc > 1) {
        for (int i = 0; i < N; i++) {
          int sum = 0;
          for (int j = i; j < N; j++) {
            sum ^= A[j];
            assert(ans[i][j] == (sum == 0 ? -1 : __lg(sum)));
          }
        }
      } else {
        cout << '!';
        for (int i = 0; i < N; i++) {
          cout << '\n';
          for (int j = i; j < N; j++) {
            cout << ans[i][j] << ' ';
          }
        }
        cout << endl;
      }
    };

    vector ans(N, vector<int>(N, -2));
    auto dfs = [&](auto self, vector<pair<int, int>> ranges) -> void {
      int n = ranges.size();
      if (n == 0) return;

      vector<int> ps1(n);
      for (int i = 0; i < n; i++) {
        int l1 = ranges[0].first, r1 = ranges[n - 1].second,
            r2 = ranges[i].second;
        if (r2 - l1 + 1 >= r1 - (r2 + 1) + 1) {
          ps1[i] = query(l1, r2);
        } else {
          ps1[i] = query(r2 + 1, r1);
        }
      }

      int x = *max_element(ps1.begin(), ps1.end());

      vector<int> ps2(n + 1);
      ps2[0] = 0;
      for (int i = 0; i < n; i++) {
        int l1 = ranges[0].first, r1 = ranges[n - 1].second,
            r2 = ranges[i].second;
        if (r2 - l1 + 1 >= r1 - (r2 + 1) + 1) {
          ps2[i + 1] = ps1[i] == x ? 1 : 0;
        } else {
          ps2[i + 1] = (ps1[i] == x) != (ps1[n - 1] == x) ? 1 : 0;
        }
      }

      for (int i = 0; i < n; i++) {
        if ((ps2[i + 1] ^ ps2[i]) == 0) continue;
        auto [l, r] = ranges[i];
        ans[l][r] = x;
      }

      vector<pair<int, int>> ranges1, ranges2;
      int l1 = -1, l2 = -1;
      for (int i = 0; i < n; i++) {
        auto [l, r] = ranges[i];
        if (ps2[i] == 0) {
          l1 = l;
        } else {
          l2 = l;
        }
        if (ps2[i + 1] == 0) {
          if (l1 != -1) {
            ranges1.emplace_back(l1, r);
          }
        } else {
          if (l2 != -1) {
            ranges2.emplace_back(l2, r);
          }
        }
      }
      self(self, ranges1);
      self(self, ranges2);
    };
    vector<pair<int, int>> ranges(N);
    for (int i = 0; i < N; i++) {
      ranges[i] = {i, i};
    }
    dfs(dfs, ranges);

    for (int i = 0; i < N; i++) {
      for (int j = N - 1; j >= i; j--) {
        int k = i;
        while (k <= j) {
          int l = j;
          while (ans[k][l] == -2) {
            l--;
          }
          ans[i][j] = max(ans[i][j], ans[k][l]);
          k = l + 1;
        }
      }
    }
    answer(ans);
  }
}
