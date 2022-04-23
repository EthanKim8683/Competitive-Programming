#include <iostream>
#include <cstdio>
#include <vector>

#define MOD 1000000007
#define N 200000

using namespace std;

using I = int;
using Lli = long long int;

I a_arr[N];
I visited[N];
Lli pows[N + 1];
I start;
I total;

void dfs(I a, I p = -1) {
  visited[a] = 1;
  total++;
  const auto b = a_arr[a];
  if (visited[b]) {
    if (visited[b] == 1)
      start = b;
  } else
    dfs(b, a);
  visited[a] = 2;
}

Lli mod(Lli x) {
  return x % MOD + (x < 0) * MOD;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("711d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    a_arr[i] = a - 1;
  }
  Lli pow = 1;
  for (I i = 0; i <= n; i++) {
    pows[i] = pow;
    pow = mod(pow * 2);
  }
  Lli result = 1;
  I factor = 0;
  for (I i = n; i--;) {
    if (!visited[i]) {
      start = -1;
      total = 0;
      dfs(i);
      if (start != -1) {
        I cycle = 0;
        I end = start;
        do {
          cycle++;
          end = a_arr[end];
        } while (end != start);
        result = mod(result * (pows[cycle] - 2));
        total -= cycle;
      }
      factor += total;
    }
  }
  printf("%lli\n", mod(result * pows[factor]));
  return 0;
}