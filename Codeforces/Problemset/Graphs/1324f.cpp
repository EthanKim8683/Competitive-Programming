#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=2e5;

I a_arr[N];
vector<I>adjs[N];
I dp1[N];
I dp2[N];
I ress[N];

void dfs1(I a,I p=-1){
  dp1[a]=a_arr[a]?1:-1;
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    dp1[a]+=max(dp1[b],0);
  }
}

void dfs2(I a,I p=-1){
  ress[a]=dp2[a]+dp1[a];
  for(auto b:adjs[a])if(b!=p){
    dp2[b]=max(dp2[a]+dp1[a]-max(dp1[b],0),0);
    dfs2(b,a);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs1(0),dfs2(0);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
  return 0;
}