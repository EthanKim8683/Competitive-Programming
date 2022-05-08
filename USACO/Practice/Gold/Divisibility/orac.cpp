#include <iostream>
#include <cstdio>

using namespace std;

using I = unsigned;
using Lli = long long int;

const I N = 100000;
const I A = 200000;

I a_arr[N];
I facs[A + 1][19];

int main(void) {
#ifdef ETHANKIM8683
  freopen("orac.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++) {
    auto a = a_arr[i];
    for (I j = 2; j * j <= a; j++) {
      I fac = 0;
      while (a % j == 0) {
        facs[j][fac]++;
        a /= j;
        fac++;
      }
    }
    if (a > 1)
      facs[a][0]++;
  }
  Lli res = 1;
  for (I i = 2; i <= A; i++) {
    I ind = 0;
    Lli mul = 1;
    while (facs[i][ind] >= n - 1) {
      mul *= i;
      ind++;
    }
    res *= mul;
  }
  printf("%lli\n", res);
  return 0;
}