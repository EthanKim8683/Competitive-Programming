#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I K = 1e5;

I a_arr[K];
vector<I> odds;
vector<I> eves;

I fix(I x) {
  if (x < 2)
    return 0;
  return x;
}

I odd(I x) {
  return x - 1 + x % 2;
}

I eve(I x) {
  return x - x % 2;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m, k;
    cin >> n >> m >> k;
    for (I i = 0; i < k; i++)
      cin >> a_arr[i];
    sort(a_arr, a_arr + k, greater<I>());
    if (a_arr[0] > (Lli) n * m) {
      printf("Yes\n");
      continue;
    }
    odds.clear();
    eves.clear();
    for (I i = 0; i < k; i++) {
      const I a = a_arr[i];
      const I wid = a / n;
      if (wid % 2 == 1)
        odds.push_back(wid);
      else
        eves.push_back(wid);
    }
    I tot = m;
    I odd_ind = 0;
    I eve_ind = 0;
    if (tot % 2 == 1 && !odds.empty()) {
      tot -= fix(odds[odd_ind]);
      odd_ind++;
    }
    if (tot % 2 == 1 && !eves.empty()) {
      tot -= fix(odd(eves[eve_ind]));
      eve_ind++;
    }
    for (; odd_ind + 1 < odds.size(); odd_ind += 2)
      tot -= min(fix(tot), fix(eve(fix(odds[odd_ind]) + fix(odds[odd_ind + 1]))));
    for (; eve_ind < eves.size(); eve_ind++)
      tot -= min(fix(tot), fix(eves[eve_ind]));
    if (odd_ind < odds.size())
      tot -= min(fix(tot), fix(eve(odds[odd_ind])));
    if (tot == 0) {
      printf("Yes\n");
      continue;
    }
    odds.clear();
    eves.clear();
    for (I i = 0; i < k; i++) {
      const I a = a_arr[i];
      const I wid = a / m;
      if (wid % 2 == 1)
        odds.push_back(wid);
      else
        eves.push_back(wid);
    }
    tot = n;
    odd_ind = 0;
    eve_ind = 0;
    if (tot % 2 == 1 && !odds.empty()) {
      tot -= fix(odds[odd_ind]);
      odd_ind++;
    }
    if (tot % 2 == 1 && !eves.empty()) {
      tot -= fix(odd(eves[eve_ind]));
      eve_ind++;
    }
    for (; odd_ind + 1 < odds.size(); odd_ind += 2)
      tot -= min(fix(tot), fix(eve(fix(odds[odd_ind]) + fix(odds[odd_ind + 1]))));
    for (; eve_ind < eves.size(); eve_ind++)
      tot -= min(fix(tot), fix(eves[eve_ind]));
    if (odd_ind < odds.size())
      tot -= min(fix(tot), fix(eve(odds[odd_ind])));
    if (tot == 0) {
      printf("Yes\n");
      continue;
    }
    printf("No\n");
  }
  return 0;
}