#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=50000;
set<tuple<I,I,I,I>>pnts;
vector<pair<I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y,z;cin>>x>>y>>z;
    pnts.insert({x,y,z,i});
  }
  for(auto it1=pnts.begin();it1!=pnts.end();){
    auto pnt1=*it1;
    auto it2=pnts.upper_bound(pnt1);
    auto pnt2=*it2;
    if(get<0>(pnt1)==get<0>(pnt2)&&get<1>(pnt1)==get<1>(pnt2)){
      ress.push_back({get<3>(pnt1),get<3>(pnt2)});
      pnts.erase(it1);
      pnts.erase(it2);
    }
    it1=pnts.upper_bound(pnt1);
  }
  for(auto it1=pnts.begin();it1!=pnts.end();){
    auto pnt1=*it1;
    auto it2=pnts.upper_bound(pnt1);
    auto pnt2=*it2;
    if(get<0>(pnt1)==get<0>(pnt2)){
      ress.push_back({get<3>(pnt1),get<3>(pnt2)});
      pnts.erase(it1);
      pnts.erase(it2);
    }
    it1=pnts.upper_bound(pnt1);
  }
  for(auto it1=pnts.begin();it1!=pnts.end();){
    auto pnt1=*it1;
    auto it2=pnts.upper_bound(pnt1);
    auto pnt2=*it2;
    if(1){
      ress.push_back({get<3>(pnt1),get<3>(pnt2)});
      pnts.erase(it1);
      pnts.erase(it2);
    }
    it1=pnts.upper_bound(pnt1);
  }
  for(auto[a,b]:ress)printf("%i %i\n",a+1,b+1);
}