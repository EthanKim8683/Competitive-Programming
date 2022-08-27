#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using S = string;
using Lli = long long int;

const Lli MOD = 1000000007;

vector<pair<S, vector<vector<Lli>>>> frw_stk;
vector<pair<S, vector<vector<Lli>>>> bkw_stk;
I n;

vector<vector<Lli>> mat() {
  return vector<vector<Lli>>(n, vector<Lli>(n, 0));
}

vector<vector<Lli>> idn() {
  auto res = mat();
  for (I i = 0; i < n; i++)
    res[i][i] = 1;
  return res;
}

vector<vector<Lli>> flp(vector<vector<Lli>> x) {
  auto res = mat();
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      res[j][i] = x[i][j];
  return res;
}

vector<vector<Lli>> mul(vector<vector<Lli>> a, vector<vector<Lli>> b) {
  auto res = mat();
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      for (I k = 0; k < n; k++)
        res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
  return res;
}

vector<vector<Lli>> rel(S a, S b) {
  auto res = mat();
  for (I i = 0; i < n; i++) {
    if (i - 1 >= 0 && b[i - 1] == a[i])
      res[i][i - 1]++;
    if (b[i] == a[i])
      res[i][i]++;
    if (i + 1 < n && b[i + 1] == a[i])
      res[i][i + 1]++;
  }
  return res;
}

vector<vector<Lli>> cmb(pair<S, vector<vector<Lli>>> src, S val) {
  return mul(src.second, rel(src.first, val));
}

vector<vector<Lli>> frw_rel() {
  return flp(frw_stk.back().second);
}

vector<vector<Lli>> bkw_rel() {
  return bkw_stk.back().second;
}

vector<vector<Lli>> mid_rel() {
  return rel(frw_stk.front().first, bkw_stk.front().first);
}

void psh(S val) {
  if (frw_stk.empty())
    frw_stk.push_back({val, idn()});
  else
    frw_stk.push_back({val, cmb(frw_stk.back(), val)});
}

void pop() {
  if (bkw_stk.empty()) {
    while (!frw_stk.empty()) {
      auto val = frw_stk.back().first;
      frw_stk.pop_back();
      if (bkw_stk.empty())
        bkw_stk.push_back({val, idn()});
      else
        bkw_stk.push_back({val, cmb(bkw_stk.back(), val)});
    }
  }
  bkw_stk.pop_back();
}

Lli qry(I a, I b) {
  if (bkw_stk.empty())
    return frw_rel()[b][a];
  if (frw_stk.empty())
    return bkw_rel()[b][a];
  return mul(frw_rel(), mul(mid_rel(), bkw_rel()))[b][a];
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  while (q--) {
    S i;
    cin >> i;
    if (i == "add") {
      S l;
      cin >> l;
      psh(l);
    } else if (i == "remove") {
      pop();
    } else if (i == "path") {
      I a, b;
      cin >> a >> b;
      printf("%lli\n", qry(a - 1, b - 1));
    }
  }
  return 0;
}