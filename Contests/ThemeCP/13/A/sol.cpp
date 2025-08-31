#include <bits/stdc++.h>

#include "ethankim8683/algebra.hpp"

using namespace std;

using u32 = unsigned;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> ans(N);
    if (N < 6) {
      int v = 1;
      for (int i = 0; i < N; i++) {
        v += i % 2 == 1;
        ans[i] = v;
      }
    } else {
      for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
          ans[i] = i / 2 % 2 == 0 ? 1 : 2;
        } else {
          ans[i] = i / 2 % 2 == 0 ? 3 : 4;
        }
      }
    }
    map<int, int> cc;
    for (auto e : ans) {
      cc[e] = 0;
    }
    int t = 1;
    for (auto &[k, v] : cc) {
      v = t++;
    }
    for (auto &e : ans) {
      e = cc[e];
    }

    cout << cc.size() << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';

    // bool ok = true;
    // for (int i = 1; i <= N; i++) {
    //   for (int j = i + 1; j <= N; j++) {
    //     if (is_prime((u32) (i ^ j))) {
    //       ok = ok and ans[i - 1] != ans[j - 1];
    //     }
    //   }
    // }
    // cout << (ok ? "ok" : "wa") << '\n';
  }
}
