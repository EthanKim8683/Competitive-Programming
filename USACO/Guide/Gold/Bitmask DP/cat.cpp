#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
using B=bool;
const I N=15;
const I FND=64;
const Lf VEL=1e7;
const Lf MAX=1e300;
tuple<I,I,I>mics[N];
Lf dp[1<<N][N];
Lf pows[N+1];
I n;
Lf m;
Lf dis(pair<I,I>a,pair<I,I>b){
  auto[x1,y1]=a;auto[x2,y2]=b;
  Lf dx=x1-x2,dy=y1-y2;
  return sqrt(dx*dx+dy*dy);
}
B chk(Lf x){
  fill(&dp[0][0],&dp[0][0]+(1<<N)*N,MAX);
  pows[0]=x;
  for(I i=1;i<=n;i++)pows[i]=pows[i-1]*m;
  for(I i=0;i<n;i++){
    auto[x,y,s]=mics[i];
    Lf tim=dis({0,0},{x,y})/pows[0];
    if(tim<=s)dp[1<<i][i]=min(dp[1<<i][i],tim);
  }
  for(I i=1;i<(1<<n);i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++)if(~i>>k&1){
    auto[x1,y1,s1]=mics[j];auto[x2,y2,s2]=mics[k];
    Lf tim=dp[i][j]+dis({x1,y1},{x2,y2})/pows[__builtin_popcount(i)];
    if(tim<=s2)dp[i|1<<k][k]=min(dp[i|1<<k][k],tim);
  }
  return*min_element(dp[(1<<n)-1],dp[(1<<n)-1]+n)!=MAX;
}
Lf fnd(){
  Lf l=0,r=VEL;
  for(I i=0;i<FND;i++){
    Lf m=(l+r)/2;
    chk(m)?r=m:l=m;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    I x,y,s;cin>>x>>y>>s;
    mics[i]={x,y,s};
  }
  cin>>m;
  printf("%.16Lf\n",fnd());
}