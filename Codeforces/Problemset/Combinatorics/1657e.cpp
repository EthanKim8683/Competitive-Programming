#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=250;
const I K=250;
const Lli MOD=998244353;
Lli dp[N][K+1];
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
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I n,k;cin>>n>>k;
  dp[0][0]=1;
  for(I i=0;i<n-1;i++)for(I j=0;j+1<=k;j++){
    (dp[i][j+1]+=dp[i][j])%=MOD;
    for(I l=1;i+l<=n-1;l++)(dp[i+l][j+1]+=dp[i][j]*bin(n-1-i,l)%MOD*mpw(k-(j+1)+1,l*i+l*(l-1)/2)%MOD)%=MOD;
  }
  Lli res=0;
  for(I i=0;i<=k;i++)(res+=dp[n-1][i])%=MOD;
  printf("%lli\n",res);
}
/*
upon constructing a star tree (a tree where all edges are between 1 and j for
all j in [1, n)), we add edges between pairs of nodes such that neither edge
connecting the nodes to node 1 has weight greater than that of the edge to be
added

if we collect the edge weights of the star tree into an array W of size n - 1,
the number of ways to add the remaining edges is the product of
k - max(W[i], W[j]) + 1 for all indices i, j in [0, n - 1)

if we organize indices i such that W[i] = w into buckets, the number of
assignments can be found using dynamic programming

furthermore, the contribution of a bucket with x indices equals k - w + 1 ^
(x * y + x * (x - 1) / 2), where y is the number of indices in buckets with
smaller w
*/