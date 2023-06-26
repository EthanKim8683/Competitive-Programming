#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const Lli MOD=1e9+7;
I a_arr[10];
Lli facs[N+1],invs[N+1];
Lli dp[10][10+1][N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  Lli res=1;
  (res*=facs[n])%=MOD;
  (res*=invs[k])%=MOD;
  (res*=invs[n-k])%=MOD;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<10;i++)cin>>a_arr[i];
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=n;i++)invs[i]=inv(facs[i]);
  for(I i=1;i<10;i++)for(I j=0;j<=n-1;j++)dp[i][0][j]=1;
  for(I i=1;i<10;i++)for(I j=0;j<10;j++)for(I k=0;k<=n-1;k++)for(I l=a_arr[j]-(i==j);l<=k;l++)(dp[i][j+1][k-l]+=dp[i][j][k]*bin(k,l))%=MOD;
  Lli res=0;
  for(I i=1;i<10;i++)(res+=dp[i][10][0])%=MOD;
  printf("%lli\n",res);
}