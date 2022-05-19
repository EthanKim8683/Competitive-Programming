#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 1.5e6;
const I A = N;

I a_arr[N];
I cnts[A + 1];
I mex;

void add(I i) {
  cnts[i]++;
}

void rmv(I i) {
  if (--cnts[i] == 0)
    mex = min(mex, i);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("mex.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < m; i++)
    add(a_arr[i]);
  for (I i = 0; i <= A; i++) {
    if (cnts[i] == 0) {
      mex = i;
      break;
    }
  }
  for (I i = 0; i + m < n; i++) {
    add(a_arr[i + m]);
    rmv(a_arr[i]);
  }
  printf("%i\n", mex);
  return 0;
}