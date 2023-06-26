#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using S=string;
using C=char;
const I N=5000;
const Lli MAX=1e18;
Lli dp[2][N+1][2][3];
void cmb(Lli&a,Lli b){
  a=min(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,x,y;cin>>n>>x>>y;
    S a;cin>>a;
    S b;cin>>b;
    for(I i=0;i<2;i++)for(I j=0;j<=n;j++)for(I k=0;k<2;k++)for(I l=0;l<3;l++)dp[i][j][k][l]=MAX;
    dp[0][0][0][0]=0;
    for(I i=0;i<n;i++){
      for(I j=n;j>=0;j--)for(I k=0;k<2;k++)for(I l=0;l<3;l++)if(dp[i%2][j][k][l]!=MAX){
        C u=a[i],v=b[i];
        if(j-1>=0)cmb(dp[i%2][j-1][k^1][l],dp[i%2][j][k][l]);
        if(j+l<=n){
          if((u==v)^k)cmb(dp[(i+1)%2][j+l][0][0],dp[i%2][j][k][l]);
          if((u!=v)^k)cmb(dp[(i+1)%2][j+l][1][0],dp[i%2][j][k][l]+x);
          if((u!=v)^k)cmb(dp[(i+1)%2][j+l][0][1],dp[i%2][j][k][l]+y);
          if((u==v)^k)cmb(dp[(i+1)%2][j+l][1][1],dp[i%2][j][k][l]+x+y);
          if((u==v)^k)cmb(dp[(i+1)%2][j+l][0][2],dp[i%2][j][k][l]+2*y);
          if((u!=v)^k)cmb(dp[(i+1)%2][j+l][1][2],dp[i%2][j][k][l]+x+2*y);
        }
        dp[i%2][j][k][l]=MAX;
      }
    }
    Lli res=dp[n%2][0][0][0];
    printf("%lli\n",res==MAX?-1:res);
  }
}