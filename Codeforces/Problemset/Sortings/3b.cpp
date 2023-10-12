#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
vector<pair<I,I>>kays,cats;
Lli pres1[N+1],pres2[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,v;cin>>n>>v;
  for(I i=0;i<n;i++){
    I t,p;cin>>t>>p;
    if(t==1)kays.push_back({-p,i});
    if(t==2)cats.push_back({-p,i});
  }
  sort(kays.begin(),kays.end());
  sort(cats.begin(),cats.end());
  for(I i=0;i<kays.size();i++)pres1[i+1]=pres1[i]-kays[i].first;
  for(I i=0;i<cats.size();i++)pres2[i+1]=pres2[i]-cats[i].first;
  pair<Lli,I>res={0,0};
  for(I i=0;i<=min((I)kays.size(),v);i++)res=max(res,{pres1[i]+pres2[min((v-i)/2,(I)cats.size())],i});
  auto[cap,cnt1]=res;I cnt2=min((v-cnt1)/2,(I)cats.size());
  printf("%i\n",cap);
  for(I i=0;i<cnt1;i++)printf("%i ",kays[i].second+1);
  for(I i=0;i<cnt2;i++)printf("%i ",cats[i].second+1);
}