#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=25;
const I M=25;

C cels[N][M+1];
I ps[N+1][M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i+1][j+1]=cels[i][j]=='1';
  for(I i=1;i<=n;i++)for(I j=1;j<=m;j++)ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)for(I k=1;i+k<=n;k++)for(I l=1;j+l<=m;l++){
    if(ps[i+k][j+l]-ps[i+k][j]-ps[i][j+l]+ps[i][j])continue;
    res=max(res,k+l);
  }
  printf("%i\n",2*res);
}