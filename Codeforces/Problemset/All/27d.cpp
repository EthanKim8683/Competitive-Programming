#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I M=100;
pair<I,I>rngs[M];
vector<I>adjs[2*M];
I cols[M];
void dfs(I a,I col){
  if(cols[a>>1]!=-1){
    if(cols[a>>1]!=col)printf("Impossible"),exit(0);
    return;
  }
  cols[a>>1]=col;
  for(auto b:adjs[a])dfs(b,!col);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    if(a>b)swap(a,b);
    rngs[i]={a,b};
  }
  for(I i=0;i<m;i++)for(I j=i+1;j<m;j++){
    auto[a1,b1]=rngs[i];auto[a2,b2]=rngs[j];
    I a3=max(a1,a2),b3=min(b1,b2);
    if(a3>=b3)continue;
    if(a3==a1&&b3==b1)continue;
    if(a3==a2&&b3==b2)continue;
    adjs[i<<1].push_back(j<<1|1);
    adjs[j<<1].push_back(i<<1|1);
    adjs[j<<1|1].push_back(i<<1);
    adjs[i<<1|1].push_back(j<<1);
  }
  fill_n(cols,m,-1);
  for(I i=0;i<2*m;i++)if(cols[i>>1]==-1)dfs(i,0);
  for(I i=0;i<m;i++)printf("%c","io"[cols[i]]);
}
/*
this is my first ever official 2-sat problem

from the blog i read, it looks like 2-sat is constructing a dependency graph
between variables in two possible states

so that's what i'm doing here: if one range cannot be on the same side as
another, it is dependent on the fact that the other range is on a different
side

i think this is a little different from a classical 2-sat problem because
~x => y, but also y => ~x (and ~y => x and x => ~y), but i think the general
gist still applies
*/