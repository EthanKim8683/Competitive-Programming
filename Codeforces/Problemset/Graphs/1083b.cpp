#include<iostream>
#include<cstdio>
#include<deque>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=2000,M=2000;
const I MAX=1e9;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1},csts[]{0,0,1,1};
C cels[N][M];
I diss[N][M];
deque<pair<I,I>>que;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void add(I i,I j,I d,I c){
  d+=c;
  if(!bnd(i,j)||d>=diss[i][j]||cels[i][j]=='*')return;
  diss[i][j]=d;
  if(c)que.push_back({i,j});
  else que.push_front({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  I r,c;cin>>r>>c;
  I x,y;cin>>x>>y;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<n;i++)cin>>cels[i];
  add(r-1,c-1,0,0);
  while(que.size()){
    auto[i,j]=que.front();que.pop_front();
    for(I k=0;k<4;k++)add(i+dx[k],j+dy[k],diss[i][j],csts[k]);
  }
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)res+=diss[i][j]!=MAX;
  printf("%i\n",res);
  for(I i=0;i<n;i++){
    for(I j=0;j<m;j++)printf("%i",diss[i][j]!=MAX);
    printf("\n");
  }
  return 0;
}