#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I N=100000;
const Lli MAX=1e18;

I c_arr[N];
S s_arr[N];
Lli csts[N-1][2][2];
Lli dp[N][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+N*2,MAX);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  for(I i=0;i<n;i++)cin>>s_arr[i];
  for(I i=0;i+1<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++){
    S a=s_arr[i],b=s_arr[i+1];
    if(j)reverse(a.begin(),a.end());
    if(k)reverse(b.begin(),b.end());
    if(a>b){csts[i][j][k]=MAX;continue;}
    csts[i][j][k]=k*c_arr[i+1];
  }
  dp[0][0]=0,dp[0][1]=c_arr[0];
  for(I i=0;i+1<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++)
    dp[i+1][k]=min(dp[i+1][k],dp[i][j]+csts[i][j][k]);
  Lli res=min(dp[n-1][0],dp[n-1][1]);
  printf("%lli\n",res==MAX?-1:res);
}