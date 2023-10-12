#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const Lli MAX=1e18;
const I MIN=-1e9;
pair<I,I>vols[N];
I inds[N];
multiset<I>rems[N];
pair<I,I>segs[2*N];
B viss[N];
I n;
void upd(I i,pair<I,I>val){
  for(segs[i+=n]=val;i>>=1;)segs[i]=max(segs[i<<1],segs[i<<1|1]);
}
void add(I i,I val){
  rems[i].insert(val);
  upd(i,{*prev(rems[i].end()),i});
}
void rem(I i){
  rems[i].erase(prev(rems[i].end()));
  upd(i,{rems[i].size()?*prev(rems[i].end()):MIN,i});
}
pair<I,I>qry(I l,I r){
  pair<I,I>res={MIN,-1};
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res=max(res,segs[l++]);
    if(r&1)res=max(res,segs[--r]);
  }
  return res;
}
B cmp(I a,I b){
  return vols[a].second<vols[b].second;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++){
      I m,p;cin>>m>>p;
      vols[i]={p,m};
    }
    sort(vols,vols+n);
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp);
    fill_n(viss,n,0);
    fill_n(segs,2*n,pair<I,I>{MIN,-1});
    for(I i=0;i<n;i++)rems[i].clear();
    I cnt=0;
    Lli res=0;
    for(I i=0,j=0;i<n;i++){
      for(;j<n;j++){
        I k=inds[j];
        if(viss[k])continue;
        auto[p1,m1]=vols[k];
        if(m1>cnt)break;
        viss[k]=1,cnt++;
      }
      if(!viss[i]){
        auto[p1,m1]=vols[i];
        auto[p2,m2]=qry(0,cnt+1);
        if(p2!=MIN)rem(m2),res-=p2;
        add(m1,p1),res+=p1;
        viss[i]=1,cnt++;
      }
    }
    printf("%lli\n",res);
  }
}
/*
we can solve this problem greedily because, if we keep a running count of
voters and add all voters meeting the count requirement, we may run into
voters which require paying off, which we can either "trade" or pay off

when we trade a voter, we are un-paying-off a paid-off voter meeting the
count requirement and instead paying off the current voter

by itself, this will yield the minimum number of paid-off voters since, any
fewer paid-off voters and the count-dependent voters won't vote

however, by sorting the voters in non-decreasing order and trading the maximum
cost voter each time, we can also minimize the total cost of the paid-off
voters
*/