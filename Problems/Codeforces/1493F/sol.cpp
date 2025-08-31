#include <bits/stdc++.h>

#include "ethankim8683/algebra.hpp"

using namespace std;

using u32 = unsigned;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  auto query = [&](int h, int w, int i1, int j1, int i2, int j2) -> bool {
    cout << "? " << h << ' ' << w << ' ' << i1 + 1 << ' ' << j1 + 1 << ' '
         << i2 + 1 << ' ' << j2 + 1 << endl;
    int rv;
    cin >> rv;
    return rv;
  };

  auto answer = [&](int x) -> void {
    cout << "! " << x << endl;
    exit(0);
  };

  auto solve = [&](int N, auto query) -> int {
    map<int, int> counts;
    for (auto f : factorize((u32) N)) {
      counts[f]++;
    }
    int g = N;
    for (auto [f, count] : counts) {
      int n = N;
      for (int i = 1; i <= count; i++) {
        n /= f;

        bool ok;
        if (f == 2) {
          ok = query(n, 0, n);
        } else {
          int k = N / n / 2;
          ok = query(k * n, 0, k * n) and query(k * n, 0, (k + 1) * n);
        }
        if (!ok) break;

        g = gcd(g, n);
      }
    }

    int rv = 0;
    for (int i = g; i <= N; i += g) {
      if (N % i == 0) {
        rv++;
      }
    }
    return rv;
  };
  answer(solve(N, [&](int h, int i1,
                      int i2) { return query(h, M, i1, 0, i2, 0); }) *
         solve(M, [&](int w, int j1, int j2) {
           return query(N, w, 0, j1, 0, j2);
         }));
}
