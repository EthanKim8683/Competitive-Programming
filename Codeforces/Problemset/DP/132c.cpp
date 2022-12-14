#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using B=bool;
const I M=100;
const I N=50;
B dp[M+1][2*M+1][2][N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n;cin>>n;
  I m=s.size();
  dp[0][m][0][0]=1;
  for(I i=0;i<m;i++)for(I j=-m;j<=m;j++)for(I k=0;k<2;k++)for(I l=0;l<=n;l++){
    if(!dp[i][j+m][k][l])continue;
    I t=s[i]=='T';
    I d=k?-1:1;
    for(I o=l;o<=n;o++){
      if(t)dp[i+1][j+m][!k][o]=1;
      else dp[i+1][j+m+d][k][o]=1;
      t^=1;
    }
  }
  I res=0;
  for(I i=-m;i<=m;i++)for(I j=0;j<2;j++)if(dp[m][i+m][j][n])res=max(res,abs(i));
  printf("%i\n",res);
}