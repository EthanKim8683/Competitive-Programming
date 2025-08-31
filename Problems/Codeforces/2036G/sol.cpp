#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  int T = 1;
  while (T--) {
    static mt19937_64 rng(time(nullptr));
    i64 N = rng() % ((i64) 1e18 + 1 - 3) + 2, A, B, C;
    // do {
    //   A = rng() % N + 1;
    //   B = rng() % N + 1;
    //   C = rng() % N + 1;
    // } while (A == B or B == C or A == C);
    do {
      A = rng() % N + 1;
      B = rng() % N + 1;
      C = A ^ B;
    } while (A == B or B == C or A == C);
    int qcnt = 0;
#else
  int T;
  cin >> T;

  while (T--) {
    i64 N;
    cin >> N;
#endif

    auto query = [&](i64 l, i64 r) -> i64 {
      cout << "xor " << l << ' ' << r << endl;
#ifdef ETHANKIM8683
      qcnt++;
      if (qcnt > 150) {
        cout << "query limit exceeded";
        exit(0);
      }

      // you always get the xor of the included stolen tomes
      i64 rv = 0;
      for (auto x : {A, B, C}) {
        if (l <= x and x <= r) {
          rv ^= x;
        }
      }
      return rv;
#else
      i64 rv;
      cin >> rv;
      if (rv == -1) exit(0);
      return rv;
#endif
    };
    auto answer = [&](i64 a, i64 b, i64 c) -> void {
      cout << "ans " << a << ' ' << b << ' ' << c << endl;
#ifdef ETHANKIM8683
      auto tup = [&](i64 a, i64 b, i64 c) -> array<i64, 3> {
        if (a > b) swap(a, b);
        if (b > c) swap(b, c);
        if (a > b) swap(a, b);
        return {a, b, c};
      };
      cout << (tup(a, b, c) == tup(A, B, C) ? "ok" : "wa") << '\n';
#endif
    };

    auto sum = query(1, N);

    if (sum != 0) {
      i64 l = 1, r = N;
      while (l < r) {
        i64 m = l + (r - l) / 2;
        query(1, m) == 0 ? l = m + 1 : r = m;
      }
      auto sum2 = query(1, l);

      r = N;
      while (l < r) {
        i64 m = l + (r - l) / 2;
        query(1, m) == sum2 ? l = m + 1 : r = m;
      }
      auto sum3 = query(1, l);

      answer(sum2, sum3 ^ sum2, sum ^ sum3);
      continue;
    }

    i64 j;
    i64 sum2;
    for (int i = __lg(N); i >= 0; i--) {
      j = (1ll << i) - 1;
      sum2 = query(1, j);
      if (sum2 != 0) break;
    }

    i64 l = j + 1, r = N;
    while (l < r) {
      i64 m = l + (r - l + 1) / 2;
      query(j + 1, m) == sum2 ? r = m - 1 : l = m;
    }
    auto sum3 = query(j + 1, l);

    answer(sum2, sum3, sum2 ^ sum3);
  }
}
