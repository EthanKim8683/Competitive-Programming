#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MOD=1e9+7;

I ps[30][N+1];
Lli dp[N+1][30][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<30;i++)for(I j=0;j<=n;j++)ps[i][j]=0;
    for(I i=0;i<=n;i++)for(I j=0;j<30;j++)for(I k=0;k<2;k++)dp[i][j][k]=0;
    for(I i=0;i<m;i++){
      I l,r,x;cin>>l>>r>>x,l--;
      for(I j=0;j<30;j++)if(!(x>>j&1))ps[j][l]++,ps[j][r]--;
    }
    for(I i=0;i<30;i++)for(I j=0;j<n;j++)ps[i][j+1]+=ps[i][j];
    for(I i=0;i<30;i++)dp[0][i][0]=1;
    for(I i=0;i<n;i++){
      for(I j=0;j<30;j++){
        (dp[i+1][j][0]+=dp[i][j][0])%=MOD;
        (dp[i+1][j][1]+=dp[i][j][1])%=MOD;
        if(!ps[j][i]){
          (dp[i+1][j][1]+=dp[i][j][0])%=MOD;
          (dp[i+1][j][0]+=dp[i][j][1])%=MOD;
        }else{
          (dp[i+1][j][0]+=dp[i][j][0])%=MOD;
          (dp[i+1][j][1]+=dp[i][j][1])%=MOD;
        }
      }
    }
    Lli res=0;
    for(I i=0;i<30;i++)(res+=dp[n][i][1]*(1<<i))%=MOD;
    printf("%lli\n",res);
  }
}