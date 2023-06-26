#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const I K=5000;
const Lli MAX=1e18;
I a_arr[N];
I clds[K],hots[K];
Lli dp[N+1][K+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
    for(I i=0;i<k;i++)cin>>clds[i];
    for(I i=0;i<k;i++)cin>>hots[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=k;j++)dp[i][j]=MAX;
    dp[0][k]=0;
    for(I i=0;i<n;i++)for(I j=0;j<=k;j++){
      I a=a_arr[i],b=i-1>=0?a_arr[i-1]:k;
      dp[i+1][b]=min(dp[i+1][b],dp[i][j]+clds[a]);
      dp[i+1][j]=min(dp[i+1][j],dp[i][j]+clds[a]);
      if(a==j)dp[i+1][b]=min(dp[i+1][b],dp[i][j]+hots[a]);
      if(a==b)dp[i+1][j]=min(dp[i+1][j],dp[i][j]+hots[a]);
    }
    printf("%lli\n",*min_element(dp[n],dp[n]+k+1));
  }
}