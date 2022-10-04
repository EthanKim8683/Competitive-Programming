#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1000;
const I M=1000;

I cels[N][M];
I ps1[N][M+1];
I ps2[M][N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>cels[i][j];
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)ps1[i][j+1]=cels[i][j];
    for(I j=0;j<m;j++)ps1[i][j+1]+=ps1[i][j];
  }
  for(I i=0;i<m;i++){
    for(I j=0;j<n;j++)ps2[i][j+1]=cels[j][i];
    for(I j=0;j<n;j++)ps2[i][j+1]+=ps2[i][j];
  }
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j])continue;
    res+=ps1[i][j]-ps1[i][0]>0;
    res+=ps1[i][m]-ps1[i][j+1]>0;
    res+=ps2[j][i]-ps2[j][0]>0;
    res+=ps2[j][n]-ps2[j][i+1]>0;
  }
  printf("%i\n",res);
}