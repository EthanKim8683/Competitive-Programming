#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
const I MIN=-1e9;
vector<tuple<I,I,I>>adjs[N];
priority_queue<tuple<Lli,I,I>>ques;
set<I>rems;
Lli ress[N];
tuple<I,I,I,I>segs[2*N];
vector<tuple<I,I,I>>upps[N];
I n;
void asn(I i,tuple<I,I,I,I>val){
  segs[i+n]=val;
}
void bld(){
  for(I i=n-1;i>0;i--)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
void upd(I i,tuple<I,I,I,I>val){
  for(segs[i+=n]=val;i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
tuple<I,I,I,I>qry(I l,I r){
  tuple<I,I,I,I>res={MIN,MIN,MIN,MIN};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
pair<I,I>top(I i){
  auto[r,l,v,w]=qry(0,i+1);
  if(r<=i)return{MIN,MIN};
  return{v,w};
}
void pop(I i){
  auto[r,l,v,w]=qry(0,i+1);
  upps[l].pop_back();
  if(upps[l].size()){
    auto[r,v,w]=upps[l].back();
    upd(l,{r,l,v,w});
  }else{
    upd(l,{MIN,MIN,MIN,MIN});
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q,s;cin>>n>>q>>s,s--;
  for(I i=0;i<q;i++){
    I t;cin>>t;
    if(t==1){
      I v,u,w;cin>>v>>u>>w,v--,u--;
      adjs[v].push_back({u,u+1,w});
    }
    if(t==2){
      I v,l,r,w;cin>>v>>l>>r>>w,v--,l--;
      adjs[v].push_back({l,r,w});
    }
    if(t==3){
      I v,l,r,w;cin>>v>>l>>r>>w,v--,l--;
      upps[l].push_back({r,v,w});
    }
  }
  fill_n(segs,2*n,tuple<I,I,I,I>{MIN,MIN,MIN,MIN});
  for(I i=0;i<n;i++)if(upps[i].size()){
    sort(upps[i].begin(),upps[i].end());
    auto[r,v,w]=upps[i].back();
    asn(i,{r,i,v,w});
  }
  bld();
  fill_n(ress,n,MAX);
  for(I i=0;i<n;i++)rems.insert(i);
  ques.push({0,s,s+1});
  while(ques.size()){
    auto[d,l1,r1]=ques.top();ques.pop(),d=-d;
    auto end=rems.lower_bound(r1);
    for(auto it=rems.lower_bound(l1);it!=end;){
      I a=*it;
      ress[a]=d;
      for(auto[l2,r2,w]:adjs[a])ques.push({-(d+w),l2,r2});
      while(1){
        auto[v,w]=top(a);
        if(v==MIN)break;
        ques.push({-(d+w),v,v+1});
        pop(a);
      }
      it=rems.erase(it);
    }
  }
  for(I i=0;i<n;i++)printf("%lli ",ress[i]==MAX?-1:ress[i]);
}
/*
ee can solve the problem using dijkstra's algorithm, but with an emphasis on
using each edge at most once

edges of type 1 can be handled normally

edges of type 2 can be handled using a set of unvisited nodes, where ranges
are handled by visiting all unvisited nodes within said range

edges of type 3 can be handled by traversing the edge starting with the first
node within its range
*/