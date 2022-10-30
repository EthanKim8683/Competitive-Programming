#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=2e5;
const Lli MOD=998244353;

Lli dp[2];

Lli ipw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}

Lli inv(Lli x){
  return ipw(x,MOD-2);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  dp[1]=1;
  for(I i=0;i<n-1;i++)(dp[i%2]+=dp[1-i%2])%=MOD;
  printf("%lli\n",dp[n%2]*inv(ipw(2,n))%MOD);
}