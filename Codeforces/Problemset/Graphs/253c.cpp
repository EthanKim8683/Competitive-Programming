#include<iostream>
#include<cstdio>
#include<queue>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=100;
const I A=1e5;
const I MAX=1e9;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
I a_arr[N];
I diss[N][A+1];
queue<pair<I,I>>que;
I n;

void fix(I&i,I&j){
  i=max(min(i,n-1),0);
  j=max(min(j,a_arr[i]),0);
}

void add(I i,I j,I d){
  fix(i,j);
  if(d>=diss[i][j])return;
  que.push({i,j}),diss[i][j]=d;
}

I main(){
#ifndef ETHANKIM8683
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I r1,c1,r2,c2;cin>>r1>>c1>>r2>>c2,r1--,c1--,r2--,c2--;
  add(r1,c1,0);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    for(I k=0;k<4;k++)
      add(i+dx[k],j+dy[k],diss[i][j]+1);
  }
  printf("%i\n",diss[r2][c2]);
  return 0;
}