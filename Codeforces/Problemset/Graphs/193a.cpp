#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=50;
const I M=50;

I dx[]{-1,1,0,0},dy[]{0,0,-1,1};
C cels[N][M];
B viss[N][M];
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I dfs(I i,I j){
  if(!bnd(i,j)||cels[i][j]!='#'||viss[i][j])return 0;
  viss[i][j]=1;
  I res=1;
  for(I k=0;k<4;k++)res+=dfs(i+dx[k],j+dy[k]);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  I cnt=0;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    cnt+=cels[i][j]=='#';
  if(cnt<=2){printf("-1\n");return 0;}
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]!='#')continue;
    fill(&viss[0][0],&viss[0][0]+sizeof(viss)/sizeof(B),0);
    viss[i][j]=1;
    B trv=0;
    I tot;
    for(I k=0;k<n&&!trv;k++)for(I l=0;l<m&&!trv;l++){
      if(cels[k][l]!='#'||(k==i&&l==j))continue;
      tot=dfs(k,l),trv=1;
    }
    if(tot!=cnt-1){printf("1\n");return 0;}
  }
  printf("2\n");
  return 0;
}