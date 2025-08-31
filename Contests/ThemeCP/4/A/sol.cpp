#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    i64 N;
    cin >> N;
    N >>= countr_zero((u64) N);

    auto tri = [&](i64 x) -> i128 { return (i128) x * (x + 1) / 2; };
    i64 ans = -1;
    for (i64 i = 2; tri(i) <= N; i *= 2) {
      if ((N - tri(i)) % i == 0) {
        ans = i;
        break;
      }
    }
    if (ans != -1) {
      cout << ans << '\n';
      continue;
    }
    cout << "-1\n";
  }
}
