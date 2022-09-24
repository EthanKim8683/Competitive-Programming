#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=100;

I di[]{-1,0,1,-1,1,-1,0,1},dj[]{-1,-1,-1,0,0,1,1,1};
C cels[2][N];
B viss[2][N];
queue<pair<I,I>>que;
I n;

B bnd(I i,I j){
  return i>=0&&i<2&&j>=0&&j<n;
}

void add(I i,I j){
  if(!bnd(i,j)||cels[i][j]=='1'||viss[i][j])return;
  viss[i][j]=1,que.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    fill(&viss[0][0],&viss[0][0]+2*N,0);
    cin>>n;
    for(I i=0;i<2;i++)cin>>cels[i];
    add(0,0);
    while(que.size()){
      auto[i,j]=que.front();que.pop();
      for(I k=0;k<8;k++)add(i+di[k],j+dj[k]);
    }
    printf("%s\n",viss[1][n-1]?"YES":"NO");
  }
}