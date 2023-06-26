#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100;
const I T=20;
const I D=2000;
I inds[N];
tuple<I,I,I>itms[N];
pair<I,I>dp[N+1][D+2];
vector<I>ress;
B cmp(I a,I b){
  return itms[a]<itms[b];
}
void cmb(pair<I,I>&a,pair<I,I>b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I t,d,p;cin>>t>>d>>p;
    itms[i]={d,t,p};
  }
  iota(inds,inds+n,0);
  sort(inds,inds+n,cmp);
  for(I i=0;i<n;i++)for(I j=0;j<=D+1;j++){
    auto[d,t,p]=itms[inds[i]];
    if(j+t<d)cmb(dp[i+1][min(j+t,D+1)],{dp[i][j].first+p,j});
    cmb(dp[i+1][j],{dp[i][j].first,j});
  }
  I j=max_element(dp[n],dp[n]+D+2)-dp[n];
  printf("%i\n",dp[n][j].first);
  for(I i=n;i>0;i--){
    auto[tot,k]=dp[i][j];
    if(tot!=dp[i-1][k].first)ress.push_back(inds[i-1]);
    j=k;
  }
  reverse(ress.begin(),ress.end());
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
}