#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using S = string;
using C = char;
using B = bool;

vector<I> cons;
vector<I> invs;
S s, t;

B con(C c) {
  I s_cnt = 0;
  I t_cnt = 0;
  for (const auto chr : s)
    if (chr == c)
      s_cnt++;
  for (const auto chr : t)
    if (chr == c)
      t_cnt++;
  if (s_cnt != t_cnt)
    return false;
  return true;
}

B equ(C a, C b) {
  I s_ind = 0;
  I t_ind = 0;
  I s_cnt = 0;
  I t_cnt = 0;
  while (s_ind < s.size() && t_ind < t.size()) {
    while (s_ind < s.size() && s[s_ind] != a && s[s_ind] != b)
      s_ind++;
    while (t_ind < t.size() && t[t_ind] != a && t[t_ind] != b)
      t_ind++;
    if (s_ind < s.size())
      s_cnt++;
    if (t_ind < t.size())
      t_cnt++;
    if (s_ind < s.size() && t_ind < t.size() && s[s_ind] != t[t_ind])
      return false;
    s_ind++;
    t_ind++;
  }
  if (s_cnt != t_cnt)
    return false;
  return true;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  cin >> t;
  for (C i = 'a'; i <= 'r'; i++)
    if (!con(i))
      invs.push_back(1 << (i - 'a'));
  for (C i = 'a'; i < 'r'; i++)
    for (C j = i + 1; j <= 'r'; j++)
      if (!equ(i, j))
        invs.push_back(1 << (i - 'a') | 1 << (j - 'a'));
  I q;
  cin >> q;
  while (q--) {
    S que;
    cin >> que;
    I msk = 0;
    for (const auto cha : que)
      msk |= 1 << (cha - 'a');
    B res = true;
    for (const auto inv : invs) {
      if ((inv & msk) == inv) {
        res = false;
        break;
      }
    }
    if (res)
      printf("Y");
    else
      printf("N");
  }
  return 0;
}