#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 200000;
const I BITS = 30;
const I MAX = 1 << BITS;

pair<I, I> nods[N * BITS][2];
I pars[N];
I a_arr[N];
pair<I, I> mins[N];
unordered_set<I> coms;
unordered_map<I, unordered_set<I>> vals;
vector<I> adjs[N];
I nod = 0;

I fnd(I i) {
  if (pars[i] < 0)
    return i;
  return pars[i] = fnd(pars[i]);
}

B uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return false;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  return true;
}

void add(I val) {
  I msk = 1 << (BITS - 1);
  I cur = 0;
  for (I i = 0; i < BITS; i++) {
    const B bit = val & msk;
    nods[cur][bit].second++;
    if (nods[cur][bit].first == 0)
      cur = nods[cur][bit].first = ++nod;
    else
      cur = nods[cur][bit].first;
    msk >>= 1;
  }
}

void rem(I val) {
  I msk = 1 << (BITS - 1);
  I cur = 0;
  for (I i = 0; i < BITS; i++) {
    const B bit = val & msk;
    nods[cur][bit].second--;
    cur = nods[cur][bit].first;
    msk >>= 1;
  }
}

I qry(I val) {
  I msk = 1 << (BITS - 1);
  I cur = 0;
  I res = 0;
  for (I i = 0; i < BITS; i++) {
    const B bit = val & msk;
    if (nods[cur][bit].second == 0) {
      cur = nods[cur][!bit].first;
      res |= msk * !bit;
    } else {
      cur = nods[cur][bit].first;
      res |= msk * bit;
    }
    msk >>= 1;
  }
  return res;
}

void exc(I a) {
  rem(a_arr[a]);
  vals[a_arr[a]].erase(a);
  for (const auto b : adjs[a])
    exc(b);
}

void inc(I a) {
  add(a_arr[a]);
  vals[a_arr[a]].insert(a);
  for (const auto b : adjs[a])
    inc(b);
}

void prc(I a) {
  const auto a_val = a_arr[a];
  const auto b_val = qry(a_val);
  const I dst = a_val ^ b_val;
  const auto b = *vals[b_val].begin();
  const auto a_par = fnd(a);
  const auto b_par = fnd(b);
  if (dst < mins[a_par].first)
    mins[a_par] = {dst, b_par};
  if (dst < mins[b_par].first)
    mins[b_par] = {dst, a_par};
  for (const auto b : adjs[a])
    prc(b);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("xor2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  fill_n(pars, n, -1);
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    a_arr[i] = a;
    coms.insert(i);
    inc(i);
  }
  fill_n(mins, n, pair<I, I>{MAX, -1});
  Lli res = 0;
  while (coms.size() > 1) {
    for (const auto a : coms) {
      exc(a);
      prc(a);
      inc(a);
    }
    for (const auto a : coms) {
      const auto [dst, b] = mins[a];
      if (dst != MAX && uni(a, b))
        res += dst;
    }
    for (auto it = coms.begin(); it != coms.end();) {
      if (pars[*it] < 0)
        mins[*it++].first = MAX;
      else {
        adjs[pars[*it]].push_back(*it);
        it = coms.erase(it);
      }
    }
  }
  printf("%lli\n", res);
  return 0;
}