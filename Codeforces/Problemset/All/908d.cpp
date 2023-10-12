#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I K=1000;
const Lli MOD=1e9+7;
Lli dp[K][K+1];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli k,p1,p2;cin>>k>>p1>>p2;
  Lli fac=inv(p1+p2);
  (p1*=fac)%=MOD,(p2*=fac)%=MOD;
  dp[0][1]=1;
  Lli res=0;
  for(I i=0;i<k;i++)for(I j=1;j<k;j++){
    (dp[i][j+1]+=dp[i][j]*p1)%=MOD;
    if(i+j<k){
      (dp[i+j][j]+=dp[i][j]*p2)%=MOD;
    }else{
      (res+=dp[i][j]*p2%MOD*(i+j))%=MOD;
    }
  }
  Lli exb=inv(p2)-1;
  for(I i=0;i<k;i++)(res+=dp[i][k]*(i+k+exb))%=MOD;
  printf("%lli\n",res);
}
/*
dynamic programming can be used to handle most cases, except for when a is
equal to k, whose expected value is the current number of subsequences plus
the expected number of a's before the next b in addition to the existing a's

the expected number of a's before the next b can be solved algebraically
(similar to the coin flip problem):

e = p1 * (e + 1) + p2 * 1

where e denotes the expected value, p1 the probability of a and p2 the
probability of b
*/