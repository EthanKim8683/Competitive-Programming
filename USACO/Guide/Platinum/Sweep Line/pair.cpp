#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=100000;
const Lf MAX=1e99;
pair<Lf,Lf>pnts[N];
map<Lf,I>curs;
Lf dis(I a,I b){
  auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];
  Lf dx=x1-x2,dy=y1-y2;
  return sqrt(dx*dx+dy*dy);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  while(1){
    I n;cin>>n;
    if(n==0)break;
    for(I i=0;i<n;i++){
      Lf x,y;cin>>x>>y;
      pnts[i]={x,y};
    }
    tuple<Lf,I,I>res={MAX,-1,-1};
    sort(pnts,pnts+n);
    curs.clear();
    for(I i=0,j=0;i<n;i++){
      auto[x1,y1]=pnts[i];
      while(j<n){
        auto[x2,y2]=pnts[j];
        if(x1-x2<get<0>(res))break;
        if(curs.count(y2))curs.erase(y2);
        j++;
      }
      auto low=curs.lower_bound(y1-get<0>(res));
      auto upp=curs.upper_bound(y1+get<0>(res));
      for(auto it=low;it!=upp;it++){
        I j=it->second;
        res=min(res,{dis(i,j),j,i});
      }
      curs[y1]=i;
    }
    auto[dis,a,b]=res;
    auto[x1,y1]=pnts[a];auto[x2,y2]=pnts[b];
    printf("%Lf %Lf %Lf %Lf\n",x1,y1,x2,y2);
  }
}