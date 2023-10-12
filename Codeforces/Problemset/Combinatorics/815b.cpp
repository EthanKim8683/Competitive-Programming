#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200000;
const I SQTN=448;
const Lli MOD=1e9+7;
I a_arr[N];
Lli facs[N+1];
Lli dp[4][N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I m=(n-1)/4*4;
  for(I i=0;i<=m;i++)if(i%2==0)dp[0][i]=bin(m/2,i/2);
  for(I i=0,t=n/2%2;i<n-1-m;t^=i%2,i++)for(I j=0;j<=m+i;j++){
    if(t==j%2){
      (dp[i+1][j]+=dp[i][j])%=MOD;
      (dp[i+1][j+1]-=dp[i][j])%=MOD;
    }else{
      (dp[i+1][j]+=dp[i][j])%=MOD;
      (dp[i+1][j+1]+=dp[i][j])%=MOD;
    }
  }
  Lli res=0;
  for(I i=0;i<n;i++)(res+=a_arr[i]*dp[n-1-m][i])%=MOD;
  printf("%lli\n",(res+MOD)%MOD);
}
/*
note that, if we start from a single number and work upwards, the contribution
of five numbers to the original number is [1, 0, 2, 0, 1], which looks like the
third row of Pascal's triangle, and tiles

this means that we can find the contribution of each element using the binomial
theorem
*/