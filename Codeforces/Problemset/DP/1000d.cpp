#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e3;
const Lli MOD=998244353;
I a_arr[N];
Lli dp[N+1];
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
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  facs[0]=1;
  for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a>0)for(I j=a;j+i+1<=n;j++)(dp[j+i+1]+=bin(j,a)*(dp[i]+1))%=MOD;
  }
  printf("%lli\n",dp[n]);
}