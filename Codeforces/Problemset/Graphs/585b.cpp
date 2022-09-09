#include<iostream>
#include<cstdio>
#include<queue>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=100;

I dy[]{-1,1,0};
C cels[3][N+3];
queue<pair<I,I>>que;
B viss[3][N+3];
I n;

B bnd(I i,I j){
  return i>=0&&i<3&&j>=0&&j<n+3;
}

void add(I i,I j){
  for(I k=0;k<=2;k++)
    if(!bnd(i,j+k)||cels[i][j+k]!='.')return;
  if(viss[i][j+=2])return;
  que.push({i,j}),viss[i][j]=1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I k;cin>>n>>k;
    while(que.size())que.pop();
    fill(&viss[0][0],&viss[0][0]+sizeof(viss)/sizeof(B),0);
    for(I i=0;i<3;i++)cin>>cels[i];
    for(I i=0;i<3;i++)for(I j=0;j<3;j++)cels[i][n+j]='.';
    for(I i=0;i<3;i++)if(cels[i][0]=='s')
      que.push({i,0}),viss[i][0]=1;
    B res=0;
    while(que.size()){
      auto[i,j]=que.front();que.pop();
      if(j>=n-1){res=1;break;}
      if(bnd(i,j+1)&&cels[i][j+1]=='.')for(I k=0;k<3;k++)
        add(i+dy[k],j+1);
    }
    if(res)printf("YES\n");
    else printf("NO\n");
  }
  return 0;
}