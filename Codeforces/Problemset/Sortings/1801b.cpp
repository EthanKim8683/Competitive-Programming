#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=500000;
const I MAX=2e9;
const I MIN=-1e9;
pair<I,I>deps[N];
multiset<I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++){
      I a,b;cin>>a>>b;
      deps[i]={a,-b};
    }
    sort(deps,deps+n);
    rems.clear();
    for(I i=0;i<n;i++)rems.insert(-deps[i].second);
    I res=MAX,upp=MIN;
    for(I i=n-1;i>=0;i--){
      auto[a,b]=deps[i];b=-b;
      rems.erase(rems.find(b));
      res=min(res,abs(upp-a));
      auto it1=rems.upper_bound(a);
      if(it1!=rems.begin())res=min(res,abs(max(upp,*prev(it1))-a));
      auto it2=rems.lower_bound(a);
      if(it2!=rems.end())res=min(res,abs(max(upp,*it2)-a));
      upp=max(upp,b);
    }
    printf("%i\n",res);
  }
}