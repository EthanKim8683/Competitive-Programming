#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I h_arr[N];
I dp[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>h_arr[i];
  copy_n(h_arr,n,dp);
  dp[0]=min(dp[0],1),dp[n-1]=min(dp[n-1],1);
  for(I i=0;i+1<n;i++)dp[i+1]=min(dp[i+1],dp[i]+1);
  for(I i=n-1;i>0;i--)dp[i-1]=min(dp[i-1],dp[i]+1);
  printf("%i\n",*max_element(dp,dp+n));
}