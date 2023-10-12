#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=200;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
pair<I,I>pnts[N];
pair<I,I>edgs[N];
I angs[N];
I lens[N];
vector<tuple<I,I,Lli>>pres[N];
multiset<Lli>viss;
I diss[N];
I main(){
#ifndef ETHANKIM8683
  freopen("lightsout.in","r",stdin);
  freopen("lightsout.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  for(I i=0;i<n;i++){
    auto[x1,y1]=pnts[i];
    auto[x2,y2]=pnts[(i+1)%n];
    edgs[i]={x2-x1,y2-y1};
    lens[i]=abs(x2-x1)+abs(y2-y1);
  }
  for(I i=0;i<n;i++){
    I dis1=0,dis2=0;
    for(I j=0;j<i;j++)dis1+=lens[j];
    for(I j=i;j<n;j++)dis2+=lens[j];
    diss[i]=min(dis1,dis2);
  }
  for(I i=0;i<n;i++){
    auto[x1,y1]=edgs[(i-1+n)%n];
    auto[x2,y2]=edgs[i];
    angs[i]=x1*y2-y1*x2>0;
  }
  for(I i=1;i<n;i++){
    pres[i].push_back({0,i,angs[i]});
    for(I j=i;j<n;j++){
      I len=lens[j],k=(j+1)%n,ang=angs[k];
      auto[acc1,k1,hsh1]=pres[i].back();
      pres[i].push_back({acc1+len,k,(hsh1*BAS+len)%MOD});
      auto[acc2,k2,hsh2]=pres[i].back();
      pres[i].push_back({acc2,k,(hsh2*BAS+ang)%MOD});
    }
  }
  for(I i=0;i<n;i++)for(auto[acc,j,hsh]:pres[i])viss.insert(hsh);
  I res=0;
  for(I i=1;i<n;i++){
    for(auto[acc,j,hsh]:pres[i])viss.erase(viss.find(hsh));
    I l=0,r=pres[i].size()-1;
    while(l<r){
      I m=l+(r-l)/2;
      auto[acc,j,hsh]=pres[i][m];
      viss.find(hsh)==viss.end()?r=m:l=m+1;
    }
    for(auto[acc,j,hsh]:pres[i])viss.insert(hsh);
    auto[acc,j,hsh]=pres[i][l];
    res=max(res,acc+diss[j]-diss[i]);
  }
  printf("%i\n",res);
}