#include<iostream>
#include<cstdio>
#include<queue>
#include<tuple>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=100;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
B viss1[2*N+1][2*N+1];
B viss2[2*N+1][2*N+1];
queue<tuple<I,I,I>>que;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I x=N,y=N;
  viss1[x][y]=true;
  for(auto c:s){
    x+=(c=='R')-(c=='L');
    y+=(c=='U')-(c=='D');
    viss1[x][y]=true;
  }
  viss2[N][N]=true;
  que.push({N,N,0});
  while(que.size()){
    auto[cx,cy,d]=que.front();que.pop();
    if(cx==x&&cy==y){
      if(d==s.size())printf("OK\n");
      else printf("BUG\n");
      break;
    }
    for(I i=0;i<4;i++){
      I nx=cx+dx[i],ny=cy+dy[i];
      if(!viss1[nx][ny]||viss2[nx][ny])continue;
      viss2[nx][ny]=true;
      que.push({nx,ny,d+1});
    }
  }
  return 0;
}