#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=1e5;
const I MAX=1e9;

I t_arr[N];
I dp[2];

I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  dp[0]=dp[1]=MAX;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  dp[0]=0;
  for(I i=0;i<n;i++){
    I t=t_arr[i];
    if(i>0)dp[1]=min(dp[1],dp[0]);
    dp[0]+=t>=0;
    dp[1]+=t<=0;
  }
  printf("%i\n",dp[1]);
  return 0;
}