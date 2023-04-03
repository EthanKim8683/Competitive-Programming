#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const Lli MAX=1e18;
pair<I,I>itms[N];
Lli dp[N+1][2*N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(N+1)*(2*N+1),MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I t,c;cin>>t>>c;
    itms[i]={c,-t};
  }
  sort(itms,itms+n);
  dp[0][N]=0;
  for(I i=0;i<n;i++){
    auto[c,t]=itms[i];t=-t;
    for(I j=-i;j<=n;j++){
      dp[i+1][N+min(j+t,n)]=min(dp[i+1][N+min(j+t,n)],dp[i][N+j]+c);
      dp[i+1][N+j-1]=min(dp[i+1][N+j-1],dp[i][N+j]);
    }
  }
  Lli res=MAX;
  for(I i=0;i<=n;i++)res=min(res,dp[n][N+i]);
  printf("%lli\n",res);
}