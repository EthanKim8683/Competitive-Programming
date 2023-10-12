#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I P=1e7;
pair<I,I>rngs[N];
set<pair<I,I>>upps;
I inds[N];
I ress[N];
B cmp(I a,I b){
  return rngs[a]<rngs[b];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    rngs[i]={l,r};
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=1,j=0;i<=P;i++){
    for(;j<n;j++){
      I k=inds[j];
      auto[l,r]=rngs[k];
      if(l>i)break;
      upps.insert({r,k});
    }
    if(!upps.size())continue;
    auto it=upps.begin();
    ress[it->second]=i;
    upps.erase(it);
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}