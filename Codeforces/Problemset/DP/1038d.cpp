#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=500000;
const Lli MIN=-1e18;

I a_arr[N];
Lli dp[N+1][2][2];

void cmb(Lli&a,Lli b){
  a=max(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+N*2*2,MIN);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  if(n==1)printf("%i\n",a_arr[0]),exit(0);
  dp[0][0][0]=0;
  for(I i=0;i<n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++){
    I a=a_arr[i];
    cmb(dp[i+1][j|1][k|0],dp[i][j][k]+a);
    cmb(dp[i+1][j|0][k|1],dp[i][j][k]-a);
  }
  printf("%lli\n",dp[n][1][1]);
}