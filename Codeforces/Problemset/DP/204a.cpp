#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const I L=19;

Lli dp[L][10][10][2];

pair<Lli,Lli>slv(S x){
  fill(&dp[0][0][0][0],&dp[0][0][0][0]+L*10*10*2,0);
  I l=x.size();
  I d=x[0]-'0';
  for(I i=1;i<=d;i++)
    dp[0][i][i][i==d]=1;
  for(I i=0;i+1<l;i++){
    I d=x[i+1]-'0';
    for(I j=0;j<=d;j++)for(I k=1;k<10;k++)for(I l=0;l<10;l++)
      dp[i+1][k][j][j==d]+=dp[i][k][l][1];
    for(I j=0;j<10;j++)for(I k=1;k<10;k++)for(I l=0;l<10;l++)
      dp[i+1][k][j][0]+=dp[i][k][l][0];
    for(I j=1;j<10;j++)
      dp[i+1][j][j][0]+=1;
  }
  Lli res=0,upp=0;
  for(I i=1;i<10;i++)res+=dp[l-1][i][i][0];
  for(I i=1;i<10;i++)upp+=dp[l-1][i][i][1];
  return{res,upp};
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S l,r;cin>>l>>r;
  auto[r1,r2]=slv(r);
  auto[l1,l2]=slv(l);
  printf("%lli\n",r1+r2-l1);
}