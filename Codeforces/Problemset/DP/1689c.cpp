#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=3e5;

vector<I>adjs[N];
vector<I>savs[N];
vector<I>rems[N];
I dp1[N],dp2[N];

void dfs(I a,I p=-1){
  dp1[a]=0,dp2[a]=1;
  savs[a].clear();
  rems[a].clear();
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    dp2[a]+=dp2[b];
    savs[a].push_back(dp2[b]-1);
    rems[a].push_back(dp1[b]);
  }
  I sum=accumulate(rems[a].begin(),rems[a].end(),0);
  for(I i=0;i<rems[a].size();i++)
    dp1[a]=max(dp1[a],sum-rems[a][i]+savs[a][i]);
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
    dfs(0);
    printf("%i\n",dp1[0]);
  }
}