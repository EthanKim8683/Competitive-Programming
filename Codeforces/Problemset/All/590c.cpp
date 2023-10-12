#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=1000;
const I M=1000;
const I MAX=1e8;
C maps[N][M+1];
I diss[3][N][M];
I dx[]{-1,0,1,0},dy[]{0,-1,0,1};
deque<pair<I,I>>ques;
I pirs[3][3];
I n,m;
void add(I t,I i,I j,I dis){
  if(i<0||i>=n||j<0||j>=m||maps[i][j]=='#')return;
  I cst=maps[i][j]=='.';
  if(dis+cst>=diss[t][i][j])return;
  diss[t][i][j]=dis+cst;
  if(cst==0)ques.push_front({i,j});
  if(cst==1)ques.push_back({i,j});
}
void bfs(I t){
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)if(maps[i][j]==t+'1')add(t,i,j,0);
  while(ques.size()){
    auto[i,j]=ques.front();ques.pop_front();
    for(I k=0;k<4;k++)add(t,i+dx[k],j+dy[k],diss[t][i][j]);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss[0][0][0],&diss[0][0][0]+3*N*M,MAX);
  fill(&pirs[0][0],&pirs[0][0]+3*3,MAX);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>maps[i];
  for(I i=0;i<3;i++)bfs(i);
  I res=MAX;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    for(I k=0;k<3;k++)for(I l=k+1;l<3;l++)pirs[k][l]=min(pirs[k][l],diss[k][i][j]+diss[l][i][j]-(maps[i][j]=='.'));
    res=min(res,diss[0][i][j]+diss[1][i][j]+diss[2][i][j]-2*(maps[i][j]=='.'));
  }
  for(I i=0;i<3;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++){
    if(i==j||j==k||i==k)continue;
    res=min(res,pirs[i][j]+pirs[j][k]);
  }
  printf("%i\n",res==MAX?-1:res);
}