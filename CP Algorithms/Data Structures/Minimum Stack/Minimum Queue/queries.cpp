#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;

const I N = 1e5;

I a_arr[N];
vector<pair<I, I>> frw_stk;
vector<pair<I, I>> bkw_stk;

void psh(I val) {
  auto max_val = val;
  if (!frw_stk.empty())
    max_val = max(max_val, frw_stk.back().second);
  frw_stk.push_back({val, max_val});
}

void pop() {
  if (bkw_stk.empty()) {
    while (!frw_stk.empty()) {
      const auto val = frw_stk.back().first;
      auto max_val = val;
      frw_stk.pop_back();
      if (!bkw_stk.empty())
        max_val = max(max_val, bkw_stk.back().second);
      bkw_stk.push_back({val, max_val});
    }
  }
  bkw_stk.pop_back();
}

void clr() {
  frw_stk.clear();
  bkw_stk.clear();
}

I qry() {
  I res = 0;
  if (!frw_stk.empty())
    res = max(res, frw_stk.back().second);
  if (!bkw_stk.empty())
    res = max(res, bkw_stk.back().second);
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  while (q--) {
    I d;
    cin >> d;
    clr();
    for (I i = 0; i < d; i++)
      psh(a_arr[i]);
    I res = qry();
    for (I i = d; i < n; i++) {
      psh(a_arr[i]);
      pop();
      res = min(res, qry());
    }
    printf("%i\n", res);
  }
  return 0;
}