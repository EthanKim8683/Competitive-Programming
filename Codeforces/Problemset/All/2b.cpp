#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=1000;
const I MAX=1e9;
const I MIN=-1e9;
I mats[N][N];
I twos[N][N],fivs[N][N];
tuple<I,I,I>dp1[N][N],dp2[N][N];
C ress[2*N-2+1];
void cmb1(tuple<I,I,I>&a,tuple<I,I,I>b){
  if(get<0>(b)<get<0>(a))a=b;
}
void cmb2(tuple<I,I,I>&a,tuple<I,I,I>b){
  if(get<1>(b)<get<1>(a))a=b;
}
I cst(tuple<I,I,I>x){
  return min(get<0>(x),get<1>(x));
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp1[0][0],&dp1[0][0]+N*N,tuple<I,I,I>{MAX,MAX,-1});
  fill(&dp2[0][0],&dp2[0][0]+N*N,tuple<I,I,I>{MAX,MAX,-1});
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>mats[i][j];
  I x=-1,y=-1;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    I val=mats[i][j];
    if(val==0){x=i,y=j;continue;}
    twos[i][j]=__builtin_ctz(val);
    while(val%5==0)fivs[i][j]++,val/=5;
  }
  dp1[0][0]=dp2[0][0]={twos[0][0],fivs[0][0],-1};
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    auto[two1,fiv1,mov1]=dp1[i][j];
    auto[two2,fiv2,mov2]=dp2[i][j];
    if(i+1<n){
      I two3=twos[i+1][j],fiv3=fivs[i+1][j];
      cmb1(dp1[i+1][j],{two1+two3,fiv1+fiv3,0});
      cmb2(dp2[i+1][j],{two2+two3,fiv2+fiv3,0});
    }
    if(j+1<n){
      I two3=twos[i][j+1],fiv3=fivs[i][j+1];
      cmb1(dp1[i][j+1],{two1+two3,fiv1+fiv3,1});
      cmb2(dp2[i][j+1],{two2+two3,fiv2+fiv3,1});
    }
  }
  I res,res1=cst(dp1[n-1][n-1]),res2=cst(dp2[n-1][n-1]);
  if(res1<res2){
    res=res1;
    I i=n-1,j=n-1;
    for(I k=2*n-2-1;k>=0;k--){
      auto[two,fiv,mov]=dp1[i][j];
      ress[k]="DR"[mov];
      i-=mov==0,j-=mov==1;
    }
  }else{
    res=res2;
    I i=n-1,j=n-1;
    for(I k=2*n-2-1;k>=0;k--){
      auto[two,fiv,mov]=dp2[i][j];
      ress[k]="DR"[mov];
      i-=mov==0,j-=mov==1;
    }
  }
  if(x!=-1&&res>1){
    res=1;
    I i=0,j=0,k=0;
    while(i<x)i++,ress[k++]='D';
    while(j<y)j++,ress[k++]='R';
    while(i<n-1)i++,ress[k++]='D';
    while(j<n-1)j++,ress[k++]='R';
  }
  printf("%i\n",res);
  printf("%s\n",ress);
}