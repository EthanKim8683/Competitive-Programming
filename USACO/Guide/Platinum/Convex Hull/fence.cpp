#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const Lf MAX=1e99;
vector<pair<I,I>>pnts;
vector<pair<I,I>>huls;
I are1(pair<I,I>a,pair<I,I>b,pair<I,I>c){
  return(b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first);
}
I are2(pair<I,I>a,pair<I,I>b,pair<I,I>c){
  return(b.first-a.first)*(c.first-a.first)+(b.second-a.second)*(c.second-a.second);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  while(1){
    I n=0;cin>>n;
    if(n==0)break;
    pnts.clear(),huls.clear();
    for(I i=0;i<n;i++){
      I x,y;cin>>x>>y;
      pnts.push_back({x,y});
    }
    sort(pnts.begin(),pnts.end());
    pnts.erase(unique(pnts.begin(),pnts.end()),pnts.end());
    n=pnts.size();
    for(I i=0;i<n;i++){
      while(huls.size()>=2&&are1(huls.end()[-2],huls.end()[-1],pnts[i])<=0)huls.pop_back();
      huls.push_back(pnts[i]);
    }
    I low=huls.size();
    for(I i=n-2;i>=0;i--){
      while(huls.size()>low&&are1(huls.end()[-2],huls.end()[-1],pnts[i])<=0)huls.pop_back();
      huls.push_back(pnts[i]);
    }
    huls.pop_back();
    n=huls.size();
    Lf res=MAX;
    I j=1,k=-1,l=-1;
    for(I i=0;i<n;i++){
      while(are1(huls[i],huls[(i+1)%n],huls[(j+1)%n])>are1(huls[i],huls[(i+1)%n],huls[j]))j=(j+1)%n;
      if(k==-1)k=i;
      if(l==-1)l=j;
      while(are2(huls[i],huls[(i+1)%n],huls[(k+1)%n])>are2(huls[i],huls[(i+1)%n],huls[k]))k=(k+1)%n;
      while(are2(huls[i],huls[(i+1)%n],huls[(l+1)%n])<are2(huls[i],huls[(i+1)%n],huls[l]))l=(l+1)%n;
      Lf c=huls[i].first-huls[(i+1)%n].first,s=huls[i].second-huls[(i+1)%n].second,h=sqrt(c*c+s*s);
      Lf x=(huls[j].first-huls[i].first)*s-(huls[j].second-huls[i].second)*c;
      Lf y=(huls[k].first-huls[i].first)*c+(huls[k].second-huls[i].second)*s;
      Lf z=(huls[l].first-huls[i].first)*c+(huls[l].second-huls[i].second)*s;
      res=min(res,2*(abs(x)+abs(y-z))/h);
    }
    printf("%Lf\n",res);
  }
}