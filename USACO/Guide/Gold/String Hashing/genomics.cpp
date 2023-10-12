#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using Lli=long long int;
using B=bool;
const I N=500;
const I M=500;
const I MAX=1e9;
const Lli MOD=(1ll<<31)-1;
const Lli BAS=(1ll<<17)-1;
C spts[N][M+1];
C plns[N][M+1];
Lli pows[M+1];
Lli pres1[N][M+1],pres2[N][M+1];
set<I>viss;
I n,m;
B chk(I len){
  for(I i=0;i+len<=m;i++){
    viss.clear();
    for(I j=0;j<n;j++)viss.insert(((pres1[j][i+len]-pres1[j][i]*pows[len])%MOD+MOD)%MOD);
    B vld=1;
    for(I j=0;j<n;j++)vld&=viss.find(((pres2[j][i+len]-pres2[j][i]*pows[len])%MOD+MOD)%MOD)==viss.end();
    if(vld)return 1;
  }
  return 0;
}
I fnd(){
  I l=1,r=m;
  while(l<r){
    I t=l+(r-l)/2;
    chk(t)?r=t:l=t+1;
  }
  return l;
}
I main(){
#ifndef ETHANKIM8683
  freopen("cownomics.in","r",stdin);
  freopen("cownomics.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=M;i++)pows[i]=pows[i-1]*BAS%MOD;
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>spts[i];
  for(I i=0;i<n;i++)cin>>plns[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)pres1[i][j+1]=(pres1[i][j]*BAS+spts[i][j])%MOD;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)pres2[i][j+1]=(pres2[i][j]*BAS+plns[i][j])%MOD;
  printf("%i\n",fnd());
}