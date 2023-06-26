#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I K=447;
const Lli MIN=-1e18;
I a_arr[N];
Lli ps[N+1];
Lli dp[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++)ps[i+1]=ps[i]+a_arr[i];
    I siz=(sqrt(1+8*n)-1)/2;
    for(I i=0;i<=n;i++)for(I j=1;j<=siz;j++)dp[i][j]=MIN;
    for(I i=n;i>0;i--){
      dp[i-1][1]=max(dp[i][1],ps[i]-ps[i-1]);
      for(I j=2;j<=siz;j++){
        if(i-j>=0&&ps[i]-ps[i-j]<dp[i][j-1])dp[i-j][j]=max(dp[i-j][j],ps[i]-ps[i-j]);
        dp[i-1][j]=max(dp[i-1][j],dp[i][j]);
      }
    }
    I res=0;
    for(I i=0;i<=siz;i++)if(dp[0][i]!=MIN)res=max(res,i);
    printf("%i\n",res);
  }
}