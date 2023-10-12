#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I MAX=1e9;
I a_arr[N];
I pres[N];
set<pair<I,I>>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,d;cin>>n>>d;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I pre=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      pres[i]=a-pre-1,pre=a;
    }
    rems.clear();
    for(I i=0;i<n;i++)rems.insert({pres[i],i});
    I res=0;
    for(I i=0;i+1<n;i++){
      rems.erase({pres[i],i});
      rems.erase({pres[i+1],i+1});
      rems.insert({pres[i]+pres[i+1]+1,i+1});
      auto tmp=*prev(rems.end());
      rems.erase(tmp);
      res=max(res,min(rems.size()?rems.begin()->first:MAX,(tmp.first-1)/2));
      rems.insert(tmp);
      res=max(res,min(rems.begin()->first,d-pre-1));
      rems.erase({pres[i]+pres[i+1]+1,i+1});
      rems.insert({pres[i],i});
      rems.insert({pres[i+1],i+1});
    }
    rems.erase({pres[n-1],n-1});
    res=max(res,min(rems.begin()->first,d-a_arr[n-2]-1));
    rems.insert({pres[n-1],n-1});
    printf("%i\n",res);
  }
}