#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
const Lli MOD=998244353;
Lli dp[N+1][2];
B coms[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli m;cin>>n>>m;
  Lli prds=1;
  dp[0][0]=1;
  for(I i=0;i<n;i++){
    Lli v=i+1;
    if(v>1)for(Lli j=v*v;j<=n;j+=v)coms[j]=1;
    if(!coms[v])prds=min(prds*v,m+1);
    Lli a=m/prds,b=m-a;
    (dp[i+1][1]+=m%MOD*dp[i][1])%=MOD;
    (dp[i+1][1]+=b%MOD*dp[i][0])%=MOD;
    (dp[i+1][0]+=a%MOD*dp[i][0])%=MOD;
  }
  Lli res=0;
  for(I i=1;i<=n;i++)(res+=dp[i][1])%=MOD;
  printf("%lli\n",res);
}