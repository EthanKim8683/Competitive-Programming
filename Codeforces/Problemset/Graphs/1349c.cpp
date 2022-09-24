#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

using I=int;
using C=char;
using B=bool;
using Lli=long long int;

const I N=1000;
const I M=1000;
const Lli MAX=1e18+5;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[N][M+1];
B viss1[N][M],viss2[N][M];
Lli diss[N][M];
queue<pair<I,I>>que;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void add(I i,I j,Lli d){
  if(d>=diss[i][j])return;
  que.push({i,j}),diss[i][j]=d;
}

void dfs2(I i,I j,Lli d){
  if(!bnd(i,j)||viss2[i][j])return;
  viss2[i][j]=1;
  add(i,j,d);
  for(I k=0;k<4;k++){
    I x=i+dx[k],y=j+dy[k];
    if(cels[i][j]==cels[x][y])dfs2(i+dx[k],j+dy[k],d);
  }
}

I dfs1(I i,I j){
  if(!bnd(i,j)||viss1[i][j])return 0;
  viss1[i][j]=1;
  I siz=1;
  for(I k=0;k<4;k++){
    I x=i+dx[k],y=j+dy[k];
    if(cels[i][j]==cels[x][y])siz+=dfs1(i+dx[k],j+dy[k]);
  }
  if(siz>1)dfs2(i,j,0);
  return siz;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>n>>m>>t;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(Lli),MAX);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)cels[i][j]-='0';
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)dfs1(i,j);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    for(I k=0;k<4;k++)dfs2(i+dx[k],j+dy[k],diss[i][j]+1);
  }
  while(t--){
    I i,j;Lli t;cin>>i>>j>>t,i--,j--;
    Lli d=diss[i][j];
    if(t<d)printf("%i\n",cels[i][j]);
    else printf("%i\n",cels[i][j]^((t-d)%2));
  }
  return 0;
}