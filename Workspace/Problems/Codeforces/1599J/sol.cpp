#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // if we solve for K, we solve for N >= K
  //
  // for odd K, we use K = 3
  //
  // for even K, we need to find two equally-sized sets with equal sum
  //
  // if we try sets of increasing size, we'll eventually find a pair with equal
  // sum after not too many iterations over Kmax(B) unique sums

#if defined(ETHANKIM8683) and 0
  mt19937 rng(time(nullptr));

  int N = rng() % ((int) 1e3 + 1 - 2) + 2;

  vector<int> B(N);
  for (auto &e : B) {
    e = rng() % (int) 5e5 * 2 + 1;
  }

  auto answer = [&](vector<int> ans) -> void {
    set<i64> S;
    for (int i = 0; i < ans.size(); i++) {
      for (int j = i + 1; j < ans.size(); j++) {
        S.insert(ans[i] + ans[j]);
      }
    }
    bool ok = true;
    for (auto e : B) {
      ok = ok and S.contains(e);
    }
    cout << (ok ? "ok" : "wa");
    exit(0);
  };
#else
  int N;
  cin >> N;

  vector<int> B(N);
  for (auto &e : B) cin >> e;

  auto answer = [&](vector<int> ans) -> void {
    cout << "YES\n";
    for (auto e : ans) {
      cout << e << ' ';
    }
    exit(0);
  };
#endif

  vector<int> by_parity[2];
  for (int i = 0; i < N; i++) {
    by_parity[B[i] % 2].push_back(i);
  }
  int x = -1, y, z;
  if (by_parity[0].size() >= 3) {
    x = by_parity[0][0];
    y = by_parity[0][1];
    z = by_parity[0][2];
  } else if (by_parity[0].size() >= 1 and by_parity[1].size() >= 2) {
    x = by_parity[1][0];
    y = by_parity[1][1];
    z = by_parity[0][0];
  }
  if (x != -1) {
    int a = (B[x] + B[y] - B[z]) / 2, b = B[x] - a, c = B[y] - a;
    vector<int> ans = {a, b, c};
    for (int i = 0; i < N; i++) {
      if (i == x or i == y or i == z) continue;
      ans.push_back(B[i] - a);
    }
    answer(ans);
  }

  if (N == 3) {
    cout << "NO";
    exit(0);
  }

  map<int, vector<int>> by_sum;
  vector<int> S;
  auto dfs = [&](auto self, int n, int k, int i, int sum) -> void {
    if (k == n) {
      if (by_sum.contains(sum)) {
        auto Sc = by_sum[sum];
        vector<int> T;
        for (int i = 0; i < n; i++) {
          T.push_back(S[i]);
          T.push_back(Sc[i]);
        }

        vector<int> ans = {0};
        for (int i = 0; i < 2 * n - 1; i++) {
          ans.push_back(B[T[i]] - ans.back());
        }

        sort(T.begin(), T.end());
        for (int i = 0; i < N; i++) {
          if (binary_search(T.begin(), T.end(), i)) continue;
          ans.push_back(B[i] - ans[0]);
        }

        answer(ans);
      }
      by_sum.insert({sum, S});
      return;
    }

    if (i < N) {
      self(self, n, k, i + 1, sum);
      S.push_back(i);
      self(self, n, k + 1, i + 1, sum + B[i]);
      S.pop_back();
    }
  };
  for (int n = 1; n <= N / 2; n++) {
    by_sum.clear();
    dfs(dfs, n, 0, 0, 0);
  }
  cout << "NO";
}
