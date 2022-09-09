#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=50;
const I M=50;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[N][M];
queue<pair<I,I>>que;
B viss[N][M];
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void add(I i,I j){
  if(!bnd(i,j)||viss[i][j]||cels[i][j]=='#')return;
  viss[i][j]=true;
  que.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>m;
    fill(&viss[0][0],&viss[0][0]+sizeof(viss)/sizeof(B),false);
    for(I i=0;i<n;i++)cin>>cels[i];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      if(cels[i][j]!='B')continue;
      for(I k=0;k<4;k++){
        I l=i+dx[k],m=j+dy[k];
        if(bnd(l,m)&&cels[l][m]=='.')cels[l][m]='#';
      }
    }
    add(n-1,m-1);
    while(que.size()){
      auto[i,j]=que.front();que.pop();
      for(I k=0;k<4;k++)add(i+dx[k],j+dy[k]);
    }
    B res=true;
    for(I i=0;i<n;i++)for(I j=0;j<m;j++){
      if(cels[i][j]=='G'&&!viss[i][j])res=false;
      if(cels[i][j]=='B'&&viss[i][j])res=false;
    }
    if(res)printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}