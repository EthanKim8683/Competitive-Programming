#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
I pars[N];
set<I>incs1[N],outs1[N];
set<I>incs2[N],outs2[N];
set<I>nods[N];
Lli res=0;
I fnd(I i){
  return pars[i]<0?i:pars[i]=fnd(pars[i]);
}
I siz(I i){
  return-pars[fnd(i)];
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  Lli siz1=siz(a),siz2=siz(b);
  res-=siz1*(incs1[a].size()+siz1-1);
  res-=siz2*(incs1[b].size()+siz2-1);
  for(auto c:incs1[b]){
    outs1[c].erase(b);
    if(fnd(c)==a)continue;
    incs1[a].insert(c);
    outs1[c].insert(a);
  }
  for(auto c:nods[b]){
    nods[a].insert(c);
    if(!outs1[c].count(a))continue;
    outs1[c].erase(a);
    incs1[a].erase(c);
  }
  for(auto c:incs2[b]){
    outs2[c].erase(b);
    if(c==a)continue;
    incs2[a].insert(c);
    outs2[c].insert(a);
  }
  for(auto c:outs2[b]){
    incs2[c].erase(b);
    if(c==a)continue;
    outs2[a].insert(c);
    incs2[c].insert(a);
  }
  pars[a]+=pars[b],pars[b]=a;
  Lli siz3=siz(a);
  res+=siz3*(incs1[a].size()+siz3-1);
  for(auto c:incs2[b]){
    if(c==a)continue;
    if(outs2[a].count(c))uni(a,c);
  }
  for(auto c:outs2[b]){
    if(c==a)continue;
    if(outs2[c].count(a))uni(c,a);
  }
  incs1[b].clear();
  incs2[b].clear(),outs2[b].clear();
  nods[b].clear();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++)nods[i].insert(i);
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    I c=fnd(a),d=fnd(b);
    if(c!=d){
      if(!outs1[a].count(d)){
        incs1[d].insert(a);
        outs1[a].insert(d);
        res+=siz(d);
      }
      if(!outs2[c].count(d)){
        incs2[d].insert(c);
        outs2[c].insert(d);
        if(outs2[d].count(c))uni(c,d);
      }
    }
    printf("%lli\n",res);
  }
}