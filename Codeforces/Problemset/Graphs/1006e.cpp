#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

vector<I>adjs[N];
I ords[N];
I els[N],ers[N];
I t=0;

void dfs(I a,I p=-1){
  ords[t]=a;
  els[a]=t++;
  for(auto b:adjs[a])if(b!=p)dfs(b,a);
  ers[a]=t;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  for(I i=1;i<n;i++){I p;cin>>p,adjs[p-1].push_back(i);}
  for(I i=0;i<n;i++)sort(adjs[i].begin(),adjs[i].end());
  dfs(0);
  while(q--){
    I u,k;cin>>u>>k,u--,k--;
    if(k<ers[u]-els[u])printf("%i\n",ords[els[u]+k]+1);
    else printf("-1\n");
  }
  return 0;
}