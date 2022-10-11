#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;

const I N=50;
const I M=50;
const I MAX=1e5;

C cels[N][M+1];
I diss[N][3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]>='0'&&cels[i][j]<='9')cels[i][j]=0;
    if(cels[i][j]>='a'&&cels[i][j]<='z')cels[i][j]=1;
    if(cels[i][j]=='#'||cels[i][j]=='*'||cels[i][j]=='&')cels[i][j]=2;
  }
  for(I i=0;i<n;i++)for(I j=0;j<3;j++){
    diss[i][j]=MAX;
    for(I k=0,l=0;k<m;k++,l=(l+1+m)%m)if(cels[i][l]==j)diss[i][j]=min(diss[i][j],k);
    for(I k=0,l=0;k<m;k++,l=(l-1+m)%m)if(cels[i][l]==j)diss[i][j]=min(diss[i][j],k);
  }
  I res=MAX;
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++){
      for(I k=0;k<n;k++){
        if(i==j)continue;
        if(j==k)continue;
        if(i==k)continue;
        res=min(res,diss[i][0]+diss[j][1]+diss[k][2]);
      }
    }
  }
  printf("%i\n",res);
}