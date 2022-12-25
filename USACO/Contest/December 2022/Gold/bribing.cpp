#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2000;
const I A=2000;
const I B=2000;
const I MIN=-1e9;
tuple<I,I,I>frds[N];
I dp1[N+1][B+1];
I dp2[N+1][A+1];
void cmb(I&a,I b){
  a=max(a,b);
}
I main(){
  fill(&dp1[0][0],&dp1[0][0]+(N+1)*(B+1),MIN);
  fill(&dp2[0][0],&dp2[0][0]+(N+1)*(A+1),MIN);
  cin.tie(0)->sync_with_stdio(0);
  I n,a,b;cin>>n>>a>>b;
  for(I i=0;i<n;i++){
    I p,c,x;cin>>p>>c>>x;
    frds[i]={x,p,c};
  }
  // a-0  -0  -0  -0  -(c-d)-c-c-c-c>=0
  // b-c*x-c*x-c*x-c*x-d*x  -0-0-0-0>=0
  sort(frds,frds+n);
  fill_n(dp1[0],b+1,0);
  for(I i=0;i<n;i++)for(I j=0;j<=b;j++){
    auto[x,p,c]=frds[i];
    cmb(dp1[i+1][j],dp1[i][j]);
    if(j-c*x>=0)cmb(dp1[i+1][j-c*x],dp1[i][j]+p);
  }
  fill_n(dp2[n],a+1,0);
  for(I i=n;i>0;i--)for(I j=0;j<=a;j++){
    auto[x,p,c]=frds[i-1];
    cmb(dp2[i-1][j],dp2[i][j]);
    if(j+c<=a)cmb(dp2[i-1][j+c],dp2[i][j]+p);
  }
  I res=MIN;
  res=max(res,*max_element(dp1[n],dp1[n]+b+1));
  res=max(res,*max_element(dp2[0],dp2[0]+a+1));
  for(I i=0;i<n;i++)for(I j=0;j<=b;j++){
    auto[x,p,c]=frds[i];
    res=max(res,dp1[i][j]+dp2[i+1][a-(c-j/x)]+p);
  }
  printf("%i\n",res);
}