#include<bits/stdc++.h>

using namespace std;

using I=int;
using Hi=short;
using S=string;
using B=bool;
using C=char;

const I N=3000;
const Hi MAX=N;

C chrs[]="aeiou";
B typs[N];
tuple<Hi,Hi,Hi,B>dp[N+1][N+1][2];

void cmb(tuple<Hi,Hi,Hi,B>&a,tuple<Hi,Hi,Hi,B>b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*2,tuple<Hi,Hi,Hi,B>{MAX,0,0,0});
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i<n;i++)typs[i]=!binary_search(chrs,chrs+5,s[i]);
  dp[0][0][0]={0,0,0,0};
  for(I i=0;i<n;i++){
    C a=i-1<0?-1:s[i-1],b=s[i];
    B t=i-1<0?0:typs[i-1]&&typs[i]&&a!=b;
    for(I j=0;j<=i;j++){
      if(typs[i]){
        if(!(j+1>=3&&t))cmb(dp[i+1][j+1][t],{get<0>(dp[i][j][0]),j,0,0});
        if(!(j+1>=3&&1))cmb(dp[i+1][j+1][1],{get<0>(dp[i][j][1]),j,1,0});
        cmb(dp[i+1][1][0],{get<0>(dp[i][j][0])+1,j,0,1});
        cmb(dp[i+1][1][0],{get<0>(dp[i][j][1])+1,j,1,1});
      }else{
        cmb(dp[i+1][0][0],{get<0>(dp[i][j][0]),j,0,0});
        cmb(dp[i+1][0][0],{get<0>(dp[i][j][1]),j,1,0});
      }
    }
  }
  tuple<Hi,Hi,Hi,B>cur={MAX,0,0,0};
  for(I i=0;i<=n;i++)for(I j=0;j<2;j++)cmb(cur,{get<0>(dp[n][i][j]),i,j,0});
  I j=get<1>(cur),k=get<2>(cur);
  S res="";
  for(I i=n;i>0;i--){
    auto[val,x,y,z]=dp[i][j][k];
    res=s[i-1]+res;
    if(z)res=" "+res;
    j=x,k=y;
  }
  printf("%s\n",res.c_str());
}