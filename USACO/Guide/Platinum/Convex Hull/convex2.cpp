#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
vector<pair<I,I>>pnts;
vector<pair<I,I>>stks;
Lli are(pair<I,I>a,pair<I,I>b,pair<I,I>c){
  return(Lli)(a.first-c.first)*(b.second-c.second)-(Lli)(a.second-c.second)*(b.first-c.first);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  while(1){
    I n;cin>>n;
    if(n==0)break;
    pnts.clear();
    for(I i=0;i<n;i++){
      I x,y;cin>>x>>y;
      pnts.push_back({x,y});
    }
    sort(pnts.begin(),pnts.end());
    pnts.erase(unique(pnts.begin(),pnts.end()),pnts.end());
    if(pnts.size()<3){
      printf("%i\n",pnts.size());
      for(auto[x,y]:pnts)printf("%i %i\n",x,y);
      continue;
    }
    stks.clear();
    for(I i=0;i<pnts.size();i++){
      while(stks.size()>=2&&are(stks.end()[-2],stks.end()[-1],pnts[i])<=0)stks.pop_back();
      stks.push_back(pnts[i]);
    }
    I low=stks.size();
    for(I i=pnts.size()-2;i>=0;i--){
      while(stks.size()>low&&are(stks.end()[-2],stks.end()[-1],pnts[i])<=0)stks.pop_back();
      stks.push_back(pnts[i]);
    }
    stks.pop_back();
    printf("%i\n",stks.size());
    for(auto[x,y]:stks)printf("%i %i\n",x,y);
  }
}