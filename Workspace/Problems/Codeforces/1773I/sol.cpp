#include <bits/stdc++.h>

#include "atcoder/convolution.hpp"

using namespace std;
using namespace atcoder;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // vector<array<int, 10>> trie;
  // trie.push_back({});
  vector<int> F = {1};
  f64 avg = 0;
  for (int n = 1; n <= 5982; n++) {
    vector<int> N;
    for (int i = n; i > 0; i /= 10) {
      N.push_back(i % 10);
    }
    F = convolution(F, N);
    for (int i = 0; i < F.size(); i++) {
      if (F[i] >= 10) {
        if (i + 1 == F.size()) {
          F.push_back(0);
        }
        F[i + 1] += F[i] / 10;
        F[i] %= 10;
      }
    }

    // int a = 0;
    // for (int i = 0; i < 20000; i++) {
    //   int d = i < F.size() ? F[i] : 0;
    //   if (trie[a][d] == 0) {
    //     trie[a][d] = trie.size();
    //     trie.push_back({});
    //   }
    //   a = trie[a][d];
    // }

    f64 p = 0;
    int k = 0;
    bool ok = false;
    for (int i = 0; i + 1 < F.size(); i++) {
      if (F[i] != 0) {
        ok = true;
      }
      if (ok) {
        p += F[i] == 0 and F[i + 1] == 0;
        k++;
      }
    }
    if (k != 0) {
      p /= k;
    }
    avg += p;
  }
  avg /= 5982;
  cerr << avg;

  // int max_splits = 0;
  // map<int, int> by_depth;
  // auto dfs = [&](auto self, int a, int depth, int splits) -> void {
  //   int ch = 0;
  //   for (auto b : trie[a]) {
  //     ch += b != 0;
  //   }
  //   if (ch >= 2) {
  //     by_depth[depth]++;
  //     splits++;
  //   }
  //   max_splits = max(max_splits, splits);
  //   for (auto b : trie[a]) {
  //     if (b == 0) continue;
  //     self(self, b, depth + 1, splits);
  //   }
  // };
  // dfs(dfs, 0, 0, 0);
  // cout << max_splits << '\n';
  // cout << by_depth.size() << '\n';
  // for (auto [depth, count] : by_depth) {
  //   cout << depth << ' ' << count << '\n';
  // }

  // vector<int> ans(1e7, -1), F = {1};
  // for (int n = 1; n <= 5982; n++) {
  //   vector<int> N;
  //   for (int i = n; i > 0; i /= 10) {
  //     N.push_back(i % 10);
  //   }
  //   F = convolution(F, N);
  //   for (int i = 0; i < F.size(); i++) {
  //     if (F[i] >= 10) {
  //       if (i + 1 == F.size()) {
  //         F.push_back(0);
  //       }
  //       F[i + 1] += F[i] / 10;
  //       F[i] %= 10;
  //     }
  //   }

  //   int key = 0;
  //   for (int i = 0; i < 7; i++) {
  //     key = key * 10 + (i < F.size() ? F[F.size() - 1 - i] : 0);
  //   }
  //   ans[key] = n;
  // }

  // int T;
  // cin >> T;

  // while (T--) {
  //   int key = 0;
  //   for (int i = 0; i < 7; i++) {
  //     cout << "? " << i << endl;
  //     int d;
  //     cin >> d;
  //     key = key * 10 + d;
  //   }
  //   cout << "! " << ans[key] << endl;
  //   string ok;
  //   cin >> ok;
  //   if (ok == "NO") exit(0);
  // }
}
