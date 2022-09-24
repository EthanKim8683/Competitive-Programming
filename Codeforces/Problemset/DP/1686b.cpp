#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I MIN=-1e9;

I p_arr[N];
I dp[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<=n;i++)dp[i]=MIN;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    dp[0]=0;
    for(I i=0;i<n;i++){
      if(i+2<=n)dp[i+2]=max(dp[i+2],dp[i]+(p_arr[i]>p_arr[i+1]));
      dp[i+1]=max(dp[i+1],dp[i]);
    }
    printf("%i\n",dp[n]);
  }
}