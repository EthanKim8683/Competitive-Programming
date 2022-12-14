#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1e5;
const Lli MOD=1e9;
pair<I,I>rngs[N];
I rgts[N];
Lli dp[N];//how many end at i
Lli ps[N];//how many end at or before i
B cmp(pair<I,I>a,pair<I,I>b){
  return a.second<b.second;
}
I main(){
#ifndef ETHANKIM8683
  freopen("help.in","r",stdin);
  freopen("help.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  sort(rngs,rngs+n,cmp);
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    rgts[i]=r;
  }
  fill_n(dp,n,1),ps[0]=1;
  for(I i=1;i<n;i++){
    auto[l,r]=rngs[i];
    I j=lower_bound(rgts,rgts+n,l)-rgts-1;
    if(j>=0)(dp[i]+=ps[j])%=MOD;
    (ps[i]=ps[i-1]+dp[i])%=MOD;
  }
  for(I i=0;i<n;i++)printf("%lli ",dp[i]);
  printf("\n");
  for(I i=0;i<n;i++)printf("%lli ",ps[i]);
  printf("\n");
}