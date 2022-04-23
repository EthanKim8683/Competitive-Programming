#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C s[50];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("10.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  cin >> s;
  U result = 0;
  for (U i = 0; i < n;) {
    const auto c = s[i];
    while (++i < n && s[i] == c)
      result++;
  }
  printf("%u\n", result);
  return 0;
}