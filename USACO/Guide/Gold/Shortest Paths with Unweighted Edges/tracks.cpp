#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I H=4000;
const I W=4000;

I dx[4]{1,-1,0,0};
I dy[4]{0,0,1,-1};
C cels[H][W+1];
I deps[H][W];
deque<pair<I,I>>que;
I h,w;

B bnd(I i,I j){
  return i>=0&&i<h&&j>=0&&j<w;
}

void add1(I i,I j,I dep){
  deps[i][j]=dep;
  que.push_front({i,j});
}

void add2(I i,I j,I dep){
  deps[i][j]=dep+1;
  que.push_back({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>h>>w;
  for(I i=0;i<h;i++)
    cin>>cels[i];
  add2(0,0,0);
  I res=1;
  while(que.size()){
    auto[i,j]=que.front();
    que.pop_front();
    I dep=deps[i][j];
    res=max(res,dep);
    for(I k=0;k<4;k++){
      I x=i+dx[k],y=j+dy[k];
      if(!bnd(x,y)||deps[x][y]>0||cels[x][y]=='.')continue;
      if(cels[i][j]==cels[x][y])add1(x,y,dep);
      else add2(x,y,dep);
    }
  }
  printf("%i\n",res);
  return 0;
}