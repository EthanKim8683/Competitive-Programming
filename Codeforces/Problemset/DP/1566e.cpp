#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
vector<I>adjs[N];
I cols[N];
I dp1[N],dp2[N];
void dfs1(I a,I p=-1){
  cols[a]=0;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    if(cols[b]==0)cols[a]=1;
  }
}
void dfs2(I a,I p=-1){
  dp1[a]=0;
  for(auto b:adjs[a])if(b!=p){
    dfs2(b,a);
    dp1[a]+=dp1[b]+(cols[b]==1);
  }
}
void dfs3(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dp2[b]=dp2[a]+dp1[a]-(dp1[b]+(cols[b]==1));
    dfs3(b,a);
  }
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
    dfs1(0);
    I tot=0;
    for(I i=0;i<n;i++)tot+=cols[i]==0;
    dfs2(0),dfs3(0);
    I res=tot;
    for(I i=0;i<n;i++)res=min(res,tot-(dp1[i]+dp2[i]));
    printf("%i\n",res);
  }
}