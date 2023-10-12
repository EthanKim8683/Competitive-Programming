#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I MAX=1e9;
tuple<I,I,I>mins[N];
vector<I>cpss[2];
vector<pair<I,I>>vals[2][N];
I pars[N];
I lows[N];
vector<I>tims;
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}
B chk(I x){
  I cnt=0;
  for(auto i:tims)cnt+=i>x;
  return cnt-1<=x;
}
I bin(){
  I l=0,r=tims.size();
  while(l<r){
    I m=l+(r-l)/2;
    chk(m)?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    fill_n(pars,n,-1);
    for(I i=0;i<2;i++)cpss[i].clear();
    for(I i=0;i<n;i++){
      I x,y,tim;cin>>x>>y>>tim;
      mins[i]={x,y,tim};
      cpss[0].push_back(x);
      cpss[1].push_back(y);
    }
    for(I i=0;i<2;i++){
      sort(cpss[i].begin(),cpss[i].end());
      cpss[i].erase(unique(cpss[i].begin(),cpss[i].end()),cpss[i].end());
    }
    for(I i=0;i<2;i++)for(I j=0;j<cpss[i].size();j++)vals[i][j].clear();
    for(I i=0;i<n;i++){
      auto[x,y,tim]=mins[i];
      vals[0][lower_bound(cpss[0].begin(),cpss[0].end(),x)-cpss[0].begin()].push_back({y,i});
      vals[1][lower_bound(cpss[1].begin(),cpss[1].end(),y)-cpss[1].begin()].push_back({x,i});
    }
    for(I i=0;i<cpss[0].size();i++){
      sort(vals[0][i].begin(),vals[0][i].end());
      for(I j=0;j+1<vals[0][i].size();j++){
        auto[y1,k1]=vals[0][i][j];auto[y2,k2]=vals[0][i][j+1];
        if(abs(y1-y2)<=k)uni(k1,k2);
      }
    }
    for(I i=0;i<cpss[1].size();i++){
      sort(vals[1][i].begin(),vals[1][i].end());
      for(I j=0;j+1<vals[1][i].size();j++){
        auto[x1,k1]=vals[1][i][j];auto[x2,k2]=vals[1][i][j+1];
        if(abs(x1-x2)<=k)uni(k1,k2);
      }
    }
    fill_n(lows,n,MAX);
    for(I i=0;i<n;i++){
      I j=fnd(i);auto[x,y,tim]=mins[i];
      lows[j]=min(lows[j],tim);
    }
    tims.clear();
    for(I i=0;i<n;i++)if(i==fnd(i))tims.push_back(lows[i]);
    printf("%i\n",bin());
  }
}