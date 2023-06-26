#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
pair<I,I>rngs[N];
vector<I>cpss;
I inds1[N],inds2[N];
I ress1[N],ress2[N];
I fens[2*N+1];
I cps(I x){
  return lower_bound(cpss.begin(),cpss.end(),x)-cpss.begin();
}
B cmp1(I a,I b){
  if(rngs[a].second==rngs[b].second)return rngs[a].first>rngs[b].first;
  return rngs[a].second<rngs[b].second;
}
B cmp2(I a,I b){
  if(rngs[a].first==rngs[b].first)return rngs[a].second>rngs[b].second;
  return rngs[a].first<rngs[b].first;
}
void upd(I i,I val){
  for(;i<=cpss.size();i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I qry(I l,I r){
  return qry(r)-qry(l);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    rngs[i]={x,y};
    cpss.push_back(x);
    cpss.push_back(y);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  for(I i=0;i<n;i++){
    auto[x,y]=rngs[i];
    rngs[i]={cps(x),cps(y)};
  }
  iota(inds1,inds1+n,0);
  iota(inds2,inds2+n,0);
  sort(inds1,inds1+n,cmp1);
  sort(inds2,inds2+n,cmp2);
  for(I i=0;i<n;i++){
    I a=inds1[i];
    ress1[a]=qry(rngs[a].first,cpss.size());
    upd(rngs[a].first+1,1);
  }
  fill_n(fens,cpss.size()+1,0);
  for(I i=0;i<n;i++){
    I a=inds2[i];
    ress2[a]=qry(rngs[a].second,cpss.size());
    upd(rngs[a].second+1,1);
  }
  for(I i=0;i<n;i++)printf("%i ",ress1[i]);
  printf("\n");
  for(I i=0;i<n;i++)printf("%i ",ress2[i]);
  printf("\n");
}