#include <iostream>
#include <cstdio>
#include <unordered_map>

#define N 100000

using namespace std;

using I = int;
using Lli = long long int;

unordered_map<Lli, I> sieve;
Lli x_arr[N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("230b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    Lli x;
    cin >> x;
    sieve[x] = 0;
    x_arr[i] = x;
  }
  for (I i = 2; i <= 1e6; i++)
    for (auto& [x, count] : sieve)
      if (x != i && x % i == 0)
        count++;
  for (I i = 0; i < n; i++) {
    if (sieve[x_arr[i]] == 1)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}