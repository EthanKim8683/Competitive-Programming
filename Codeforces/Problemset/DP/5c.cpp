#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;
using B = bool;

const I N = 1e6;
const I MAX = 1e9;

B ivds[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  S str;
  cin >> str;
  I dep = 0;
  for (I i = 0; i < str.size(); i++) {
    dep += str[i] == '(' ? 1 : -1;
    if (dep < 0) {
      ivds[i] = true;
      dep = 0;
    }
  }
  dep = 0;
  for (I i = str.size() - 1; i >= 0; i--) {
    dep += str[i] == ')' ? 1 : -1;
    if (dep < 0) {
      ivds[i] = true;
      dep = 0;
    }
  }
  I max_siz = 0;
  I max_cnt = 1;
  I siz = 0;
  for (I i = 0; i < str.size(); i++) {
    if (!ivds[i]) {
      siz++;
      if (siz > max_siz) {
        max_siz = siz;
        max_cnt = 1;
      } else if (siz == max_siz)
        max_cnt++;
    } else
      siz = 0;
  }
  printf("%i %i\n", max_siz, max_cnt);
  return 0;
}