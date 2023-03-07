#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using Lf=long double;
const I N=1e6;
I a_arr[N];
vector<pair<Lli,Lli>>pnts;
vector<pair<Lli,Lli>>huls;
Lf ress[N];
Lli are(pair<Lli,Lli>a,pair<Lli,Lli>b,pair<Lli,Lli>c){
  return(b.first-a.first)*(c.second-a.second)-(b.second-a.second)*(c.first-a.first);
}
void mtc(){
  sort(pnts.begin(),pnts.end());
  pnts.erase(unique(pnts.begin(),pnts.end()),pnts.end());
  I n=pnts.size();
  if(n<3){huls=pnts;return;}
  for(I i=0;i<n;i++){
    while(huls.size()>=2&&are(huls.end()[-2],huls.end()[-1],pnts[i])<=0)huls.pop_back();
    huls.push_back(pnts[i]);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli cur=0;
  pnts.push_back({0,0});
  for(I i=0;i<n;i++){
    cur+=a_arr[i];
    pnts.push_back({i,cur});
    pnts.push_back({i+1,cur});
  }
  mtc();
  for(I i=0;i+1<huls.size();i++){
    auto[x1,y1]=huls[i];auto[x2,y2]=huls[i+1];
    Lf ave=(Lf)(y2-y1)/(x2-x1);
    for(I j=x1;j<x2;j++)ress[j]=ave;
  }
  for(I i=0;i<n;i++)printf("%.9Lf\n",ress[i]);
}