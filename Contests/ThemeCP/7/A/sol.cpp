#include <bits/stdc++.h>

#include "ethankim8683/algebra.hpp"

using namespace std;

using u32 = unsigned;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    auto to_counts = [&](auto F) -> map<int, int> {
      map<int, int> rv;
      for (auto p : F) {
        rv[p]++;
      }
      return rv;
    };
    auto F0 = to_counts(factorize((u32) N)), F = F0;

    while (Q--) {
      int k;
      cin >> k;

      if (k == 1) {
        int x;
        cin >> x;

        for (auto [p, count] : to_counts(factorize((u32) x))) {
          F[p] += count;
        }
        int d = 1;
        for (auto [p, count] : F) {
          d *= count + 1;
        }
        bool ok = true;
        for (auto [p, count] : to_counts(factorize((u32) d))) {
          ok = ok and count <= F[p];
        }
        cout << (ok ? "YES" : "NO") << '\n';
      } else {
        F = F0;
      }
    }
    cout << '\n';
  }
}
