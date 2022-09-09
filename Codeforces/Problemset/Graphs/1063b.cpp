#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

using I=int;
using B=bool;
using C=char;

const I N=2000,M=2000;

C cels[N][M];
pair<I,I>diss[N][M];
B viss[N][M];
deque<pair<I,I>>que;
I n,m;
I x,y;

B bnd(I i,I j,I a,I b){
  return i>=0&&i<n&&j>=0&&j<m&&a<=x&&b<=y;
}

void add(B t,I i,I j,I a,I b){
  if(!bnd(i,j,a,b)||viss[i][j]||cels[i][j]=='*')return;
  viss[i][j]=1,diss[i][j]={a,b};
  if(t)que.push_front({i,j});
  else que.push_back({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  I r,c;cin>>r>>c;
  cin>>x>>y;
  for(I i=0;i<n;i++)cin>>cels[i];
  add(0,r-1,c-1,0,0);
  while(que.size()){
    auto[i,j]=que.front();que.pop_front();
    auto[a,b]=diss[i][j];
    add(1,i-1,j,a,b);
    add(1,i+1,j,a,b);
    add(0,i,j-1,a+1,b);
    add(0,i,j+1,a,b+1);
  }
  I res=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    res+=viss[i][j];
  printf("%i\n",res);
  return 0;
}