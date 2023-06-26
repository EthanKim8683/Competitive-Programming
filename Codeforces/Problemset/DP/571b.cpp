#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I K=5000;
const Lli MAX=1e18;
I a_arr[N];
Lli dp[K+1][K];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(K+1)*K,MAX);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sort(a_arr,a_arr+n);
  dp[0][0]=0;
  I x=n/k,y=n%k;
  for(I i=0;i<k;i++)for(I j=0;j<=y;j++){
    I z=i*x+j;
    dp[i+1][j]=min(dp[i+1][j],dp[i][j]+a_arr[z+x-1]-a_arr[z]);
    if(j+1<=y)dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]+a_arr[z+x]-a_arr[z]);
  }
  printf("%lli\n",dp[k][y]);
}