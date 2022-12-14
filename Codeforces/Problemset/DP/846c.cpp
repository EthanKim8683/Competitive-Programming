#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5000;
const Lli MIN=-1e18;
I a_arr[N];
pair<Lli,I>dp1[N+1][2],dp2[N+1][2];
void cmb(pair<Lli,I>&a,pair<Lli,I>b){
  a=max(a,b);
}
void cmb(tuple<Lli,I,I,I>&a,tuple<Lli,I,I,I>b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp1[0][0],&dp1[0][0]+(N+1)*2,pair<Lli,I>{MIN,-1});
  fill(&dp2[0][0],&dp2[0][0]+(N+1)*2,pair<Lli,I>{MIN,-1});
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  dp1[0][0]={0,0};
  for(I i=0;i<n;i++){
    auto[val0,del0]=dp1[i][0];
    auto[val1,del1]=dp1[i][1];
    I a=a_arr[i];
    cmb(dp1[i+1][0],{val0+a,i+1});
    cmb(dp1[i+1][1],{val0-a,i});
    cmb(dp1[i+1][1],{val1-a,del1});
  }
  dp2[n][0]={0,n};
  for(I i=n;i>0;i--){
    auto[val0,del0]=dp2[i][0];
    auto[val1,del1]=dp2[i][1];
    I a=a_arr[i-1];
    cmb(dp2[i-1][0],{val0-a,i-1});
    cmb(dp2[i-1][1],{val0+a,i});
    cmb(dp2[i-1][1],{val1+a,del1});
  }
  tuple<Lli,I,I,I>res={MIN,-1,-1,-1};
  for(I i=0;i<=n;i++)for(I j=0;j<2;j++)for(I k=0;k<2;k++){
    auto[val1,del1]=dp1[i][j];
    auto[val2,del2]=dp2[i][k];
    cmb(res,{val1+val2,del1,i,del2});
  }
  auto[val,del0,del1,del2]=res;
  printf("%i %i %i\n",del0,del1,del2);
}