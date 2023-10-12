#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MAX=1e9;
pair<I,I>cnts[N];
vector<I>unqs;
multiset<I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    fill_n(cnts,n,pair<I,I>{0,0});
    for(I i=0;i<n;i++){
      I a,f;cin>>a>>f,a--;
      cnts[a].first++;
      cnts[a].second+=f;
    }
    sort(cnts,cnts+n);
    I pre=MAX,acc=0;
    unqs.clear();
    for(I i=n-1;i>=0;i--){
      auto[tot,giv]=cnts[i];
      tot=min(tot,pre-1),pre=tot;
      if(tot<=0)continue;
      unqs.push_back(tot),acc+=tot;
    }
    I res=0;
    rems.clear();
    for(I i=0,j=n-1;i<unqs.size();i++){
      for(;j>=0;j--){
        auto[tot,giv]=cnts[j];
        if(tot<unqs[i])break;
        rems.insert(giv);
      }
      auto it=prev(rems.end());
      res+=min(*it,unqs[i]);
      rems.erase(it);
    }
    printf("%i %i\n",acc,res);
  }
}