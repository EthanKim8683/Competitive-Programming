#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=500;
const Lli MOD=1e9+7;
Lli dp[N+1][N+1][2];
Lli bins[N+1][N+1];
Lli facs[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=n;i++)for(I j=0;j<=i;j++)bins[i][j]=bin(i,j);
  for(I i=0;i+2<=n;i++)if(s[i]==s[i+1])dp[i][i+2][1]=1;
  for(I i=4;i<=n;i+=2)for(I j=0;j+i<=n;j++){
    if(s[j]==s[j+i-1])(dp[j][j+i][1]+=dp[j+1][j+i-1][0]+dp[j+1][j+i-1][1])%=MOD;
    for(I k=0;k<=i;k+=2){
      (dp[j][j+i][0]+=dp[j][j+k][1]*dp[j+k][j+i][1]%MOD*bins[i/2][k/2])%=MOD;
      (dp[j][j+i][0]+=dp[j][j+k][0]*dp[j+k][j+i][1]%MOD*bins[i/2][k/2])%=MOD;
    }
  }
  printf("%lli\n",(dp[0][n][0]+dp[0][n][1])%MOD);
}