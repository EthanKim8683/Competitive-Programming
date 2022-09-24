#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=105;

I di[]{-1,1,0,0},dj[]{0,0,-1,1};
queue<pair<I,I>>que;
I diss[2*N][2*N];
I n;

void add(I d,I i,I j){
  if(d>=diss[i][j])return;
  diss[i][j]=d,que.push({i,j});
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  fill(&diss[0][0],&diss[0][0]+2*N*2*N,n);
  add(0,N,N);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    for(I k=0;k<4;k++)add(diss[i][j]+1,i+di[k],j+dj[k]);
  }
  I res=0;
  for(I i=0;i<2*N;i++)for(I j=0;j<2*N;j++)res+=diss[i][j]<n;
  printf("%i\n",res);
}