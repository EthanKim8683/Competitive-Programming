#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using Lli=long long int;

const Lli MAX=1e18;

Lli dp[10][10][10];
Lli ress[10][10];

void cmb(Lli&a,Lli b){
  a=min(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0],&dp[0][0][0]+10*10*10,MAX);
  for(I i=0;i<10;i++)for(I j=0;j<10;j++){
    dp[i][j][i]=1;
    dp[i][j][j]=1;
    for(I k=0;k<10;k++)for(I l=0;l<10;l++)for(I m=0;m<10;m++)
      cmb(dp[i][j][(l+m)%10],dp[i][j][l]+dp[i][j][m]);
  }
  S s;cin>>s;
  I n=s.size();
  for(I i=0;i+1<n;i++)for(I j=0;j<10;j++)for(I k=0;k<10;k++){
    Lli d=dp[j][k][(s[i+1]-s[i]+10)%10];
    if(d==MAX)ress[j][k]=-1;
    if(ress[j][k]==-1)continue;
    ress[j][k]+=d-1;
  }
  for(I i=0;i<10;i++){
    for(I j=0;j<10;j++)printf("%lli ",ress[i][j]);
    printf("\n");
  }
}