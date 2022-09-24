#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;
using C=char;

const I N=1e3;

pair<I,I>cels[N][N];
I di[]{-1,0,1,0},dj[]{0,-1,0,1};
C chrs[]{'D','R','U','L','X'};
I ress[N][N];
I n;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<n;
}

void dfs(I i,I j){
  for(I k=0;k<4;k++){
    I l=i+di[k],m=j+dj[k];
    if(!bnd(l,m)||cels[l][m]!=cels[i][j])continue;
    if(ress[l][m]!=-1)continue;
    ress[l][m]=k;
    dfs(l,m);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&ress[0][0],&ress[0][0]+sizeof(ress)/sizeof(I),-1);
  cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){I x,y;cin>>x>>y,cels[i][j]={x-1,y-1};}
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    if(ress[i][j]!=-1)continue;
    if(cels[i][j]!=pair<I,I>{i,j})continue;
    ress[i][j]=4;
    dfs(i,j);
  }
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    if(ress[i][j]!=-1)continue;
    if(cels[i][j]!=pair<I,I>{-2,-2})printf("INVALID\n"),exit(0);
    for(I k=0;k<4;k++){
      I l=i+di[k],m=j+dj[k];
      if(!bnd(l,m)||cels[l][m]!=cels[i][j])continue;
      ress[i][j]=(k+2)%4;
    }
    if(ress[i][j]==-1)printf("INVALID\n"),exit(0);
    dfs(i,j);
  }
  printf("VALID\n");
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++)printf("%c",chrs[ress[i][j]]);
    printf("\n");
  }
  return 0;
}