#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;

vector<I>adjs[N];
I dp1[N],dp2[N];

void dfs(I a,I p=-1){
  dp1[a]=0,dp2[a]=0;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    dp2[a]=max(dp2[a],dp2[b]);
    dp2[a]=max(dp2[a],dp1[a]+dp1[b]+1);
    dp1[a]=max(dp1[a],dp1[b]+1);
  }
}

I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  I res=0;
  for(I i=0;i<n;i++){
    I m;cin>>m;
    for(I j=0;j<m;j++)adjs[j].clear();
    for(I j=0;j<m-1;j++){
      I a,b;cin>>a>>b,a--,b--;
      adjs[a].push_back(b);
      adjs[b].push_back(a);
    }
    dfs(0);
    res+=dp2[0];
  }
  printf("%i\n",res);
}