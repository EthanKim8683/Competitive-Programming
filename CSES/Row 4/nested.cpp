#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
pair<I,I>rngs[N];
I inds1[N],inds2[N];
I ress1[N],ress2[N];
B cmp1(I a,I b){
  if(rngs[a].second==rngs[b].second)return rngs[a].first>rngs[b].first;
  return rngs[a].second<rngs[b].second;
}
B cmp2(I a,I b){
  if(rngs[a].first==rngs[b].first)return rngs[a].second>rngs[b].second;
  return rngs[a].first<rngs[b].first;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    rngs[i]={x,y};
  }
  iota(inds1,inds1+n,0);
  iota(inds2,inds2+n,0);
  sort(inds1,inds1+n,cmp1);
  sort(inds2,inds2+n,cmp2);
  I low=-1;
  for(I i=0;i<n;i++){
    I a=inds1[i];
    ress1[a]=low>=rngs[a].first;
    low=max(low,rngs[a].first);
  }
  I upp=-1;
  for(I i=0;i<n;i++){
    I a=inds2[i];
    ress2[a]=upp>=rngs[a].second;
    upp=max(upp,rngs[a].second);
  }
  for(I i=0;i<n;i++)printf("%i ",ress1[i]);
  printf("\n");
  for(I i=0;i<n;i++)printf("%i ",ress2[i]);
  printf("\n");
}