#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=2000;
C cels[N][N+1];
I ps1[N][N+1];
I ps2[N+1][N];
I ps3[N][N+1];
I ps4[N+1][N];
I ps5[N][N+1];
I ps6[N+1][N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps1[i][j+1]=cels[i][j]=='B';
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps2[i+1][j]=cels[i][j]=='B';
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps1[i][j+1]+=ps1[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps2[i+1][j]+=ps2[i][j];
  for(I i=0;i+k<=n;i++)for(I j=0;j<n;j++)ps3[i][j+1]=(ps2[n][j]-ps2[0][j])-(ps2[i+k][j]-ps2[i][j])==0;
  for(I i=0;i<n;i++)for(I j=0;j+k<=n;j++)ps4[i+1][j]=(ps1[i][n]-ps1[i][0])-(ps1[i][j+k]-ps1[i][j])==0;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps3[i][j+1]+=ps3[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps4[i+1][j]+=ps4[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps5[i][j+1]=ps2[n][j]-ps2[0][j]==0;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps6[i+1][j]=ps1[i][n]-ps1[i][0]==0;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps5[i][j+1]+=ps5[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)ps6[i+1][j]+=ps6[i][j];
  I res=0;
  for(I i=0;i+k<=n;i++)for(I j=0;j+k<=n;j++){
    I cur=0;
    cur+=ps3[i][j+k]-ps3[i][j];
    cur+=ps4[i+k][j]-ps4[i][j];
    cur+=(ps5[i][j]-ps5[i][0])+(ps5[i][n]-ps5[i][j+k]);
    cur+=(ps6[i][j]-ps6[0][j])+(ps6[n][j]-ps6[i+k][j]);
    res=max(res,cur);
  }
  printf("%i\n",res);
}