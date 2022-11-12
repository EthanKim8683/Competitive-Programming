#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=400;
const I M=400;
const I MAX=1e9;

C cels[N][M+1];
I psv[M][N+1];
I psh[M+1];
I psm[M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>cels[i];
    for(I i=0;i<m;i++)for(I j=0;j<=n;j++)psv[i][j]=0;
    for(I i=0;i<=m;i++)psh[i]=psm[i]=0;
    for(I i=0;i<m;i++)for(I j=0;j<n;j++)psv[i][j+1]=cels[j][i]=='1';
    for(I i=0;i<m;i++)for(I j=0;j<n;j++)psv[i][j+1]+=psv[i][j];
    I res=MAX;
    for(I i=0;i<n;i++)for(I j=5;i+j<=n;j++){
      for(I k=0;k<m;k++)psh[k+1]=1-(psv[k][i+1]-psv[k][i])+1-(psv[k][i+j]-psv[k][i+j-1])+psv[k][i+j-1]-psv[k][i+1];
      for(I k=0;k<m;k++)psh[k+1]+=psh[k];
      for(I k=0;k<m;k++)psm[k]=psh[k+1]-(j-2-(psv[k][i+j-1]-psv[k][i+1]));
      for(I k=0;k<m;k++)psm[k+1]=max(psm[k+1],psm[k]);
      for(I k=3;k<m;k++)res=min(res,psh[k]-psm[k-3]+j-2-(psv[k][i+j-1]-psv[k][i+1]));
    }
    printf("%i\n",res);
  }
}