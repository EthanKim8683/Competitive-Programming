#include<iostream>
#include<cstdio>
#include<queue>
#include<tuple>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1000;
const I M=1000;
const I MAX=2+1;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
I trns[N][M][4];
C cels[N][M];
priority_queue<tuple<I,I,I,I>>que;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void add(I t,I i,I j,I d){
  if(!bnd(i,j)||cels[i][j]=='*'||t>=trns[i][j][d])return;
  que.push({-(trns[i][j][d]=t),i,j,d});
}

I main(){
  fill(&trns[0][0][0],&trns[0][0][0]+sizeof(trns)/sizeof(I),MAX);
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  I si,sj,ti,tj;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]=='S')si=i,sj=j;
    if(cels[i][j]=='T')ti=i,tj=j;
  }
  for(I i=0;i<4;i++)add(0,si,sj,i);
  while(que.size()){
    auto[t,i,j,d]=que.top();que.pop();
    if((t*=-1)!=trns[i][j][d])continue;
    for(I k=0;k<4;k++)
      add(t+(k!=d),i+dx[k],j+dy[k],k);
  }
  I res=MAX;
  for(I i=0;i<4;i++)res=min(res,trns[ti][tj][i]);
  if(res==MAX)printf("NO\n");
  else printf("YES\n");
  return 0;
}