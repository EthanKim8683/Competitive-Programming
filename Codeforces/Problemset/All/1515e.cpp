#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=400;
Lli facs[N+1];
Lli pows[N+1];
Lli bins[N+1][N+1];
Lli dp[N+1][N+1];
Lli m;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=m;y;y>>=1,(x*=x)%=m)if(y&1)(res*=x)%=m;
  return res;
}
Lli inv(Lli x){
  return mpw(x,m-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[n-k]*facs[k])%m;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%m;
  pows[0]=1;
  for(I i=1;i<=n;i++)pows[i]=pows[i-1]*2%m;
  dp[0][0]=1;
  for(I i=0;i<=n;i++)for(I j=0;j<=i;j++)bins[i][j]=bin(i,j);
  for(I i=0;i<n;i++)for(I j=0;j<=i;j++){
    for(I k=1;i+k+1<n;k++)(dp[i+k+1][j+1]+=dp[i][j]*pows[k-1]%m*bins[i-j+k][k])%=m;
    (dp[n][j+1]+=dp[i][j]*pows[n-i-1]%m*bins[i-j+n-i][n-i])%=m;
  }
  Lli res=0;
  for(I i=0;i<=n;i++)(res+=dp[n][i])%=m;
  printf("%lli\n",res);
}