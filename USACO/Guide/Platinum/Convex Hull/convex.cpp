#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=10000;
pair<Lli,Lli>pnts[N];
pair<Lli,Lli>bas;
vector<pair<Lli,Lli>>stks;
pair<Lli,Lli>sub(pair<Lli,Lli>a,pair<Lli,Lli>b){
  return{a.first-b.first,a.second-b.second};
}
Lli crs(pair<Lli,Lli>a,pair<Lli,Lli>b){
  return a.first*b.second-a.second*b.first;
}
Lli crs(pair<Lli,Lli>a,pair<Lli,Lli>b,pair<Lli,Lli>c){
  return crs(sub(a,c),sub(b,c));
}
Lli dsq(pair<Lli,Lli>a,pair<Lli,Lli>b){
  Lli dx=a.first-b.first,dy=a.second-b.second;
  return dx*dx+dy*dy;
}
B cmp(pair<Lli,Lli>a,pair<Lli,Lli>b){
  Lli res=crs(a,b,bas);
  return res!=0?res>0:dsq(a,bas)<dsq(b,bas);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  while(1){
    I n;cin>>n;
    if(n==0)break;
    for(I i=0;i<n;i++){
      I x,y;cin>>x>>y;
      pnts[i]={x,y};
    }
    swap(*min_element(pnts,pnts+n),pnts[0]);
    bas=pnts[0];
    sort(pnts+1,pnts+n,cmp);
    stks.clear(),stks.push_back(bas);
    for(I i=1;i<n;i++){
      if(pnts[i]==bas)continue;
      while(stks.size()>=2&&crs(stks.end()[-2],stks.end()[-1],pnts[i])<=0)stks.pop_back();
      stks.push_back(pnts[i]);
    }
    printf("%i\n",stks.size());
    for(auto[x,y]:stks)printf("%lli %lli\n",x,y);
  }
}