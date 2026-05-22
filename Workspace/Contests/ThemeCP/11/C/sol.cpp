#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  int T = 100;
  while (T--) {
    int N = 16, M = 16, X1, Y1, X2, Y2;
    do {
      static mt19937 rng(time(nullptr));
      X1 = rng() % N;
      Y1 = rng() % M;
      X2 = rng() % N;
      Y2 = rng() % M;
    } while (X1 == X2 and Y1 == Y2);
    bool found1 = false, found2 = false;
#else
  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;
#endif

    auto dig = [&](int r, int c) -> int {
#ifdef ETHANKIM8683
      if (r == X1 and c == Y1) {
        found1 = true;
        return true;
      }
      if (r == X2 and c == Y2) {
        found2 = true;
        return true;
      }
      return false;
#else
      cout << "DIG " << r + 1 << ' ' << c + 1 << endl;
      int rv;
      cin >> rv;
      return rv;
#endif
    };

    auto scan = [&](int r, int c) -> int {
#ifdef ETHANKIM8683
      return abs(r - X1) + abs(c - Y1) + abs(r - X2) + abs(c - Y2);
#else
      cout << "SCAN " << r + 1 << ' ' << c + 1 << endl;
      int rv;
      cin >> rv;
      return rv;
#endif
    };

    f64 d1 = scan(0, 0) / 2.L, d2 = scan(N - 1, 0) / 2.L,
        y = (d1 + d2 - (N - 1)) / 2.L, x = d1 - y;
    int w = scan((int) x, 0) - 2.L * y, h = scan(0, (int) y) - 2.L * x;

    if (dig(x - w / 2.L, y - h / 2.L)) {
      dig(x + w / 2.L, y + h / 2.L);
    } else {
      dig(x + w / 2.L, y - h / 2.L);
      dig(x - w / 2.L, y + h / 2.L);
    }

#ifdef ETHANKIM8683
    cout << (found1 and found2 ? "ok" : "wa") << '\n';
#endif
  }
}
