#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100;
const I V=100;
const Lli MAX=1e18;

Lli dp[N][V+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,v;cin>>n>>v;
  fill(&dp[0][0],&dp[0][0]+N*(V+1),MAX);
  dp[0][0]=0;
  for(I i=0;i+1<n;i++)
    for(I j=0;j<=v;j++)
      for(I k=j;k<=v;k++)
        if(k-1>=0)
          dp[i+1][k-1]=min(dp[i+1][k-1],dp[i][j]+(k-j)*(i+1));
  Lli res=MAX;
  for(I i=0;i<=v;i++)res=min(res,dp[n-1][i]);
  printf("%lli\n",res);
}