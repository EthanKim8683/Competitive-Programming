#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=500;
const I M=500;
const I X=16;
const I Y=1e6;
I a_arr[N][M];
I viss[Y+1];
I adjs[Y+1][X+1];
I ress[X+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cin>>a_arr[i][j];
  for(I i=1;i<=X;i++)for(I j=i;j<=Y;j+=i)viss[j]++;
  I upp=-1;
  for(I i=1;i<=Y;i++)if(viss[i]==X)upp=i;
  for(I i=1;i<=X;i++)for(I j=i;j<=Y;j+=i)for(I k=1;j+k*k*k*k<=upp;k++)if(j+k*k*k*k==upp)ress[i]=j;
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)printf("%i ",(i+j)%2?upp:ress[a_arr[i][j]]);
    printf("\n");
  }
}