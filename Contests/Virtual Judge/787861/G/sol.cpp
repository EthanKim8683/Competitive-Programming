#include <bits/stdc++.h>

using namespace std;

using i128 = __int128;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // repeated binary search

  int N, S, Q;
  cin >> N >> S >> Q;

  vector<int> P(N);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  auto binom = [&](int n, int k) -> i128 {
    i128 rv = 1;
    for (int i = n - k + 1; i <= n; i++) {
      rv *= i;
    }
    for (int i = 1; i <= k; i++) {
      rv /= i;
    }
    return rv;
  };

  auto size = [&](int n, int s) -> i128 { return binom(n + s - 1, s); };

  auto count_ge = [&](int n, int s, int k) -> i128 { return size(n - k, s); };

  auto count_eq = [&](int n, int s, int k) -> i128 {
    return count_ge(n, s, k + 1) - count_ge(n, s, k);
  };

  while (Q--) {
    int k, a;
    cin >> k >> a;
    k--;
  }
}
