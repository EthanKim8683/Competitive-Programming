#include<iostream>
#include<cstdio>
#include<queue>
#include<set>
#include<map>

using namespace std;

using I=int;

const I N=1e5;

I dx[]{-1,1,0,0,-1,-1,1,1},dy[]{0,0,-1,1,-1,1,-1,1};
set<pair<I,I>>alls;
map<pair<I,I>,I>diss;
queue<pair<I,I>>que;

void add(I i,I j,I d){
  if(alls.find({i,j})==alls.end()||diss.find({i,j})!=diss.end())return;
  que.push({i,j}),diss[{i,j}]=d;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I x0,y0,x1,y1;cin>>x0>>y0>>x1>>y1;
  alls.insert({x0,y0});
  alls.insert({x1,y1});
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I r,a,b;cin>>r>>a>>b;
    for(I j=a;j<=b;j++)alls.insert({r,j});
  }
  add(x0,y0,0);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    I d=diss[{i,j}];
    if(i==x1&&j==y1){printf("%i\n",d);return 0;}
    for(I k=0;k<8;k++)add(i+dx[k],j+dy[k],d+1);
  }
  printf("-1\n");
  return 0;
}