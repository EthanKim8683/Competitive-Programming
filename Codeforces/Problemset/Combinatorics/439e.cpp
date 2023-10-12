#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MOD=1e9+7;
Lli facs[N+1];
vector<I>divs[N+1];
Lli dp[N+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=1;i<=N;i++)for(I j=i;j<=N;j+=i)divs[j].push_back(i);
  I q;cin>>q;
  while(q--){
    I n,f;cin>>n>>f;
    for(auto i:divs[n]){
      dp[i]=bin(i-f+f-1,f-1);
      for(auto j:divs[i])if(j<i)(dp[i]-=dp[j])%=MOD;
    }
    printf("%lli\n",(dp[n]+MOD)%MOD);
  }
}
/*
we are effectively finding the number of arrays of size f with sum n and gcd 1

for this we can find the number of arrays of size f with gcd 1 for each divisor
of n by subtracting the number of such arrays for divisors of their own
*/