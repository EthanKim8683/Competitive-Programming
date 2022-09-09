#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

B viss[N];
vector<I>adjs[N];
vector<I>cols[2];

void dfs(I a,B c){
  if(viss[a])return;
  viss[a]=1;
  cols[c].push_back(a);
  for(auto b:adjs[a])dfs(b,!c);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    fill_n(viss,n,0);
    cols[0].clear(),cols[1].clear();
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<m;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    dfs(0,0);
    I i=cols[0].size()<cols[1].size()?0:1;
    printf("%i\n",cols[i].size());
    for(auto j:cols[i])printf("%i ",j+1);
    printf("\n");
  }
  return 0;
}