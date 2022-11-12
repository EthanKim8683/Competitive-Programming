#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2000;

I s_arr[N];
Lli dp[N][N];
I maxs[N][N];
I mins[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  sort(s_arr,s_arr+n);
  for(I i=0;i<n;i++)maxs[0][i]=mins[0][i]=s_arr[i];
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++)maxs[i][j]=max(maxs[i-1][j+1],maxs[0][j]);
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++)mins[i][j]=min(mins[i-1][j+1],mins[0][j]);
  for(I i=0;i<n;i++)dp[0][i]=0;
  for(I i=1;i<n;i++)for(I j=0;j+i<n;j++)
    dp[i][j]=min(dp[i-1][j],dp[i-1][j+1])+maxs[i][j]-mins[i][j];
  printf("%lli\n",dp[n-1][0]);
}