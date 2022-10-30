#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I MAX=1e9;

I dp[N+1];
I t_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(dp,n+1,MAX);
  for(I i=0;i<n;i++)cin>>t_arr[i];
  dp[0]=0;
  for(I i=0;i<n;i++){
    I t=t_arr[i];
    I j=i+1;
    I k=lower_bound(t_arr,t_arr+n,t+90)-t_arr;
    I l=lower_bound(t_arr,t_arr+n,t+1440)-t_arr;
    dp[j]=min(dp[j],dp[i]+20);
    dp[k]=min(dp[k],dp[i]+50);
    dp[l]=min(dp[l],dp[i]+120);
  }
  for(I i=n;i>0;i--)dp[i-1]=min(dp[i-1],dp[i]);
  for(I i=0;i<n;i++)printf("%i\n",dp[i+1]-dp[i]);
}