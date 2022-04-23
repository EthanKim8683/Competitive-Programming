#include <iostream>
#include <cstdio>
#include <unordered_map>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using I = int;
using Lli = long long int;

unordered_map<Lli, Llu> beauty;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("61.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U min_beauty = -1;
  U max_beauty = 0;
  for (U i = n; i--;) {
    U b;
    cin >> b;
    min_beauty = min(min_beauty, b);
    max_beauty = max(max_beauty, b);
    beauty[b]++;
  }
  const U diff = max_beauty - min_beauty;
  if (diff) {
    Llu result = 0;
    for (auto it = beauty.begin(); it != beauty.end();) {
      const auto [b, count] = *it;
      const Lli b_lo = b - diff;
      const Lli b_hi = b + diff;
      const auto it_lo = beauty.find(b_lo);
      const auto it_hi = beauty.find(b_hi);
      if (it_lo != beauty.end())
        result += it_lo->second * count;
      if (it_hi != beauty.end())
        result += it_hi->second * count;
      it = beauty.erase(it);
    }
    printf("%u %llu\n", diff, result);
  } else
    printf("0 %llu\n", (Llu) (n - 1) * (Llu) n / 2llu);
  return 0;
}