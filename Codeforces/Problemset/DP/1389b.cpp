#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e5;
const I K=N-1;
const I Z=5;
const Lli MIN=-1e18;

I a_arr[N];
Lli dp[K+1][Z+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k,z;cin>>n>>k>>z;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<=k;i++)for(I j=0;j<=z;j++)dp[i][j]=MIN;
    dp[0][0]=a_arr[0];
    for(I i=0;i<k;i++){
      for(I j=0;j<=z;j++){
        I x=i-2*j;
        if(x+1<n)dp[i+1][j]=max(dp[i+1][j],dp[i][j]+a_arr[x+1]);
        if(i+2<=k&&x-1>=0&&j+1<=z)dp[i+2][j+1]=max(dp[i+2][j+1],dp[i][j]+a_arr[x-1]+a_arr[x]);
        if(i+1==k&&x-1>=0&&j+1<=z)dp[i+1][j+1]=max(dp[i+1][j+1],dp[i][j]+a_arr[x-1]);
      }
    }
    Lli res=MIN;
    for(I i=0;i<=z;i++)res=max(res,dp[k][i]);
    printf("%lli\n",res);
  }
}