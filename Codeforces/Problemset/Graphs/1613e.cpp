#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<set>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=1e6;

I di[]{-1,1,0,0},dj[]{0,0,-1,1};
S cels[N];
set<pair<I,I>>viss;
queue<pair<I,I>>que;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m&&cels[i][j]!='#';
}

void add(I i,I j){
  if(!bnd(i,j)||viss.count({i,j}))return;
  viss.insert({i,j}),que.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>m;
    viss.clear();
    for(I i=0;i<n;i++)cin>>cels[i];
    for(I i=0;i<n;i++)for(I j=0;j<m;j++)
      if(cels[i][j]=='L')add(i,j);
    while(que.size()){
      auto[i,j]=que.front();que.pop();
      if(cels[i][j]!='L')cels[i][j]='+';
      for(I k=0;k<4;k++){
        I x=i+di[k],y=j+dj[k];
        I cnt=0;
        for(I l=0;l<4;l++){
          I z=x+di[l],w=y+dj[l];
          cnt+=bnd(z,w)&&!viss.count({z,w});
        }
        if(cnt<=1)add(x,y);
      }
    }
    for(I i=0;i<n;i++)printf("%s\n",cels[i].c_str());
  }
  return 0;
}