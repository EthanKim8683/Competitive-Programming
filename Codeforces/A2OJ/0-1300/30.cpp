#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

pair<U, U> as[100000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("30.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  const U x = n - 1;
  for (U i = n; i--;) {
    auto& a = as[i];
    cin >> a.first;
    a.second = i;
  }
  sort(as, as + n);
  U m;
  cin >> m;
  Llu vasya = 0;
  Llu petya = 0;
  while (m--) {
    U b;
    cin >> b;
    U l = 0;
    U r = x;
    while (l < r) {
      const U m = l + (r - l) / 2;
      if (as[m].first < b)
        l = m + 1;
      else
        r = m;
    }
    const U i = as[l].second;
    vasya += 1 + x - i;
    petya += 1 + i;
  }
  printf("%llu %llu\n", vasya, petya);
  return 0;
}