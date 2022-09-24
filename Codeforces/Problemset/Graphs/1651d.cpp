#include<iostream>
#include<cstdio>
#include<set>
#include<map>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
set<pair<I,I>>pnts;
map<pair<I,I>,pair<I,I>>ress;
queue<pair<I,I>>que;
pair<I,I>cors[N];

void add(I i,I j,pair<I,I>res){
  if(pnts.find({i,j})==pnts.end()||ress.find({i,j})!=ress.end())return;
  que.push({i,j}),ress[{i,j}]=res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts.insert({x,y});
    cors[i]={x,y};
  }
  for(I i=0;i<n;i++){
    auto[x,y]=cors[i];
    for(I j=0;j<4;j++){
      pair<I,I>res={x+dx[j],y+dy[j]};
      if(pnts.find(res)==pnts.end()){add(x,y,res);break;}
    }
  }
  while(que.size()){
    auto[x,y]=que.front();que.pop();
    for(I i=0;i<4;i++)add(x+dx[i],y+dy[i],ress[{x,y}]);
  }
  for(I i=0;i<n;i++){
    auto[x,y]=cors[i];
    auto[z,w]=ress[{x,y}];
    printf("%i %i\n",z,w);
  }
  return 0;
}