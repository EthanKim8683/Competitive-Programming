#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  int T = 100;
  while (T--) {
    static mt19937 rng(time(nullptr));
    int X = rng() % (int) 1e9 + 1;
#else
  int T;
  cin >> T;

  while (T--) {
#endif
    auto query = [&](int a, int b) -> int {
#ifdef ETHANKIM8683
      assert(1 <= a and a <= 2e9);
      assert(1 <= b and b <= 2e9);
      assert(a != b);
      return gcd((i64) X + a, (i64) X + b);
#else
      cout << "? " << a << ' ' << b << endl;
      int rv;
      cin >> rv;
      return rv;
#endif
    };

    auto answer = [&](int x) -> void {
#ifdef ETHANKIM8683
      cerr << (x == X ? "ok" : "wa") << '\n';
#else
      cout << "! " << x << endl;
#endif
    };

    int a = 1 << 30;
    for (int i = 0; i < 29; i++) {
      if (query(a, a + (1 << (i + 1))) != (1 << (i + 1))) {
        a -= 1 << i;
      }
    }
    if (query(a, a + 3) == 3) {
      a -= 1 << 29;
    }
    answer((1 << 30) - a);
  }
}
