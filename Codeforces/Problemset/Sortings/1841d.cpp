#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2000;
const I MAX=1e9;
pair<I,I>segs[N];
vector<pair<I,I>>rngs;
set<pair<I,I>>bufs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){
      I l,r;cin>>l>>r;
      segs[i]={l,r};
    }
    sort(segs,segs+n),rngs.clear();
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
      auto[l1,r1]=segs[i];
      auto[l2,r2]=segs[j];
      if(l2>r1)continue;
      rngs.push_back({l1,max(r1,r2)});
    }
    sort(rngs.begin(),rngs.end());
    I upp=0;
    bufs.clear();
    for(auto[l,r]:rngs){
      while(bufs.size()){
        auto it=bufs.begin();
        auto[x,val]=*it;
        if(x>=l)break;
        bufs.erase(it);
        upp=max(upp,val);
      }
      bufs.insert({r,upp+2});
    }
    for(auto[x,val]:bufs)upp=max(upp,val);
    printf("%i\n",n-upp);
  }
}