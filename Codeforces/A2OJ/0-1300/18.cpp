#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("18.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U a;
  cin >> a;
  U a_min = a;
  U a_max = a;
  U result = 0;
  while (--n) {
    U a;
    cin >> a;
    if (a < a_min) {
      result++;
      a_min = a;
    }
    if (a > a_max) {
      result++;
      a_max = a;
    }
  }
  printf("%u\n", result);
  return 0;
}