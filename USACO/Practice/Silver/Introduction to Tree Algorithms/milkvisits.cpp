#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I=int;
using S=string;
using C=char;
using B=bool;

const I N=1e5;
const I LOGN=17;

vector<I> adjs[N];
I cnts[2][N];
I ps[2][N];
I ancs[N][LOGN];
I tim_begs[N];
I tim_ends[N];
I tim=0;

void dfs(I a, I p) {
  tim_begs[a]=tim++;
  ps[0][a]+=cnts[0][a];
  ps[1][a]+=cnts[1][a];
  ancs[a][0]=p;
  for (I i=1; i<LOGN; i++)
    ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for (const auto b : adjs[a]) {
    if (b!=p) {
      ps[0][b]+=ps[0][a];
      ps[1][b]+=ps[1][a];
      dfs(b, a);
    }
  }
  tim_ends[a]=tim++;
}

B anc(I a, I b) {
  return tim_begs[a]<=tim_begs[b]&&tim_ends[a]>=tim_ends[b];
}

I lca(I a, I b) {
  if (anc(a, b))
    return a;
  if (anc(b, a))
    return b;
  for (I i=LOGN-1; i>=0; i--)
    if (!anc(ancs[a][i], b))
      a=ancs[a][i];
  return ancs[a][0];
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("milkvisits.in", "r", stdin);
  freopen("milkvisits.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  S str;
  cin >> str;
  for (I i=0; i<n-1; i++) {
    I x, y;
    cin >> x >> y;
    x--, y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for (I i=0; i<n; i++) {
    cnts[0][i]=str[i]=='G';
    cnts[1][i]=str[i]=='H';
  }
  dfs(0, 0);
  for (I i=0; i<m; i++) {
    I a, b;
    C c;
    cin >> a >> b >> c;
    a--, b--;
    const I d=lca(a, b);
    const I t=c=='H';
    printf("%i", ps[t][a]+ps[t][b]-2*ps[t][d]+2*cnts[t][d]>0);
  }
  return 0;
}