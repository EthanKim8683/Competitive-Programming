#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I K=1000;
const I C=1000;
const Lli MOD=1e9+7;

I c_arr[K];
Lli dp[C+1][K+1];
I ps[K+1];
Lli facs[C+1];

Lli mpw(Lli x,I y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}

Lli inv(Lli x){
  return mpw(x,MOD-2);
}

Lli bin(I n,I k){
  if(n<k)return 0;
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=C;i++)facs[i]=facs[i-1]*i%MOD;
  I k;cin>>k;
  for(I i=0;i<k;i++)cin>>c_arr[i];
  for(I i=0;i+1<k;i++)ps[i+1]=c_arr[i];
  for(I i=0;i+1<k;i++)ps[i+1]+=ps[i];
  I tot=accumulate(c_arr,c_arr+k,0);
  dp[0][0]=1;
  for(I i=0;i<tot;i++)for(I j=0;j<k;j++){
    (dp[i+1][j+1]+=dp[i][j]*bin(i-ps[j],c_arr[j]-1))%=MOD;
    (dp[i+1][j]+=dp[i][j])%=MOD;
  }
  printf("%lli\n",dp[tot][k]);
}