#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I R=500;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[R][R+1];
B viss[R][R];
I r,c;

B bnd(I i,I j){
  return i>=0&&i<r&&j>=0&&j<c;
}

B fil(I i,I j){
  if(!bnd(i,j)||viss[i][j])return false;
  viss[i][j]=true;
  if(cels[i][j]=='D')return false;
  if(cels[i][j]=='S')return true;
  B res=false;
  for(I k=0;k<4;k++)
    res|=fil(i+dx[k],j+dy[k]);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>r>>c;
  for(I i=0;i<r;i++)cin>>cels[i];
  for(I i=0;i<r;i++)for(I j=0;j<c;j++)
    if(cels[i][j]=='.')cels[i][j]='D';
  for(I i=0;i<r;i++)for(I j=0;j<c;j++){
    if(cels[i][j]=='W'&&fil(i,j)){
      printf("No\n");
      return 0;
    }
  }
  printf("Yes\n");
  for(I i=0;i<r;i++)
    printf("%s\n",cels[i]);
  return 0;
}