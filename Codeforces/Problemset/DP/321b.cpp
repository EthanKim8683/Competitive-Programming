#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=100;
const I M=100;
const I MIN=-1e9;
vector<I>atks,defs;
I foxs[M];
I dp1[N+1][N+1][M+1],dp2[N+1][N+1][M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp1[0][0][0],&dp1[0][0][0]+(N+1)*(N+1)*(M+1),MIN);
  fill(&dp2[0][0][0],&dp2[0][0][0]+(N+1)*(N+1)*(M+1),MIN);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    S pos;I str;cin>>pos>>str;
    if(pos=="ATK")atks.push_back(str);
    if(pos=="DEF")defs.push_back(str);
  }
  for(I i=0;i<m;i++)cin>>foxs[i];
  sort(atks.begin(),atks.end());
  sort(defs.begin(),defs.end());
  sort(foxs,foxs+m);
  I x=atks.size(),y=defs.size();
  dp1[0][0][0]=dp2[0][0][0]=0;
  for(I i=0;i<=x;i++)for(I j=0;j<=y;j++)for(I k=0;k<=m;k++){
    if(i<x&&k<m){
      I siz1=atks[i],siz2=foxs[k];
      if(siz2>=siz1)dp1[i+1][j][k+1]=max(dp1[i+1][j][k+1],dp1[i][j][k]+siz2-siz1);
      if(siz2>=siz1)dp2[i+1][j][k+1]=max(dp2[i+1][j][k+1],dp2[i][j][k]+siz2-siz1);
    }
    if(j<y&&k<m){
      I siz1=defs[j],siz2=foxs[k];
      if(siz2>siz1)dp1[i][j+1][k+1]=max(dp1[i][j+1][k+1],dp1[i][j][k]);
      if(siz2>siz1)dp2[i][j+1][k+1]=max(dp2[i][j+1][k+1],dp2[i][j][k]);
    }
    if(i<x)dp1[i+1][j][k]=max(dp1[i+1][j][k],dp1[i][j][k]);
    if(j<y)dp1[i][j+1][k]=max(dp1[i][j+1][k],dp1[i][j][k]);
    if(k<m)dp1[i][j][k+1]=max(dp1[i][j][k+1],dp1[i][j][k]);
    if(k<m)dp2[i][j][k+1]=max(dp2[i][j][k+1],dp2[i][j][k]+foxs[k]);
  }
  printf("%i\n",max(dp1[x][y][m],dp2[x][y][m]));
}