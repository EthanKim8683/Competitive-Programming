/*
ID: ethanki1
TASK: gift1
LANG: C++14
*/

#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

using I = int;
using S = string;

const I N = 10;

map<S, I> nets;
S mems[N];

I main(void) {
#ifndef ETHANKIM8683
  freopen("gift1.in", "r", stdin);
  freopen("gift1.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> mems[i];
  while (true) {
    S giv = "EOF";
    cin >> giv;
    if (giv == "EOF")
      break;
    I mon, cnt;
    cin >> mon >> cnt;
    if (cnt != 0) {
    const I div = mon / cnt;
      for (I i = 0; i < cnt; i++) {
        S rec;
        cin >> rec;
        nets[giv] -= div;
        nets[rec] += div;
      }
    }
  }
  for (I i = 0; i < n; i++) {
    const S mem = mems[i];
    printf("%s %i\n", mem.c_str(), nets[mem]);
  }
  return 0;
}