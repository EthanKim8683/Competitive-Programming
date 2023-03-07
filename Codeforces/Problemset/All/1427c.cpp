#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=100000;
const I MIN=-1e9;
tuple<I,I,I>cels[N+1];
I dp[N+1];
void cmb(I&a,I b){
  a=max(a,b);
}
B rea(tuple<I,I,I>a,tuple<I,I,I>b){
  auto[at,ax,ay]=a;auto[bt,bx,by]=b;
  return abs(ax-bx)+abs(ay-by)<=abs(at-bt);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I r,n;cin>>r>>n;
  for(I i=0;i<n;i++){
    I t,x,y;cin>>t>>x>>y;
    cels[i+1]={t,x,y};
  }
  cels[0]={0,1,1};
  fill_n(dp,n,MIN);
  dp[0]=0;
  I pre=MIN;
  for(I i=1,j=0;i<n+1;i++){
    auto[t,x,y]=cels[i];
    while(j<i&&abs(t-get<0>(cels[j]))>=2*(r-1))cmb(pre,dp[j++]);
    for(I k=j;k<i;k++)if(rea(cels[i],cels[k]))cmb(dp[i],dp[k]+1);
    cmb(dp[i],pre+1);
  }
  printf("%i\n",*max_element(dp,dp+n+1));
}