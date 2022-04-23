#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using C = char;

C s[100000];
U counts[100000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("97.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  cin >> s;
  sort(s, s + n);
  U length = 0;
  for (U i = 0; i < n;) {
    const auto card = s[i];
    U count = 1;
    while (++i < n && s[i] == card)
      count++;
    counts[length] = count;
    length++;
  }
  sort(counts, counts + length);
  Llu result = 0;
  for (U i = length; i-- && k;) {
    const auto count = counts[i];
    const U give = min(count, k);
    k -= give;
    result += (Llu) give * (Llu) give;
  }
  printf("%llu\n", result);
  return 0;
}