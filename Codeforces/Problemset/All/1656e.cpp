#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I A=1e5;
vector<I>adjs[N];
I ress[N];
I dfs(I a,I res,I p=-1){
  ress[a]=res;
  for(auto b:adjs[a])if(b!=p)ress[a]-=dfs(b,-res,a);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    ress[0]=0;
    for(auto i:adjs[0])ress[0]-=dfs(i,1,0);
    for(I i=0;i<n;i++)printf("%i ",ress[i]);
    printf("\n");
  }
}