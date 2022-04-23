#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <algorithm>

using namespace std;

using U = unsigned;

unordered_map<U, pair<U, U>> xs;
pair<U, U> results[100000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("62.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  for (U i = 1; i <= n; i++) {
    U x;
    cin >> x;
    auto &[l, p] = xs[x];
    if (p) {
      if (i - l != p)
        p = -1;
    } else if (l)
      p = i - l;
    l = i;
  }
  U length = 0;
  for (const auto& [x, info] : xs) {
    const auto [l, p] = info;
    if (p != -1) {
      auto& result = results[length];
      result.first = x;
      result.second = p;
      length++;
    }
  }
  sort(results, results + length);
  printf("%u\n", length);
  for (U i = 0; i < length; i++) {
    const auto [x, p] = results[i];
    printf("%u %u\n", x, p);
  }
  return 0;
}