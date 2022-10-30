#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;
using Lli=long long int;

const I N=1000;
const I M=1000;
const Lli MIN=-1e18;

I di[]{1,0},dj[]{0,1};
I cels[N][M];
Lli dp1[N][M],dp2[N][M],dp3[N][M],dp4[N][M];
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp1[0][0],&dp1[0][0]+N*M,MIN);
  fill(&dp2[0][0],&dp2[0][0]+N*M,MIN);
  fill(&dp3[0][0],&dp3[0][0]+N*M,MIN);
  fill(&dp4[0][0],&dp4[0][0]+N*M,MIN);
  cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>cels[i][j];
  dp1[0][0]=cels[0][0];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(bnd(i+1,j))dp1[i+1][j]=max(dp1[i+1][j],dp1[i][j]+cels[i+1][j]);
    if(bnd(i,j+1))dp1[i][j+1]=max(dp1[i][j+1],dp1[i][j]+cels[i][j+1]);
  }
  dp2[n-1][0]=cels[n-1][0];
  for(I i=n-1;i>=0;i--)for(I j=0;j<m;j++){
    if(bnd(i-1,j))dp2[i-1][j]=max(dp2[i-1][j],dp2[i][j]+cels[i-1][j]);
    if(bnd(i,j+1))dp2[i][j+1]=max(dp2[i][j+1],dp2[i][j]+cels[i][j+1]);
  }
  dp3[n-1][m-1]=cels[n-1][m-1];
  for(I i=n-1;i>=0;i--)for(I j=m-1;j>=0;j--){
    if(bnd(i-1,j))dp3[i-1][j]=max(dp3[i-1][j],dp3[i][j]+cels[i-1][j]);
    if(bnd(i,j-1))dp3[i][j-1]=max(dp3[i][j-1],dp3[i][j]+cels[i][j-1]);
  }
  dp4[0][m-1]=cels[0][m-1];
  for(I i=0;i<n;i++)for(I j=m-1;j>=0;j--){
    if(bnd(i+1,j))dp4[i+1][j]=max(dp4[i+1][j],dp4[i][j]+cels[i+1][j]);
    if(bnd(i,j-1))dp4[i][j-1]=max(dp4[i][j-1],dp4[i][j]+cels[i][j-1]);
  }
  Lli res=MIN;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    for(I k=0;k<2;k++)for(I l=0;l<2;l++){
      for(I o=0;o<2;o++)for(I p=0;p<2;p++){
        I a=i-di[k],b=j-dj[k];
        I c=i+di[l],d=j-dj[l];
        I e=i+di[o],f=j+dj[o];
        I g=i-di[p],h=j+dj[p];
        if(!bnd(a,b))continue;
        if(!bnd(c,d))continue;
        if(!bnd(e,f))continue;
        if(!bnd(g,h))continue;
        if(a==c&&b==d)continue;
        if(a==e&&b==f)continue;
        if(a==g&&b==h)continue;
        if(c==e&&d==f)continue;
        if(c==g&&d==h)continue;
        if(e==g&&f==h)continue;
        res=max(res,dp1[a][b]+dp2[c][d]+dp3[e][f]+dp4[g][h]);
      }
    }
  }
  printf("%lli\n",res);
}