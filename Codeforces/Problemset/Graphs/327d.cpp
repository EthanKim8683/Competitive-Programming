#include<iostream>
#include<cstdio>
#include<vector>
#include<tuple>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=500;
const I M=500;

I di[]{-1,1,0,0},dj[]{0,0,-1,1};
C cels[N][M+1];
B viss[N][M];
vector<tuple<C,I,I>>ress;
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void blu(I i,I j){
  ress.push_back({'B',i,j});
}

void red(I i,I j){
  ress.push_back({'D',i,j});
  ress.push_back({'R',i,j});
}

B dfs(I i,I j){
  if(!bnd(i,j)||viss[i][j]||cels[i][j]=='#')return 0;
  viss[i][j]=1;
  blu(i,j);
  for(I k=0;k<4;k++){
    I l=i+di[k],m=j+dj[k];
    if(dfs(l,m))red(l,m);
  }
  return 1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)dfs(i,j);
  printf("%i\n",ress.size());
  for(auto[c,i,j]:ress)printf("%c %i %i\n",c,i+1,j+1);
  return 0;
}