#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=2000;
const Lf MAX=1e300;
const Lf MIN=-1e300;
Lf a_arr[2*N];
Lf dp[2*N+1][N+1][2];
I main(){
  I n;cin>>n;
  for(I i=0;i<2*n;i++)cin>>a_arr[i];
  for(I i=0;i<=2*n;i++)for(I j=0;j<=n;j++)dp[i][j][0]=MAX,dp[i][j][1]=MIN;
  dp[0][0][0]=0;
  for(I i=0;i<2*n;i++)for(I j=0;j<=n;j++)for(I k=0;k<2;k++){
    Lf a=a_arr[i];
    Lf b=dp[i][j][k]+ceil(a)-a,c=dp[i][j][k]+floor(a)-a;
    if(j+1<=n){
      if(b<0)dp[i+1][j+1][1]=max(dp[i+1][j+1][1],b);
      else dp[i+1][j+1][0]=min(dp[i+1][j+1][0],b);
    }
    if(c<0)dp[i+1][j][1]=max(dp[i+1][j][1],c);
    else dp[i+1][j][0]=min(dp[i+1][j][0],c);
  }
  printf("%.3Lf\n",min(dp[2*n][n][0],-dp[2*n][n][1]));
}