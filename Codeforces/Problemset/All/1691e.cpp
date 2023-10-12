#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
multimap<I,I>curs[2];
tuple<I,I,I>segs[N];
I pars[N];
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){
      I c,l,r;cin>>c>>l>>r;
      segs[i]={l,r,c};
    }
    for(I i=0;i<2;i++)curs[i].clear();
    sort(segs,segs+n);
    fill_n(pars,n,-1);
    for(I i=0;i<n;i++){
      auto[l,r,c]=segs[i];
      while(curs[!c].size()){
        auto it=curs[!c].begin();
        if(it->first>=l)break;
        curs[!c].erase(it);
      }
      while(curs[!c].size()>1){
        auto it=curs[!c].begin();
        uni(i,it->second);
        curs[!c].erase(it);
      }
      if(curs[!c].size()){
        auto it=curs[!c].begin();
        uni(i,it->second);
      }
      curs[c].insert({r,i});
    }
    I res=0;
    for(I i=0;i<n;i++)res+=fnd(i)==i;
    printf("%i\n",res);
  }
}
/*
we can use sweep line for both red and blue segments merging same-color
segments at the start of segments of different color
*/