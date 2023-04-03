#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <tuple>
 
using namespace std;
 
using I = int;
using C = char;
 
const I N = 1000;
const I M = 1000;
const I MAX = 1e9;
 
C cels[N][M + 1];
set<I> hor_bnds[N];
set<I> ver_bnds[M];
vector<tuple<I, I, I>> ress;
I hor_ps[N][M + 1];
I ver_ps[M][N + 1];
I n, m;
 
void hor_fil(I i, I& j) {
  if (cels[i][j] == '*') {
    hor_bnds[i].insert(j);
    while (++j < m && cels[i][j] == '*');
    hor_bnds[i].insert(j);
  }
}
 
void ver_fil(I& i, I j) {
  if (cels[i][j] == '*') {
    ver_bnds[j].insert(i);
    while (++i < n && cels[i][j] == '*');
    ver_bnds[j].insert(i);
  }
}
 
I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> cels[i];
  for (I i = 0; i < n; i++)
    for (I j = 0; j < m; j++)
      hor_fil(i, j);
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      ver_fil(j, i);
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      if (cels[i][j] == '*') {
        auto hor_it = hor_bnds[i].upper_bound(j);
        auto ver_it = ver_bnds[j].upper_bound(i);
        I siz = MAX;
        siz = min(siz, *hor_it - 1 - j);
        siz = min(siz, *ver_it - 1 - i);
        siz = min(siz, j - *--hor_it);
        siz = min(siz, i - *--ver_it);
        if (siz > 0) {
          ress.push_back({i, j, siz});
          hor_ps[i][j - siz]++;
          ver_ps[j][i - siz]++;
          hor_ps[i][j + siz + 1]--;
          ver_ps[j][i + siz + 1]--;
        }
      }
    }
  }
  for (I i = 0; i < n; i++)
    for (I j = 0; j < m; j++)
      hor_ps[i][j + 1] += hor_ps[i][j];
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      ver_ps[i][j + 1] += ver_ps[i][j];
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      if (cels[i][j] == '*' && hor_ps[i][j] == 0 && ver_ps[j][i] == 0) {
        printf("-1\n");
        return 0;
      }
    }
  }
  printf("%i\n", ress.size());
  for (const auto [i, j, siz] : ress)
    printf("%i %i %i\n", i + 1, j + 1, siz);
  return 0;
}