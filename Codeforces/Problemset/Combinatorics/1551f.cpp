#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I K=100;
const Lli MOD=1e9+7;
vector<I>adjs[N];
Lli facs[N+1];
I cnts[N],bpts[2];
Lli dp[N][K+1];
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
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
}
void dfs(I a,I p,I d=0){
  cnts[d]++;
  for(auto b:adjs[a])if(b!=p)dfs(b,a,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I i=0;i<n-1;i++){
      I u,v;cin>>u>>v,u--,v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    Lli res=0;
    for(I i=0;i<n;i++){
      for(I j=0;j<n;j++){
        for(I l=0;l<=k;l++)dp[j][l]=0;
        dp[j][0]=1;
      }
      for(auto j:adjs[i]){
        fill_n(cnts,n,0);
        dfs(j,i);
        for(I l=0;l<n;l++){
          if(cnts[l]==0)break;
          for(I m=k-1;m>=0;m--)(dp[l][m+1]+=cnts[l]*dp[l][m])%=MOD;
        }
      }
      for(I j=0;j<n;j++)(res+=dp[j][k])%=MOD;
    }
    if(k==2){
      fill_n(cnts,n,0);
      dfs(0,-1);
      bpts[0]=bpts[1]=0;
      for(I i=0;i<n;i++)bpts[i%2]+=cnts[i];
      (res+=(Lli)bpts[0]*bpts[1])%=MOD;
    }
    printf("%lli\n",res);
  }
}
/*
for every set of equidistant vertices there exists a central vertex that is
equidistant to all vertices of the set

for each central vertex we can find the number of subsets of vertices, each
from different subtrees, such that each vertex is distance x from the center

if we collect the number of vertices at each depth of each subtree, we can
calculate the number of ways to choose vertices at that depth using dynamic
programming, since the total maximum depth across all subtrees will not
exceed n
*/