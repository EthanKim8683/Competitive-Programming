#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1000;
const I M=1000;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[N][M];
pair<I,I>pars[N][M];
I ress[N][M];
B viss[N][M];
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I dfs(I i,I j,I k,I l){
  if(viss[i][j])return 0;
  if(cels[i][j]=='*')return 1;
  viss[i][j]=true;
  I res=0;
  for(I m=0;m<4;m++)
    res+=dfs(i+dx[m],j+dy[m],k,l);
  pars[i][j]={k,l};
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<k;i++){
    I x,y;cin>>x>>y,x--,y--;
    if(!viss[x][y])ress[x][y]=dfs(x,y,x,y);
    auto[z,w]=pars[x][y];
    printf("%i\n",ress[z][w]);
  }
  return 0;
}