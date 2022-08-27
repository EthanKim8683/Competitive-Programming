#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
 
using namespace std;
 
using I = int;
using C = char;
using B = bool;
using Lli = long long int;
 
vector<pair<I, I>> pais;
vector<I> pois;
vector<pair<I, pair<I, I>>> mids; 
multiset<I> low_lows;
multiset<I> low_upps;
multiset<I> upp_lows;
multiset<I> upp_upps;
Lli dis = 0;
 
Lli slv1() {
  if (pais.empty())
    return 0;
  for (const auto [s, t] : pais) {
    pois.push_back(s);
    pois.push_back(t);
  }
  const I mid = pois.size() / 2;
  nth_element(pois.begin(), pois.begin() + mid, pois.end());
  const I med = pois[mid];
  Lli res = 0;
  for (const auto poi : pois)
    res += abs(med - poi);
  return res;
}
 
void upp_bal() {
  if (upp_lows.empty() && !upp_upps.empty()) {
    const I mov = *upp_upps.begin();
    upp_lows.insert(mov);
    upp_upps.erase(upp_upps.find(mov));
    return;
  }
  if (upp_upps.size() > upp_lows.size()) {
    const I las = *upp_lows.rbegin();
    const I mov = *upp_upps.begin();
    upp_lows.insert(mov);
    upp_upps.erase(upp_upps.find(mov));
    const I cur = *upp_lows.rbegin();
    dis += (upp_lows.size() - upp_upps.size() - 2) * (cur - las);
  }
  if (upp_lows.size() > upp_upps.size() + 1) {
    const I las = *upp_lows.rbegin();
    const I mov = *upp_lows.rbegin();
    upp_upps.insert(mov);
    upp_lows.erase(upp_lows.find(mov));
    const I cur = *upp_lows.rbegin();
    dis -= (upp_upps.size() - upp_lows.size()) * (las - cur);
  }
}
 
void low_bal() {
  if (low_upps.size() > low_lows.size()) {
    const I las = *low_lows.rbegin();
    const I mov = *low_upps.begin();
    low_lows.insert(mov);
    low_upps.erase(low_upps.find(mov));
    const I cur = *low_lows.rbegin();
    dis += (low_lows.size() - low_upps.size() - 2) * (cur - las);
  }
  if (low_lows.size() > low_upps.size() + 1) {
    const I las = *low_lows.rbegin();
    const I mov = *low_lows.rbegin();
    low_upps.insert(mov);
    low_lows.erase(low_lows.find(mov));
    const I cur = *low_lows.rbegin();
    dis -= (low_upps.size() - low_lows.size()) * (las - cur);
  }
}
 
void upp_add(I val) {
  if (upp_lows.empty()) {
    upp_lows.insert(val);
    return;
  }
  const I med = *upp_lows.rbegin();
  if (val > med) {
    upp_upps.insert(val);
    dis += val - med;
  } else {
    upp_lows.insert(val);
    dis += med - val;
  }
  upp_bal();
}
 
void low_add(I val) {
  if (low_lows.empty()) {
    low_lows.insert(val);
    return;
  }
  const I med = *low_lows.rbegin();
  if (val > med) {
    low_upps.insert(val);
    dis += val - med;
  } else {
    low_lows.insert(val);
    dis += med - val;
  }
  low_bal();
}
 
void upp_rem(I val) {
  const I med = *upp_lows.rbegin();
  if (val > med) {
    upp_upps.erase(upp_upps.find(val));
    dis -= val - med;
  } else {
    upp_lows.erase(upp_lows.find(val));
    dis -= med - val;
  }
  upp_bal();
}
 
Lli slv2() {
  if (pais.empty())
    return 0;
  for (const auto [s, t] : pais) {
    upp_add(s);
    upp_add(t);
  }
  for (const auto [s, t] : pais)
    mids.push_back({s + (t - s) / 2, {s, t}});
  sort(mids.begin(), mids.end());
  Lli res = dis;
  for (const auto [mid, pai] : mids) {
    const auto [s, t] = pai;
    upp_rem(s);
    upp_rem(t);
    low_add(s);
    low_add(t);
    res = min(res, dis);
  }
  return res;
}
 
I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I k, n;
  cin >> k >> n;
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    C p, q;
    I s, t;
    cin >> p >> s >> q >> t;
    if (s > t)
      swap(s, t);
    if (p != q) {
      pais.push_back({s, t});
      res++;
    } else
      res += t - s;
  }
  if (k == 1)
    res += slv1();
  else
    res += slv2();
  printf("%lli\n", res);
  return 0;
}