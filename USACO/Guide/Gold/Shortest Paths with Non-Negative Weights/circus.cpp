#ifndef ETHANKIM8683
#include "circus.h"
#endif
#include <algorithm>
#include <queue>
#include <vector>
#include <map>

using namespace std;

using I = int;
using B = bool;

const I N = 100000;
const I LOGN = 17;
const I MIN = -1e9;
const I MAX = 1e9;

map<I, I> unvs;
vector<I> cpss1;
vector<I> cpss2;
vector<I> cpss3;
priority_queue<pair<I, I>, vector<pair<I, I>>, greater<pair<I, I>>> que;
I diss[N + 1];
I segs1[2 * (N + 1)];
I segs2[2 * (N + 1)];
I ps1[N + 1];
I ps2[N + 1];

void add(I dis, I a) {
  if (dis < diss[a]) {
    diss[a] = dis;
    que.push({dis, a});
  }
}

void unq1() {
  sort(cpss1.begin(), cpss1.end());
  cpss1.erase(unique(cpss1.begin(), cpss1.end()), cpss1.end());
}

void unq2() {
  sort(cpss2.begin(), cpss2.end());
  cpss2.erase(unique(cpss2.begin(), cpss2.end()), cpss2.end());
}

void unq3() {
  sort(cpss3.begin(), cpss3.end());
  cpss3.erase(unique(cpss3.begin(), cpss3.end()), cpss3.end());
}
 
I cps1(I x) {
  return lower_bound(cpss1.begin(), cpss1.end(), x) - cpss1.begin();
}
 
I cps2(I x) {
  return upper_bound(cpss1.begin(), cpss1.end(), x) - cpss1.begin() - 1;
}
 
I cps3(I x) {
  return lower_bound(cpss2.begin(), cpss2.end(), x) - cpss2.begin();
}
 
I cps4(I x) {
  return upper_bound(cpss3.begin(), cpss3.end(), x) - cpss3.begin() - 1;
}

void cmb1(I& a, I b) {
  a = max(a, b);
}

void cmb2(I& a, I b) {
  a = min(a, b);
}

void upd1(I l, I r, I val) {
  for (l += cpss1.size(), r += cpss1.size(); l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      cmb1(segs1[l++], val);
    if (r & 1)
      cmb1(segs1[--r], val);
  }
}

void upd2(I l, I r, I val) {
  for (l += cpss1.size(), r += cpss1.size(); l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      cmb2(segs2[l++], val);
    if (r & 1)
      cmb2(segs2[--r], val);
  }
}

I qry1(I i) {
  I res = MIN;
  for (i += cpss1.size(); i > 0; i >>= 1)
    cmb1(res, segs1[i]);
  return res;
}

I qry2(I i) {
  I res = MAX;
  for (i += cpss1.size(); i > 0; i >>= 1)
    cmb2(res, segs2[i]);
  return res;
}

void init(I n, I m, I p_arr[]) {
  for (I i = 0; i < n; i++)
    cpss1.push_back(p_arr[i]);
  unq1();
  fill_n(diss, cpss1.size(), MAX);
  fill_n(segs1, 2 * cpss1.size(), MIN);
  fill_n(segs2, 2 * cpss1.size(), MAX);
  for (I i = 0; i < cpss1.size(); i++)
    unvs.insert({cpss1[i], i});
  add(m - cpss1.back(), cpss1.size() - 1);
  while (!que.empty() && !unvs.empty()) {
    const auto [dis, a] = que.top();
    que.pop();
    if (dis != diss[a])
      continue;
    const I p = cpss1[a];
    upd1(cps1(p + dis), cpss1.size(), p);
    upd2(0, cps2(p - dis) + 1, p);
    unvs.erase(p);
    if (!unvs.empty()) {
      auto upp_it = unvs.lower_bound(p + dis);
      auto low_it = unvs.upper_bound(p - dis);
      if (upp_it != unvs.end()) {
        const auto [p, a] = *upp_it;
        add(min(p - qry1(a), qry2(a) - p), a);
      }
      if (low_it-- != unvs.begin()) {
        const auto [p, a] = *low_it;
        add(min(p - qry1(a), qry2(a) - p), a);
      }
    }
  }
  for (I i = 0; i < cpss1.size(); i++) {
    cpss2.push_back(cpss1[i] - diss[i]);
    cpss3.push_back(cpss1[i] + diss[i]);
  }
  unq2();
  unq3();
  fill_n(ps1, cpss2.size(), MAX);
  fill_n(ps2, cpss3.size(), MIN);
  for (I i = 0; i < cpss1.size(); i++) {
    const I low = cps3(cpss1[i] - diss[i]);
    const I upp = cps4(cpss1[i] + diss[i]);
    ps1[low] = min(ps1[low], cpss1[i]);
    ps2[upp] = max(ps2[upp], cpss1[i]);
  }
  for (I i = cpss2.size() - 1; i - 1 >= 0; i--)
    ps1[i - 1] = min(ps1[i - 1], ps1[i]);
  for (I i = 0; i + 1 < cpss3.size(); i++)
    ps2[i + 1] = max(ps2[i + 1], ps2[i]);
}

I minLength(I d) {
  I res = MAX;
  const I upp = cps3(d);
  const I low = cps4(d);
  if (upp < cpss2.size())
    res = min(res, ps1[upp] - d);
  if (low >= 0)
    res = min(res, d - ps2[low]);
  return res;
}

#ifdef ETHANKIM8683
#include <iostream>
#include <cstdio>

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  static I p[N];
  for (I i = 0; i < n; i++)
    cin >> p[i];
  init(n, m, p);
  while (true) {
    I d = -1;
    cin >> d;
    if (d == -1)
      break;
    printf("%i\n", minLength(d));
  }
  return 0;
}
#endif