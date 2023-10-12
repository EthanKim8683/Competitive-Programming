#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
vector<I>adjs[N];
B viss[N];
B cols[N];
vector<I>ress;
void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])cols[b]&=!cols[a];
  for(auto b:adjs[a])dfs(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<m;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    fill_n(viss,n,0),fill_n(cols,n,1);
    dfs(0);
    B vld=1;
    for(I i=0;i<n;i++)vld&=viss[i];
    if(!vld){printf("NO\n");continue;}
    ress.clear();
    for(I i=0;i<n;i++)if(cols[i])ress.push_back(i);
    printf("YES\n");
    printf("%i\n",ress.size());
    for(auto i:ress)printf("%i ",i+1);
    printf("\n");
  }
}