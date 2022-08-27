#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=100000;

vector<I>adjs[N];
I cols[N];
B viss[N];
vector<I>covs[2];

B dfs(I a,I c){
  if(viss[a])return cols[a]==c;
  viss[a]=true;
  cols[a]=c;
  covs[c].push_back(a);
  B res=true;
  for(auto b:adjs[a])res&=dfs(b,!c);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  for(I i=0;i<n;i++)if(!dfs(i,cols[i])){
    printf("-1\n");return 0;
  }
  printf("%i\n",covs[0].size());
  for(auto i:covs[0])printf("%i ",i+1);
  printf("\n%i\n",covs[1].size());
  for(auto i:covs[1])printf("%i ",i+1);
  return 0;
}