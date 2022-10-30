#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e6;
const Lli MOD=998244353;

Lli facs[N+1];
Lli dp[N+1];
Lli ps[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=1;i<=n;i++)for(I j=2*i;j<=N;j+=i)facs[j]+=1;
  ps[0]=dp[0]=1;
  for(I i=1;i<=n;i++){
    (ps[i]+=ps[i-1])%=MOD;
    (dp[i]+=ps[i])%=MOD;
    (dp[i]+=facs[i])%=MOD;
    (ps[i]+=dp[i])%=MOD;
  }
  printf("%lli\n",dp[n]);
}