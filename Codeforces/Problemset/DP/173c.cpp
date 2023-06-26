#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=500;
const I M=500;
const Lli MIN=-1e18;
I tabs[N][M];
Lli ps[N+1][M+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>tabs[i][j];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)ps[i+1][j+1]=tabs[i][j];
  for(I i=1;i<=n;i++)for(I j=1;j<=m;j++)ps[i][j]+=ps[i-1][j]+ps[i][j-1]-ps[i-1][j-1];
  Lli res=MIN;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    Lli pre=tabs[i][j];
    for(I k=3;k<=min(n,m);k+=2){
      I t=(k-1)/2,y=i-t,x=j-t;
      if(x<0||y<0||x+k>m||y+k>n)break;
      Lli cur=ps[y+k][x+k]-ps[y][x+k]-ps[y+k][x]+ps[y][x]-pre-tabs[y+1][x];
      res=max(res,cur);
      pre=cur;
    }
  }
  printf("%lli\n",res);
}