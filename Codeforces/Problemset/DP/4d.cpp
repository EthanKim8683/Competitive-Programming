#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=5000;

pair<I,I>envs[N];
I dp[N];
I pars[N];
I inds[N];
I ress[N];

B cmp(I a,I b){
  return envs[a]<envs[b];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,w,h;cin>>n>>w>>h;
  for(I i=0;i<n;i++){
    I w,h;cin>>w>>h;
    envs[i]={w,h};
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++){
    auto[wi,hi]=envs[inds[i]];
    dp[i]=w<wi&&h<hi;
  }
  for(I i=0;i<n;i++)for(I j=0;j<i;j++){
    if(!dp[i])continue;
    if(!dp[j])continue;
    auto[wi,hi]=envs[inds[i]];
    auto[wj,hj]=envs[inds[j]];
    if(wj<wi&&hj<hi&&dp[j]+1>dp[i])
      dp[i]=dp[j]+1,pars[i]=j;
  }
  I j=max_element(dp,dp+n)-dp;
  I res=dp[j];
  for(I i=res-1;i>=0;i--)ress[i]=inds[j],j=pars[j];
  printf("%i\n",res);
  for(I i=0;i<res;i++)printf("%i ",ress[i]+1);
}