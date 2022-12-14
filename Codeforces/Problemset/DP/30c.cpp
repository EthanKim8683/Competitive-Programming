#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using Lli=long long int;
using B=bool;
const I N=1000;
const Lf MIN=-1e300;
tuple<I,I,I,Lf>tars[N];
pair<Lf,Lf>dp[N+1][N];
B rea(I i,I j){
  auto[t1,x1,y1,p1]=tars[i];
  auto[t2,x2,y2,p2]=tars[j];
  Lli dx=x1-x2,dy=y1-y2,dt=t1-t2;
  return dx*dx+dy*dy<=dt*dt;
}
void cmb(pair<Lf,Lf>&a,pair<Lf,Lf>b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y,t;Lf p;cin>>x>>y>>t>>p;
    tars[i]={t,x,y,p};
  }
  sort(tars,tars+n);
  for(I i=0;i<n;i++){
    auto[t,x,y,p]=tars[i];
    cmb(dp[i+1][i],{p,p});
    for(I j=0;j<i;j++){
      auto[e,c]=dp[i][j];
      cmb(dp[i+1][j],dp[i][j]);
      if(rea(i,j))cmb(dp[i+1][i],{e*(1-p)+(e+c)*p+(1-e)*p,c+p});
    }
  }
  printf("%.10Lf\n",max_element(dp[n],dp[n]+n)->first);
}