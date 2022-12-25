#include <iostream>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 2e5;

I a_arr[N];
I inds[N];
I reps[N];
I sizs[N];
B viss[N];

B cmp(I a, I b) {
  return a_arr[a] < a_arr[b];
}

I fnd(I i) {
  if (reps[i] == -1)
    return i;
  return reps[i] = fnd(reps[i]);
}

void uni(I a, I b) {
  a = fnd(a);
  b = fnd(b);
  if (a == b)
    return;
  if (sizs[a] < sizs[b]) {
    const I t = a;
    a = b;
    b = t;
  }
  reps[b] = a;
  sizs[a] += sizs[b];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("gcd.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, p;
    cin >> n >> p;
    fill_n(reps, n, -1);
    fill_n(sizs, n, 1);
    fill_n(viss, n, false);
    for (I i = 0; i < n; i++)
      inds[i] = i;
    for (I i = 0; i < n; i++)
      cin >> a_arr[i];
    sort(inds, inds + n, cmp);
    Lli res = 0;
    for (I i = 0; i < n; i++) {
      const auto j = inds[i];
      if (!viss[j]) {
        const auto a = a_arr[j];
        if (a >= p)
          break;
        for (I k = j - 1; k >= 0 && gcd(a, a_arr[k]) == a; k--) {
          uni(j, k);
          res += a;
          if (viss[k])
            break;
          viss[k] = true;
        }
        for (I k = j + 1; k < n && gcd(a, a_arr[k]) == a; k++) {
          uni(j, k);
          res += a;
          if (viss[k])
            break;
          viss[k] = true;
        }
      }
    }
    I cnt = 0;
    for (I i = 0; i < n; i++)
      cnt += reps[i] == -1;
    res += (Lli) p * (cnt - 1);
    printf("%lli\n", res);
  }
  return 0;
}