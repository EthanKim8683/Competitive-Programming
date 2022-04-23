#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using D = double;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("15.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  U sum = 0;
  for (U i = n; i--;) {
    U p;
    cin >> p;
    sum += p;
  }
  printf("%f\n", (D) sum / (D) n);
  return 0;
}