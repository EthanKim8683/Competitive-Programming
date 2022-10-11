#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=500;
const I M=500;

C cels[N][M];
I ps[N][M+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)for(I j=0;j<=m;j++)ps[i][j]=0;
    for(I i=0;i<n;i++)cin>>cels[i];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i][j+1]=cels[i][j]=='*';
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i][j+1]+=ps[i][j];
    I res=0;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)for(I k=0;i+k<n;k++,res++)
      if(ps[i+k][min(j+k,m-1)+1]-ps[i+k][max(j-k,0)]!=2*k+1)break;
    printf("%i\n",res);
  }
}