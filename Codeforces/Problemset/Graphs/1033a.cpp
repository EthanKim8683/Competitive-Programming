#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=1000;

I dx[]{-1,-1,-1,0,0,1,1,1},dy[]{-1,0,1,-1,1,-1,0,1};
B chks[N][N];
B viss[N][N];
I n;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<n;
}

void dfs(I i,I j){
  if(!bnd(i,j)||viss[i][j]||chks[i][j])return;
  viss[i][j]=true;
  for(I k=0;k<8;k++)dfs(i+dx[k],j+dy[k]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  I ax,ay;cin>>ax>>ay,ax--,ay--;
  I bx,by;cin>>bx>>by,bx--,by--;
  I cx,cy;cin>>cx>>cy,cx--,cy--;
  for(I i=0;bnd(ax+i,ay+i);i++)chks[ax+i][ay+i]=true;
  for(I i=0;bnd(ax+i,ay-i);i++)chks[ax+i][ay-i]=true;
  for(I i=0;bnd(ax-i,ay+i);i++)chks[ax-i][ay+i]=true;
  for(I i=0;bnd(ax-i,ay-i);i++)chks[ax-i][ay-i]=true;
  for(I i=0;bnd(ax-i,ay);i++)chks[ax-i][ay]=true;
  for(I i=0;bnd(ax+i,ay);i++)chks[ax+i][ay]=true;
  for(I i=0;bnd(ax,ay-i);i++)chks[ax][ay-i]=true;
  for(I i=0;bnd(ax,ay+i);i++)chks[ax][ay+i]=true;
  dfs(bx,by);
  if(viss[cx][cy])printf("YES\n");
  else printf("NO\n");
  return 0;
}