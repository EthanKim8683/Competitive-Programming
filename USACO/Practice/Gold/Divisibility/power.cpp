#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;
using S = string;
using C = char;

const I N = 1e5;
const I A = 1e5;

I a_arr[N];
B coms[A + 1];
vector<I> prms;
unordered_map<S, Lli> cnts;

I main(void) {
#ifdef ETHANKIM8683
  freopen("power.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 2; i * i <= A; i++)
    if (!coms[i])
      for (I j = i * i; j <= A; j += i)
        coms[j] = true;
  for (I i = 2; i <= A; i++)
    if (!coms[i])
      prms.push_back(i);
  for (I i = 0; i < n; i++) {
    auto a = a_arr[i];
    S str = "";
    for (const auto prm : prms) {
      I cnt = 0;
      while (a % prm == 0) {
        a /= prm;
        cnt++;
      }
      cnt %= k;
      if (cnt) {
        str += (C) (prm >> 16 & 0xff);
        str += (C) (prm >> 8 & 0xff);
        str += (C) (prm & 0xff);
        str += (C) (cnt);
      }
      if (a == 1)
        break;
    }
    cnts[str]++;
  }
  Lli res = 0;
  auto it = cnts.begin();
  while (it != cnts.end()) {
    const auto [str, cnt] = *it;
    S req = "";
    for (I i = 0; i < str.length(); i++) {
      if (i % 4 == 3)
        req += (C) (k - (I) str[i]);
      else
        req += str[i];
    }
    if (str != req) {
      auto it = cnts.find(req);
      if (it != cnts.end()) {
        res += cnt * it->second;
        cnts.erase(it);
      }
    } else
      res += cnt * (cnt - 1) / 2;
    it = cnts.erase(it);
  }
  printf("%lli\n", res);
  return 0;
}