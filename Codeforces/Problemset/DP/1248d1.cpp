#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=500;
const I MIN=-1e9;
tuple<I,I,I>dp[N+1][N+1][4];
void cmb(tuple<I,I,I>&a,tuple<I,I,I>b){
  a=max(a,b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+(N+1)*(N+1)*4,tuple<I,I,I>{MIN,0,0});
  I n;cin>>n;
  S s;cin>>s;
  I net=0;
  for(auto c:s)net+=(c=='(')-(c==')');
  if(net!=0)printf("0\n1 1"),exit(0);
  for(I i=0;i<=n;i++)dp[0][i][0]={0,0,0};
  for(I j=0;j<=n;j++)for(I k=0;k<=n;k++){
    if(s[j]=='('){
      for(I l=0;l<4;l++)if(k+1<=n)cmb(dp[j+1][k+1][l],dp[j][k][l]);
      if(k-1>=0)cmb(dp[j+1][k-1][1],{get<0>(dp[j][k][0])+(k-1==0),j,-1});
      if(k-1>=0)cmb(dp[j+1][k-1][3],{get<0>(dp[j][k][2])+(k-1==0),get<1>(dp[j][k][2]),j});
    }
    if(s[j]==')'){
      for(I l=0;l<4;l++)if(k-1>=0)cmb(dp[j+1][k-1][l],{get<0>(dp[j][k][l])+(k-1==0),get<1>(dp[j][k][l]),get<2>(dp[j][k][l])});
      if(k+1<=n)cmb(dp[j+1][k+1][2],{get<0>(dp[j][k][0]),j,-1});
      if(k+1<=n)cmb(dp[j+1][k+1][3],{get<0>(dp[j][k][1]),get<1>(dp[j][k][1]),j});
    }
  }
  tuple<I,I,I>res={MIN,0,0};
  for(I i=0;i<=n;i++)res=max(res,max(dp[n][i][0],dp[n][i][3]));
  auto[cnt,i,j]=res;
  printf("%i\n",cnt);
  printf("%i %i\n",i+1,j+1);
}