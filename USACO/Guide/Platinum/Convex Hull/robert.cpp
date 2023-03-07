#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I C=100000;
vector<pair<I,I>>pnts;
vector<pair<I,I>>huls;
Lf res=0;
I are(pair<I,I>a,pair<I,I>b,pair<I,I>c){
  return(b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first);
}
void slv(){
  sort(pnts.begin(),pnts.end());
  pnts.erase(unique(pnts.begin(),pnts.end()),pnts.end());
  I n=pnts.size();
  if(n<3){huls=pnts;return;}
  for(I i=0;i<n;i++){
    while(huls.size()>=2&&are(huls.end()[-2],huls.end()[-1],pnts[i])<=0)huls.pop_back();
    huls.push_back(pnts[i]);
  }
  I low=huls.size();
  for(I i=n-2;i>=0;i--){
    while(huls.size()>low&&are(huls.end()[-2],huls.end()[-1],pnts[i])<=0)huls.pop_back();
    huls.push_back(pnts[i]);
  }
  huls.pop_back();
}
Lf dis(pair<I,I>a,pair<I,I>b){
  Lf dx=a.first-b.first,dy=a.second-b.second;
  return sqrt(dx*dx+dy*dy);
}
void shm(){
  I n=huls.size();
  if(n==2)res=max(res,dis(huls[0],huls[1]));
  if(n<=2)return;
  I j=1;
  for(I i=0;i<n;i++){
    while(are(huls[i],huls[(i+1)%n],huls[(j+1)%n])>are(huls[i],huls[(i+1)%n],huls[j]))j=(j+1)%n;
    res=max(res,dis(huls[i],huls[j]));
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I c;cin>>c;
  for(I i=0;i<c;i++){
    I x,y;cin>>x>>y;
    pnts.push_back({x,y});
  }
  slv();
  shm();
  printf("%.8Lf\n",res);
}