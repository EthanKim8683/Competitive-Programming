#include<iostream>
#include<cstdio>
#include<queue>
#include<tuple>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=200;

B viss[N+1][N+1][N+1];
queue<tuple<I,I,I>>que;

void add(I i,I j,I k){
  if(i<0||j<0||k<0||viss[i][j][k])return;
  que.push({i,j,k}),viss[i][j][k]=1;;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  I r=0,g=0,b=0;
  for(auto c:s)r+=c=='R',g+=c=='G',b+=c=='B';
  add(r,g,b);
  B rr=0,rg=0,rb=0;
  while(que.size()){
    auto[i,j,k]=que.front();que.pop();
    rr|=i==1&&j==0&&k==0;
    rg|=i==0&&j==1&&k==0;
    rb|=i==0&&j==0&&k==1;
    add(i+1,j-1,k-1);
    add(i-1,j+1,k-1);
    add(i-1,j-1,k+1);
    if(i>=2)add(i-1,j,k);
    if(j>=2)add(i,j-1,k);
    if(k>=2)add(i,j,k-1);
  }
  if(rb)printf("B");
  if(rg)printf("G");
  if(rr)printf("R");
  return 0;
}