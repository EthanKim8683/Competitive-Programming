#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 1e5;

Lli d_arr[2 * N];
Lli difs[N];

Lli div(Lli a, Lli b, B& res) {
  res &= a % b == 0;
  return a / b;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    for (I i = 0; i < 2 * n; i++)
      cin >> d_arr[i];
    sort(d_arr, d_arr + 2 * n);
    B res = true;
    Lli tot = 0;
    for (I i = 0, j = n; i < n; i++, j--) {
      res &= d_arr[i * 2] != 0;
      res &= d_arr[i * 2] == d_arr[i * 2 + 1];
      if (i > 0) {
        difs[i] = div(d_arr[i * 2] - d_arr[(i - 1) * 2], i * 2, res);
        tot += j * difs[i];
        res &= difs[i] != 0;
      }
    }
    res &= div(d_arr[0] - tot * 2, n * 2, res) > 0;
    if (res)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}