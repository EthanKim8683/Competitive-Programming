#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
using B=bool;
const I N=500;
const I M=500;
I dx[]{-1,0,1,0},dy[]{0,-1,0,1};
C cels[N][M+1];
B viss[N][M];
I n,m;
void dfs(I i,I j){
  if(i<0||i>=n||j<0||j>=m)return;
  if(viss[i][j])return;
  viss[i][j]=1;
  if(cels[i][j]=='X')return;
  for(I k=0;k<4;k++)dfs(i+dx[k],j+dy[k]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  I r1,c1;cin>>r1>>c1,r1--,c1--;
  I r2,c2;cin>>r2>>c2,r2--,c2--;
  for(I i=0;i<4;i++)dfs(r1+dx[i],c1+dy[i]);
  if(!viss[r2][c2])printf("NO\n"),exit(0);
  if(cels[r2][c2]=='X')printf("YES\n"),exit(0);
  B res=0;
  for(I i=0;i<4;i++){
    I x=r2+dx[i],y=c2+dy[i];
    if(x<0||x>=n||y<0||y>=m)continue;
    if(cels[x][y]=='X')continue;
    for(I j=0;j<n;j++)for(I k=0;k<m;k++)viss[j][k]=0;
    viss[x][y]=1;
    for(I j=0;j<4;j++)dfs(r1+dx[j],c1+dy[j]);
    res|=viss[r2][c2];
  }
  printf("%s\n",res?"YES":"NO");
}