#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

using I=int;
using C=char;
using B=bool;
using S=string;

const I N=1000;
const I M=1000;
const I MAX=1e9;

I di[]{1,0,0,-1},dj[]{0,-1,1,0};
C chrs[]{'D','L','R','U'};
C cels[N][M];
I deps[N][M];
queue<pair<I,I>>que;
S res="";
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

void dfs(I i,I j,I k){
  if(k==0)return;
  for(I l=0;l<4;l++){
    I a=i+di[l],b=j+dj[l];
    if(!bnd(a,b)||cels[a][b]=='*'||deps[a][b]>k-1)continue;
    res+=chrs[l];
    dfs(a,b,k-1);
    break;
  }
}

void add(I i,I j,I d){
  if(!bnd(i,j)||d>=deps[i][j]||cels[i][j]=='*')return;
  que.push({i,j}),deps[i][j]=d;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>n>>m>>k;
  fill(&deps[0][0],&deps[0][0]+sizeof(deps)/sizeof(I),MAX);
  if(k%2){printf("IMPOSSIBLE\n");return 0;}
  for(I i=0;i<n;i++)cin>>cels[i];
  I xi,xj;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    if(cels[i][j]=='X')xi=i,xj=j;
  add(xi,xj,0);
  while(que.size()){
    auto[i,j]=que.front();que.pop();
    for(I k=0;k<4;k++)add(i+di[k],j+dj[k],deps[i][j]+1);
  }
  dfs(xi,xj,k);
  if(res.size())printf("%s\n",res.c_str());
  else printf("IMPOSSIBLE\n");
  return 0;
}