#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I M=N-1;

I poss[N];
pair<I,I>roks[M];
I adjs[M];
I viss[N];
I cnt=0;

void dfs(I a){
  if(viss[a]==1)cnt++;
  if(viss[a])return;
  viss[a]=1;
  I b=adjs[a];
  if(b!=-1)dfs(b);
  viss[a]=2;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(viss,n,0);
    fill_n(poss,n,-1);
    fill_n(adjs,n,-1);
    for(I i=0;i<m;i++){
      I x,y;cin>>x>>y,x--,y--;
      roks[i]={x,y};
      poss[x]=i;
    }
    I res=0;
    for(I i=0;i<m;i++){
      auto[x,y]=roks[i];
      if(x==y)continue;
      res++;
      I j=poss[y];
      if(j!=-1)adjs[i]=j;
    }
    cnt=0;
    for(I i=0;i<n;i++)
      if(!viss[i])dfs(i);
    printf("%i\n",res+cnt);
  }
  return 0;
}