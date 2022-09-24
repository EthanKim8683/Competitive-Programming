#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100;
const I M=100;

I r_arr[N];
I b_arr[M];
I dp[N+1][M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>r_arr[i];
    I m;cin>>m;
    for(I i=0;i<m;i++)cin>>b_arr[i];
    for(I i=0;i<=n;i++)for(I j=0;j<=m;j++)dp[i][j]=0;
    I res=0;
    for(I i=0;i<=n;i++)for(I j=0;j<=m;j++){
      if(i+1<=n)res=max(res,dp[i+1][j]=dp[i][j]+r_arr[i]);
      if(j+1<=m)res=max(res,dp[i][j+1]=dp[i][j]+b_arr[j]);
    }
    printf("%i\n",res);
  }
}