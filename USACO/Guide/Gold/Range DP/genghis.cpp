#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I K=300;
const Lli MAX=1e18;
I x_arr[K];
Lli dp[K+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0],&dp[0][0]+(K+1)*(K+1),MAX);
  I n;cin>>n;
  I k;cin>>k;
  for(I i=0;i<k;i++)cin>>x_arr[i];
  sort(x_arr,x_arr+k);
  for(I i=0;i<=k;i++)dp[i][i]=0;
  for(I i=0;i+1<=k;i++)dp[i][i+1]=(i+1<k?x_arr[i+1]-1:n)-(i-1>=0?x_arr[i-1]:0);
  for(I i=2;i<=k;i++)for(I j=0;j+i<=k;j++)for(I l=0;l<i;l++)dp[j][j+i]=min(dp[j][j+i],(j+i<k?x_arr[j+i]-1:n)-(j-1>=0?x_arr[j-1]:0)+dp[j][j+l]+dp[j+l+1][j+i]);
  printf("%lli\n",dp[0][k]);
}