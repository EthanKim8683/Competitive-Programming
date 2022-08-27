/*
ID: ethanki1
TASK: namenum
LANG: C++14
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using S = string;
using B = bool;
using C = char;

vector<S> nams;
C nums[9][3] = {
  {'A', 'B', 'C'},
  {'D', 'E', 'F'},
  {'G', 'H', 'I'},
  {'J', 'K', 'L'},
  {'M', 'N', 'O'},
  {'P', 'R', 'S'},
  {'T', 'U', 'V'},
  {'W', 'X', 'Y'}
};

I toi(C chr) {
  return chr - '2';
}

B rng(I num, C chr) {
  for (I i = 0; i < 3; i++)
    if (chr == nums[num][i])
      return true;
  return false;
}

B cmp(S num, S nam) {
  if (num.size() != nam.size())
    return false;
  for (I i = 0; i < num.size(); i++)
    if (!rng(toi(num[i]), nam[i]))
      return false;
  return true;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("namenum.in", "r", stdin);
  freopen("namenum.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  S num;
  cin >> num;
  ifstream fin("dict.txt");
  B non = true;
  while (true) {
    S nam = "";
    fin >> nam;
    if (nam.empty())
      break;
    if (cmp(num, nam)) {
      printf("%s\n", nam.c_str());
      non = false;
    }
  }
  if (non)
    printf("NONE\n");
  return 0;
}