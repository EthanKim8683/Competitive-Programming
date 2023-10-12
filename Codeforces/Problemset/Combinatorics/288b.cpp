#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I K=8;
const Lli MOD=1e9+7;
Lli facs[K+1];
Lli dp[K+1][K+1];
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
  for(I i=1;i<=K;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  dp[1][1]=k;
  for(I i=1;i<k;i++)for(I j=1;j<=k;j++)for(I l=1;l<=k-i;l++)(dp[i+l][l]+=dp[i][j]*bin(k-i,l)%MOD*mpw(j,l))%=MOD;
  Lli res=0;
  for(I i=1;i<=k;i++)(res+=dp[k][i])%=MOD;
  printf("%lli\n",res*mpw(n-k,n-k)%MOD);
}
/*
since all houses in [1, k] lead to house 1, none of the houses in [k + 1, n]
can have plaque in [1, k]

for the plaques of houses, we can use dynamic programming to build a tree
layer by layer, then loop the root (1) back to one a node in [1, k]
*/