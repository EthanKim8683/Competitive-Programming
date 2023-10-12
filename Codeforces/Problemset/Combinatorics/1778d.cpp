#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e6;
const Lli MOD=998244353;
Lli dp[N+1];
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
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S a;cin>>a;
    S b;cin>>b;
    I cnt=0;
    for(I i=0;i<n;i++)cnt+=a[i]!=b[i];
    dp[n]=1;
    for(I i=n-1;i-1>=0;i--)dp[i]=n*inv(i)%MOD*(1+(1-i*inv(n)%MOD)*dp[i+1]%MOD)%MOD;
    Lli res=0;
    for(I i=1;i<=cnt;i++)(res+=dp[i])%=MOD;
    printf("%lli\n",(res+MOD)%MOD);
  }
}
/*
if we take the number of different characters m between the two strings, the
expected number of moves will be equal to the expected number of moves to
invert m distinguishable characters

for i characters remaining, denote E(i) the expected number of moves before
i - 1 characters remain

E(i) = 1 + (1 - i / n) * (E(i + 1) + E(i))

we can solve for E(i) to get

E(i) = (n / i) * (1 + (1 - i / n) * E(i + 1))
*/