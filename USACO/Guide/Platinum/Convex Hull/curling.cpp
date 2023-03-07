#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
vector<pair<Lli,Lli>>pnts1,pnts2;
I n;
Lli are(pair<Lli,Lli>a,pair<Lli,Lli>b,pair<Lli,Lli>c){
  return(b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first);
}
I mtn(vector<pair<Lli,Lli>>pnts1,vector<pair<Lli,Lli>>pnts2){
  vector<pair<Lli,Lli>>lows,upps;
  for(I i=0;i<n;i++){
    while(lows.size()>=2&&are(lows.end()[-2],lows.end()[-1],pnts1[i])<=0)lows.pop_back();
    lows.push_back(pnts1[i]);
  }
  for(I i=0;i<n;i++){
    while(upps.size()>=2&&are(upps.end()[-2],upps.end()[-1],pnts1[i])>=0)upps.pop_back();
    upps.push_back(pnts1[i]);
  }
  I res=0,i=0,j=0;
  for(auto pnt:pnts2){
    if(pnt.first<pnts1.front().first)continue;
    if(pnt.first>pnts1.back().first)continue;
    while(i+1<lows.size()&&pnt.first>lows[i+1].first)i++;
    while(j+1<upps.size()&&pnt.first>upps[j+1].first)j++;
    B vld=1;
    vld&=(lows[i].first==lows[i+1].first?min(lows[i].second,lows[i+1].second)<=pnt.second:are(lows[i],lows[i+1],pnt)>=0);
    vld&=(upps[j].first==upps[j+1].first?max(upps[j].second,upps[j+1].second)>=pnt.second:are(upps[j],upps[j+1],pnt)<=0);
    res+=vld;
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
#ifndef ETHANKIM8683
  freopen("curling.in","r",stdin);
  freopen("curling.out","w",stdout);
#endif
  cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts1.push_back({x,y});
  }
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts2.push_back({x,y});
  }
  sort(pnts1.begin(),pnts1.end()),sort(pnts2.begin(),pnts2.end());
  printf("%i %i\n",mtn(pnts1,pnts2),mtn(pnts2,pnts1));
}