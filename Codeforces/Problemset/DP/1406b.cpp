#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
using Lli=long long int;
 
const I N=1e5;
const Lli MIN=-1e18;
const Lli MAX=1e18;
 
I a_arr[N];
Lli dp[N+1][5+1][2];
 
void cmb1(Lli&a,Lli b){
  a=max(a,b);
}
 
void cmb2(Lli&a,Lli b){
  a=min(a,b);
}
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli res=MIN;
    for(I i=0;i<=n;i++)for(I j=0;j<=5;j++)for(I k=0;k<2;k++)dp[i][j][k]=MIN;
    dp[0][0][0]=1;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      for(I j=0;j<=5;j++){
        for(I k=0;k<2;k++){
          if(dp[i][j][k]==MIN)continue;
          if(j+1<=5)cmb1(dp[i+1][j+1][k^(a<0)],dp[i][j][k]*abs(a));
          cmb1(dp[i+1][j][k],dp[i][j][k]);
        }
      }
    }
    if(dp[n][5][0]!=MIN)res=max(res,dp[n][5][0]);
    if(dp[n][5][1]!=MIN)res=max(res,-dp[n][5][1]);
    for(I i=0;i<=n;i++)for(I j=0;j<=5;j++)for(I k=0;k<2;k++)dp[i][j][k]=MAX;
    dp[0][0][0]=1;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      for(I j=0;j<=5;j++){
        for(I k=0;k<2;k++){
          if(dp[i][j][k]==MAX)continue;
          if(j+1<=5)cmb2(dp[i+1][j+1][k^(a<0)],dp[i][j][k]*abs(a));
          cmb2(dp[i+1][j][k],dp[i][j][k]);
        }
      }
    }
    if(dp[n][5][0]!=MAX)res=max(res,dp[n][5][0]);
    if(dp[n][5][1]!=MAX)res=max(res,-dp[n][5][1]);
    printf("%lli\n",res);
  }
}