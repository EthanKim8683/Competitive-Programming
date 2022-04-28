#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;

vector<I> ress;

int main(void) {
#ifdef ETHANKIM8683
  freopen("modulo.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli fac = 1;
  for (I i = 1; i < n; i++) {
    if (gcd(i, n) == 1) {
      ress.push_back(i);
      fac = fac * i % n;
    }
  }
  I cnt = ress.size();
  I exc = 0;
  if (fac != 1) {
    cnt--;
    exc = fac;
  }
  printf("%i\n", cnt);
  for (const auto res : ress)
    if (res != exc)
      printf("%i ", res);
  return 0;
}