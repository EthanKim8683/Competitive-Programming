#include <iostream>
#include <cstdio>
 
using namespace std;
 
using U = unsigned;
using I = int;
using Lli = long long int;
 
I as[25];
I bs[25];
 
int main(void) {
#if defined(ETHANKIM8683)
  freopen("a.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    for (U i = n; i--;)
      cin >> as[i];
    for (U i = n; i--;)
      cin >> bs[i];
    I a_l = as[0];
    I b_l = bs[0];
    Lli result = 0;
    for (U i = 1; i < n; i++) {
      const auto a = as[i];
      const auto b = bs[i];
      const I aa_d = abs(a - a_l);
      const I bb_d = abs(b - b_l);
      const I ab_d = abs(a - b_l);
      const I ba_d = abs(b - a_l);
      if (aa_d - ab_d + bb_d - ba_d > 0) {
        result += ab_d + ba_d;
        a_l = b;
        b_l = a;
      } else {
        result += aa_d + bb_d;
        a_l = a;
        b_l = b;
      }
    }
    printf("%lli\n", result);
  }
  return 0;
}