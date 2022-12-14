#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=200000;
pair<I,I>pnts[N];
pair<I,I>rngs[N];
I poss[N];
I dp[N];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,w;cin>>x>>w;
    pnts[i]={x,w};
  }
  for(I i=0;i<n;i++){
    auto[x,w]=pnts[i];
    I l=x-w,r=x+w;
    rngs[i]={l,r};
    poss[i]=l;
  }
  fill_n(dp,n,1);
  sort(rngs,rngs+n);
  sort(poss,poss+n);
  for(I i=0;i<n;i++){
    auto[l,r]=rngs[i];
    I j=upper_bound(poss,poss+n,r-1)-poss;
    if(i+1<n)cmb(dp[i+1],dp[i]);
    if(j<n)cmb(dp[j],dp[i]+1);
  }
  printf("%i\n",*max_element(dp,dp+n));
}