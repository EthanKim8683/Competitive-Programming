#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I MAX=1e9;
pair<I,I>vecs[N];
pair<I,I>abss[N];
I inds[N];
multimap<I,I>pres;
pair<I,I>trns[]{{1,1},{-1,1},{1,-1},{-1,-1}};
B cmp(I a,I b){
  return abss[a]<abss[b];
}
pair<I,I>trn(pair<I,I>a,I b){
  auto[x1,y1]=a;auto[x2,y2]=trns[b];
  return{x1*x2,y1*y2};
}
pair<I,I>add(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  return{x1+x2,y1+y2};
}
I mag(pair<I,I>a){
  auto[x,y]=a;
  return x*x+y*y;
}
I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    vecs[i]={x,y};
    abss[i]={abs(x),abs(y)};
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  tuple<I,I,I>res={MAX,-1,-1};
  for(I i=0;i<n;i++){
    I j=inds[i];auto[x1,y1]=abss[j];
    I rad=ceil(sqrt(get<0>(res)));
    auto low=pres.lower_bound(y1-rad);
    auto upp=pres.upper_bound(y1+rad);
    for(auto it=low;it!=upp;){
      I k=it->second;auto[x2,y2]=abss[k];
      I dis1=abs(x1-x2),dis2=abs(y1-y2);
      res=min(res,{dis1*dis1+dis2*dis2,j,k});
      it=dis1*dis1>=get<0>(res)?pres.erase(it):next(it);
    }
    pres.insert({y1,j});
  }
  auto[dis,i,j]=res;
  for(I k1=0;k1<4;k1++)for(I k2=0;k2<4;k2++){
    if(mag(add(trn(vecs[i],k1),trn(vecs[j],k2)))!=dis)continue;
    printf("%i %i %i %i\n",i+1,k1+1,j+1,k2+1),exit(0);
  }
}