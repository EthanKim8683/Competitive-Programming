#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;

U shoes[4];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("21.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  for (U i = 4; i--;)
    cin >> shoes[i];
  sort(shoes, shoes + 4);
  U i = 0;
  U result = 0;
  while (i < 4) {
    const U shoe = shoes[i];
    while (++i < 4 && shoes[i] == shoe)
      result++;
  }
  printf("%u\n", result);
  return 0;
}