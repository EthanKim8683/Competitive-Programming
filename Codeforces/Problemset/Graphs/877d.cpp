#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1000;
const I M=1000;
const I MAX=1e9;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[N][M+1];
I diss1[N][M][4],diss2[N][M][4];
priority_queue<tuple<I,I,I,I,I>>que;
I n,m,k;

B bnd(I x,I y){
  return x>=0&&x<n&&y>=0&&y<m;
}

void add(I d1,I d2,I x,I y,I z){
  if(!bnd(x,y)||cels[x][y]=='#')return;
  d1+=d2/k,d2%=k;
  if(d1>diss1[x][y][z])return;
  if(d1>=diss1[x][y][z]&&d2>=diss2[x][y][z])return;
  que.push({-(diss1[x][y][z]=d1),-(diss2[x][y][z]=d2),x,y,z});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&diss1[0][0][0],&diss1[0][0][0]+N*M*4,MAX);
  fill(&diss2[0][0][0],&diss2[0][0][0]+N*M*4,MAX);
  cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>cels[i];
  I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2,x1--,y1--,x2--,y2--;
  for(I i=0;i<4;i++)diss1[x1][y1][i]=diss1[x1][y1][i]=0;
  for(I i=0;i<4;i++)add(1,0,x1+dx[i],y1+dy[i],i);
  while(que.size()){
    auto[d1,d2,x,y,z]=que.top();que.pop();
    if((d1=-d1)!=diss1[x][y][z])continue;
    if((d2=-d2)!=diss2[x][y][z])continue;
    for(I i=0;i<4;i++){
      if(i!=z)add(d1+1,0,x+dx[i],y+dy[i],i);
      if(i==z)add(d1,d2+1,x+dx[i],y+dy[i],i);
    }
  }
  I res=MAX;
  for(I i=0;i<4;i++)res=min(res,diss1[x2][y2][i]);
  printf("%i\n",res==MAX?-1:res);
}