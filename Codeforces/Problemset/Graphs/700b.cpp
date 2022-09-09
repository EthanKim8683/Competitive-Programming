#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using Lli=long long int;

const I N=200000;

vector<I>adjs[N];
I dp1[N],dp2[N];
Lli res=0;

void dfs1(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dfs1(b,a);
    dp1[a]+=dp1[b];
  }
}

void dfs2(I a,I p=-1){
  for(auto b:adjs[a])if(b!=p){
    dp2[b]=dp2[a]+(dp1[a]-dp1[b]);
    res+=min(dp2[a]+(dp1[a]-dp1[b]),dp1[b]);
    dfs2(b,a);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<2*k;i++){I u;cin>>u,dp1[u-1]++;}
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs1(0),dfs2(0);
  printf("%lli\n",res);
  return 0;
}