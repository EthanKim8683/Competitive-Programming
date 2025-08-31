#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int S, K;
    cin >> S >> K;

    // last digit 0 -> no more op 2
    //
    // do accumulate first, then get discount

    i64 ans = 0;
    int rep[] = {0, 2, 4, 6, 8};
    while (!binary_search(rep, rep + 5, S % 10) and K > 0) {
      ans = max(ans, (i64) S * K);
      S += S % 10;
      K--;
    }

    vector<int> accums;
    int v = S % 10, s = 0;
    do {
      s += v;
      accums.push_back(s);
      (v += v) %= 10;
    } while (v != S % 10);
    int p = accums.size();

    auto solve = [&](int i) -> i64 {
      return (S + (i64) i / p * accums.back() +
              (i % p == 0 ? 0 : accums[i % p - 1])) *
             (K - i);
    };

    auto solve2 = [&](int i) -> vector<i64> {
      vector<i64> rv(p);
      for (int j = 0; j < p; j++) {
        rv[(i + j) % p] = solve(i + j);
      }
      return rv;
    };

    int l = 0, r = K;
    while (l < r) {
      int m = l + (r - l) / 2;
      solve2(m + 1) >= solve2(m) ? l = m + 1 : r = m;
    }
    auto a = solve2(l);
    ans = max(ans, *max_element(a.begin(), a.end()));
    cout << ans << '\n';
  }
}
