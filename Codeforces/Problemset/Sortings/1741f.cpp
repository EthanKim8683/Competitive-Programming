#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2e5;
const Lli MAX=1e18;
const Lli MIN=-MAX;
pair<I,I>segs[N];
I cols[N];
vector<I>bucs[N];
set<I>lfts,rgts;
Lli ress[N];
I inds[N];
Lli upps[N];
set<pair<Lli,I>>pres;
B cmp1(I a,I b){
  return segs[a].first<segs[b].first;
}
B cmp2(I a,I b){
  return segs[a].second>segs[b].second;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)bucs[i].clear();
    for(I i=0;i<n;i++){
      I l,r,c;cin>>l>>r>>c,c--;
      segs[i]={l,r},cols[i]=c;
      bucs[c].push_back(i);
    }
    fill_n(ress,n,MAX);
    lfts.clear(),rgts.clear();
    for(I i=0;i<n;i++){
      for(auto j:bucs[i]){
        auto[l,r]=segs[j];
        auto upp=rgts.upper_bound(r);
        auto low=lfts.lower_bound(l);
        if(upp!=rgts.begin())ress[j]=min(ress[j],(Lli)(l-*prev(upp)));
        if(low!=lfts.end())ress[j]=min(ress[j],(Lli)(*low-r));
      }
      for(auto j:bucs[i]){
        auto[l,r]=segs[j];
        lfts.insert(l);
        rgts.insert(r);
      }
    }
    lfts.clear(),rgts.clear();
    for(I i=n-1;i>=0;i--){
      for(auto j:bucs[i]){
        auto[l,r]=segs[j];
        auto upp=rgts.upper_bound(r);
        auto low=lfts.lower_bound(l);
        if(upp!=rgts.begin())ress[j]=min(ress[j],(Lli)(l-*prev(upp)));
        if(low!=lfts.end())ress[j]=min(ress[j],(Lli)(*low-r));
      }
      for(auto j:bucs[i]){
        auto[l,r]=segs[j];
        lfts.insert(l);
        rgts.insert(r);
      }
    }
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp1);
    fill_n(upps,n,MIN);
    pres.clear();
    for(I i=0;i<n;i++)pres.insert({upps[i],i});
    for(I i=0,j=0;i<n;i++){
      I k=inds[i],c1=cols[k];auto[l1,r1]=segs[k];
      for(;j<n;j++){
        I l=inds[j],c2=cols[l];auto[l2,r2]=segs[l];
        if(l2>l1)break;
        pres.erase({upps[c2],c2});
        upps[c2]=max(upps[c2],(Lli)r2);
        pres.insert({upps[c2],c2});
      }
      for(auto it=pres.rbegin();it!=pres.rend();it++){
        if(it->second==c1)continue;
        ress[k]=min(ress[k],l1-it->first);break;
      }
    }
    iota(inds,inds+n,0);
    sort(inds,inds+n,cmp2);
    fill_n(upps,n,MAX);
    pres.clear();
    for(I i=0;i<n;i++)pres.insert({upps[i],i});
    for(I i=0,j=0;i<n;i++){
      I k=inds[i],c1=cols[k];auto[l1,r1]=segs[k];
      for(;j<n;j++){
        I l=inds[j],c2=cols[l];auto[l2,r2]=segs[l];
        if(r2<r1)break;
        pres.erase({upps[c2],c2});
        upps[c2]=min(upps[c2],(Lli)l2);
        pres.insert({upps[c2],c2});
      }
      for(auto it=pres.begin();it!=pres.end();it++){
        if(it->second==c1)continue;
        ress[k]=min(ress[k],it->first-r1);break;
      }
    }
    for(I i=0;i<n;i++)printf("%i ",max(ress[i],0ll));
    printf("\n");
  }
}