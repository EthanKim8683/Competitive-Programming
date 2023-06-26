#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
pair<I,I>segs[N];
vector<I>unqs;
I fens[2*N+1];
tuple<I,I,I>evts[N];
I ress[N];
void upd(I i,I val){
  for(;i<=unqs.size();i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I l,r;cin>>l>>r;
    segs[i]={l,r};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    unqs.push_back(l);
    unqs.push_back(r);
  }
  sort(unqs.begin(),unqs.end());
  unqs.erase(unique(unqs.begin(),unqs.end()),unqs.end());
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    l=lower_bound(unqs.begin(),unqs.end(),l)-unqs.begin();
    r=lower_bound(unqs.begin(),unqs.end(),r)-unqs.begin();
    segs[i]={l,r};
  }
  for(I i=0;i<n;i++){
    auto[l,r]=segs[i];
    evts[i]={r,l,i};
  }
  sort(evts,evts+n);
  for(I i=0;i<n;i++){
    auto[x,y,j]=evts[i];
    ress[j]=qry(unqs.size())-qry(y),upd(y+1,1);
  }
  for(I i=0;i<n;i++)printf("%i\n",ress[i]);
}