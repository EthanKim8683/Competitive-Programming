#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using S = string;
using B = bool;

const I N = 2e5;
const I M = 2e5;

I x_arr[M];
multiset<I> lens;
set<I> edgs;

void ins(I val) {
  if (val != 0)
    lens.insert(val);
}

void era(I val) {
  if (val != 0)
    lens.erase(lens.find(val));
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  S str;
  cin >> str;
  I m;
  cin >> m;
  for (I i = 0; i < m; i++)
    cin >> x_arr[i];
  const I n = str.size();
  I i = 0;
  edgs.insert(i);
  while (i < n) {
    I len = 1;
    while (i + len < n && str[i] == str[i + len])
      len++;
    i += len;
    lens.insert(len);
    edgs.insert(i);
  }
  for (I i = 0; i < m; i++) {
    const I x = x_arr[i];
    const I rgt = x;
    const I lft = x - 1;
    const B lop = lft != 0 && edgs.find(lft) != edgs.end();
    const B rop = rgt != n && edgs.find(rgt) != edgs.end();
    auto bit = --edgs.upper_bound(lft);
    auto eit = edgs.lower_bound(rgt);
    if (lop && rop) {
      bit--;
      eit++;
      era(1);
      era(*eit - rgt);
      era(lft - *bit);
      ins(*eit - *bit);
      edgs.erase(lft);
      edgs.erase(rgt);
    } else if (!lop && rop) {
      eit++;
      era(*eit - rgt);
      era(rgt - *bit);
      ins(*eit - lft);
      ins(lft - *bit);
      edgs.erase(rgt);
      edgs.insert(lft);
    } else if (lop && !rop) {
      bit--;
      era(lft - *bit);
      era(*eit - lft);
      ins(*eit - rgt);
      ins(rgt - *bit);
      edgs.erase(lft);
      edgs.insert(rgt);
    } else if (!lop && !rop) {
      era(*eit - *bit);
      ins(lft - *bit);
      ins(*eit - rgt);
      ins(1);
      edgs.insert(lft);
      edgs.insert(rgt);
    }
    printf("%i ", *--lens.end());
  }
  return 0;
}