#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=30;
const I M=30;

I cels[N][M];
I dias[N+M-1][2];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n+m-1;i++)for(I j=0;j<2;j++)dias[i][j]=0;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>cels[i][j];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)dias[i+j][!cels[i][j]]++;
    I res=0;
    for(I l=0,r=n+m-2;l<r;l++,r--)res+=min(dias[l][0]+dias[r][0],dias[l][1]+dias[r][1]);
    printf("%i\n",res);
  }
}