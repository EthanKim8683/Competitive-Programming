#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using S=string;
using B=bool;

const I N=20;
const I M=20;

B viss[N][M];
I n,m;
S a,b;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I dfs(I i,I j){
  if(!bnd(i,j)||viss[i][j])return 0;
  viss[i][j]=true;
  I res=1;
  if(a[i]=='>')res+=dfs(i,j+1);
  if(a[i]=='<')res+=dfs(i,j-1);
  if(b[j]=='v')res+=dfs(i+1,j);
  if(b[j]=='^')res+=dfs(i-1,j);
  return res;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  cin>>a;
  cin>>b;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    fill(&viss[0][0],&viss[0][0]+sizeof(viss)/sizeof(B),false);
    if(dfs(i,j)!=n*m){printf("NO\n");return 0;}
  }
  printf("YES\n");
  return 0;
}