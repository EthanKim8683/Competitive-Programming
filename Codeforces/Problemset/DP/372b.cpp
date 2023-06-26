#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=40;
const I M=40;
C grds[N][M+1];
I ps[N+1][M+1];
I dp[N+1][N+1][M+1][M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  for(I i=0;i<n;i++)cin>>grds[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i+1][j+1]=grds[i][j]-'0';
  for(I i=1;i<=n;i++)for(I j=1;j<=m;j++)ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
  for(I i=0;i<=n;i++)for(I j=i+1;j<=n;j++)for(I k=0;k<=m;k++)for(I l=k+1;l<=m;l++)dp[i][j][k][l]=ps[j][l]-ps[j][k]-ps[i][l]+ps[i][k]==0;
  for(I i=1;i<=n;i++)for(I j=1;j<=m;j++)for(I k=0;k+i<=n;k++)for(I l=0;l+j<=m;l++)dp[k][k+i][l][l+j]+=dp[k+1][k+i][l][l+j]+dp[k][k+i-1][l][l+j]+dp[k][k+i][l+1][l+j]+dp[k][k+i][l][l+j-1]-dp[k+1][k+i-1][l][l+j]-dp[k][k+i][l+1][l+j-1]-dp[k+1][k+i][l+1][l+j]-dp[k+1][k+i][l][l+j-1]-dp[k][k+i-1][l+1][l+j]-dp[k][k+i-1][l][l+j-1]+dp[k+1][k+i-1][l+1][l+j]+dp[k+1][k+i-1][l][l+j-1]+dp[k+1][k+i][l+1][l+j-1]+dp[k][k+i-1][l+1][l+j-1]-dp[k+1][k+i-1][l+1][l+j-1];
  while(q--){
    I a,b,c,d;cin>>a>>b>>c>>d,a--,b--,c--,d--;
    printf("%i\n",dp[a][c+1][b][d+1]);
  }
}