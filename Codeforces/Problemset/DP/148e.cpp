#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I M=10000;
const I L=100;
vector<I>rows[N];
Lli dp1[N+1][M+1];
Lli dp3[N][L+1];
Lli dp2[L+1][L+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I l;cin>>l;
    rows[i].resize(l);
    for(I j=0;j<l;j++)cin>>rows[i][j];
  }
  for(I i=0;i<n;i++){
    I l=rows[i].size();
    for(I j=0;j<=l;j++)for(I k=0;k<=l;k++)dp2[j][k]=0;
    for(I j=l;j>=0;j--)for(I k=0;k+j<=l;k++){
      if(j>=1){
        dp2[k][k+j-1]=max(dp2[k][k+j-1],dp2[k][k+j]+rows[i][k+j-1]);
        dp2[k+1][k+j]=max(dp2[k+1][k+j],dp2[k][k+j]+rows[i][k]);
      }
      dp3[i][l-j]=max(dp3[i][l-j],dp2[k][k+j]);
    }
  }
  for(I i=0;i<n;i++){
    I l=rows[i].size();
    for(I j=0;j<=m;j++)for(I k=0;k<=l&&j+k<=m;k++)dp1[i+1][j+k]=max(dp1[i+1][j+k],dp1[i][j]+dp3[i][k]);
  }
  printf("%lli\n",*max_element(dp1[n],dp1[n]+m+1));
}