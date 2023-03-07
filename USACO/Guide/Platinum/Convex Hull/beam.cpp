#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
const Lli MIN=-MAX;
const Lli FAC=1e5;
I f_arr[N];
vector<pair<Lli,Lli>>pnts;
vector<pair<Lli,Lli>>huls;
Lli are(pair<Lli,Lli>a,pair<Lli,Lli>b,pair<Lli,Lli>c){
  return(b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first);
}
void mtc(){
  if(pnts.size()<3){huls=pnts;return;}
  for(I i=0;i<pnts.size();i++){
    while(huls.size()>=2&&are(huls.end()[-2],huls.end()[-1],pnts[i])>0)huls.pop_back();
    huls.push_back(pnts[i]);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("balance.in","r",stdin);
  freopen("balance.out","w",stdout);
#endif
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>f_arr[i];
  pnts.push_back({-1,0});
  for(I i=0;i<n;i++)pnts.push_back({i,f_arr[i]});
  pnts.push_back({n,0});
  mtc();
  for(I i=0;i<n;i++){
    auto it1=prev(lower_bound(huls.begin(),huls.end(),pair<Lli,Lli>{i,MIN}));
    auto it2=upper_bound(huls.begin(),huls.end(),pair<Lli,Lli>{i,MAX});
    Lli dis1=i-it1->first,dis2=it2->first-i,val1=it1->second,val2=it2->second;
    printf("%lli\n",max(FAC*f_arr[i],FAC*(val1*dis2+val2*dis1)/(dis1+dis2)));
  }
}