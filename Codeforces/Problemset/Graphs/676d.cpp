#include<bits/stdc++.h>
 
using namespace std;
 
using I=int;
using B=bool;
using C=char;
 
const I N=1000;
const I M=1000;
const I MAX=1e9;
 
I di[]{-1,0,1,0},dj[]{0,1,0,-1};
C typs[]="+-|^><vLRUD*";
I diss[N][M][4];
queue<tuple<I,I,I>>que;
vector<pair<I,I>>adjs[N][M][4];
C cels[N][M+1];
I cons[12][4][4]{
  {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}},
  {{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}},
  {{1,0,1,0},{0,1,0,1},{1,0,1,0},{0,1,0,1}},
  {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
  {{0,1,0,0},{0,0,1,0},{0,0,0,1},{1,0,0,0}},
  {{0,0,0,1},{1,0,0,0},{0,1,0,0},{0,0,1,0}},
  {{0,0,1,0},{0,0,0,1},{1,0,0,0},{0,1,0,0}},
  {{1,1,1,0},{0,1,1,1},{1,0,1,1},{1,1,0,1}},
  {{1,0,1,1},{1,1,0,1},{1,1,1,0},{0,1,1,1}},
  {{0,1,1,1},{1,0,1,1},{1,1,0,1},{1,1,1,0}},
  {{1,1,0,1},{1,1,1,0},{0,1,1,1},{1,0,1,1}},
  {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
};
I n,m;
 
B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}
 
void add(I d,I i,I j,I k){
  if(d>=diss[i][j][k])return;
  diss[i][j][k]=d,que.push({i,j,k});
}
 
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  fill(&diss[0][0][0],&diss[0][0][0]+N*M*4,MAX);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    cels[i][j]=find(typs,typs+12,cels[i][j])-typs;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    I a=cels[i][j];
    for(I k=0;k<4;k++){
      I x=i+di[k],y=j+dj[k];
      if(!bnd(x,y))continue;
      I b=cels[x][y];
      for(I l=0;l<4;l++)
        if(cons[a][l][k]&&cons[b][l][(k+2)%4])
          adjs[i][j][l].push_back({x,y});
    }
  }
  I xt,yt;cin>>xt>>yt,xt--,yt--;
  I xm,ym;cin>>xm>>ym,xm--,ym--;
  if(cels[xt][yt]!=11)add(0,xt,yt,0);
  while(que.size()){
    auto[i,j,k]=que.front();que.pop();
    for(auto[x,y]:adjs[i][j][k])
      add(diss[i][j][k]+1,x,y,k);
    add(diss[i][j][k]+1,i,j,(k+1)%4);
  }
  I res=MAX;
  for(I i=0;i<4;i++)res=min(res,diss[xm][ym][i]);
  printf("%i\n",res==MAX?-1:res);
}