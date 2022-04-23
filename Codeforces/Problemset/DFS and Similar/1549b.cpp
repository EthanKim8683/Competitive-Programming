#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

C as[200001];
C bs[200001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1549b.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    cin >> as;
    cin >> bs;
    U result = 0;
    for (U i = n; i--;) {
      if (bs[i] == '1') {
        const U l = i - 1;
        const U r = i + 1;
        if (r < n && as[r] == '1') {
          as[r] = 0;
          result++;
        } else if (as[i] == '0')
          result++;
        else if (l < n && as[l] == '1') {
          as[l] = 0;
          result++;
        }
      }
    }
    printf("%u\n", result);
  }
  return 0;
}