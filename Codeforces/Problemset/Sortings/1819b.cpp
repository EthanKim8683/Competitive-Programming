#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
pair<I,I>rcts[N];
set<pair<I,I>>rems1,rems2;
set<pair<Lli,Lli>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    Lli tot=0;
    pair<I,I>upp1={0,0},upp2={0,0};
    for(I i=0;i<n;i++){
      I a,b;cin>>a>>b;
      rcts[i]={a,b};
      tot+=(Lli)a*b;
      upp1=max(upp1,{a,i});
      upp2=max(upp2,{b,i});
    }
    ress.clear();
    if(tot%upp1.first==0){
      auto[w,j]=upp1;
      Lli h=tot/w-rcts[j].second;
      rems1.clear(),rems2.clear();
      for(I i=0;i<n;i++)if(i!=j){
        auto[a,b]=rcts[i];
        rems1.insert({a,i});
        rems2.insert({b,i});
      }
      B vld=1;
      for(I j=0;j<n-1;j++){
        auto it1=prev(rems1.end());
        if(it1->first==w){
          I k=it1->second;
          auto[a,b]=rcts[k];
          rems1.erase({a,k});
          rems2.erase({b,k});
          h-=b;
          continue;
        }
        auto it2=prev(rems2.end());
        if(it2->first==h){
          I k=it2->second;
          auto[a,b]=rcts[k];
          rems1.erase({a,k});
          rems2.erase({b,k});
          w-=a;
          continue;
        }
        vld=0;
        break;
      }
      if(vld){
        Lli w=upp1.first,h=tot/w;
        ress.insert({w,h});
      }
    }
    if(tot%upp2.first==0){
      auto[h,j]=upp2;
      Lli w=tot/h-rcts[j].first;
      rems1.clear(),rems2.clear();
      for(I i=0;i<n;i++)if(i!=j){
        auto[a,b]=rcts[i];
        rems1.insert({a,i});
        rems2.insert({b,i});
      }
      B vld=1;
      for(I j=0;j<n-1;j++){
        auto it1=prev(rems1.end());
        if(it1->first==w){
          I k=it1->second;
          auto[a,b]=rcts[k];
          rems1.erase({a,k});
          rems2.erase({b,k});
          h-=b;
          continue;
        }
        auto it2=prev(rems2.end());
        if(it2->first==h){
          I k=it2->second;
          auto[a,b]=rcts[k];
          rems1.erase({a,k});
          rems2.erase({b,k});
          w-=a;
          continue;
        }
        vld=0;
        break;
      }
      if(vld){
        Lli h=upp2.first,w=tot/h;
        ress.insert({w,h});
      }
    }
    printf("%i\n",ress.size());
    for(auto[a,b]:ress)printf("%lli %lli\n",a,b);
  }
}