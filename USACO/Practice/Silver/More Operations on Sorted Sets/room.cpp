#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <numeric>

using namespace std;

using I = int;
using B = bool;

const I N = 2e5;

pair<I, I> cuss[N];
multimap<I, I> roos;
unordered_set<I> emps;
I ress[N];
I inds[N];

B cmp(I a, I b) {
  return cuss[a].first < cuss[b].first;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a, b;
    cin >> a >> b;
    cuss[i] = {a, b};
  }
  iota(inds, inds + n, 0);
  sort(inds, inds + n, cmp);
  I res = 0;
  for (I i = 0; i < n; i++) {
    const I ind = inds[i];
    const auto [a, b] = cuss[ind];
    for (auto it = roos.begin(); it != roos.lower_bound(a); it = roos.erase(it))
      emps.insert(it->second);
    I roo;
    if (emps.empty())
      roo = roos.size() + 1;
    else {
      const auto it = emps.begin();
      roo = *it;
      emps.erase(it);
    }
    roos.insert({b, roo});
    ress[ind] = roo;
    res = max(res, roo);
  }
  printf("%i\n", res);
  for (I i = 0; i < n; i++)
    printf("%i ", ress[i]);
  return 0;
}