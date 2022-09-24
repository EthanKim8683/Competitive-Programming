#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=300;

Lli diss[N][N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>diss[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)for(I k=0;k<n;k++)
    diss[j][k]=min(diss[j][k],diss[j][i]+diss[i][k]);
  I k;cin>>k;
  for(I i=0;i<k;i++){
    I a,b,c;cin>>a>>b>>c,a--,b--;
    for(I j=0;j<n;j++){
      diss[j][b]=min(diss[j][b],diss[j][a]+c);
      diss[j][a]=min(diss[j][a],diss[j][b]+c);
      diss[b][j]=min(diss[b][j],c+diss[a][j]);
      diss[a][j]=min(diss[a][j],c+diss[b][j]);
    }
    for(I j=0;j<n;j++)for(I k=0;k<n;k++){
      diss[j][k]=min(diss[j][k],diss[j][a]+diss[a][k]);
      diss[j][k]=min(diss[j][k],diss[j][b]+diss[b][k]);
    }
    Lli res=0;
    for(I i=0;i<n;i++)for(I j=i+1;j<n;j++)res+=diss[i][j];
    printf("%lli ",res);
  }
  return 0;
}