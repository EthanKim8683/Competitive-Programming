#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=4000;
const I K=N;
const I T=86400;
const I MAX=1e9;
pair<I,I>cals[N];
I dp[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(K+1),MAX);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++){
    I t,d;cin>>t>>d;
    cals[i]={t-1,d};
  }
  sort(cals,cals+n);
  I res=0;
  dp[0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<=k;j++){
    auto[t,d]=cals[i];
    res=max(res,t-dp[i][j]);
    if(j+1<=k)dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
    dp[i+1][j]=min(dp[i+1][j],max(dp[i][j],t)+d);
  }
  for(I i=0;i<=k;i++)res=max(res,T-dp[n][i]);
  printf("%i\n",res);
}