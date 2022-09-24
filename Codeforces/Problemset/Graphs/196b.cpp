#include<bits/stdc++.h>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1500;
const I M=1500;

I di[]{-1,1,0,0},dj[]{0,0,-1,1};
C cels[N][M+1];
I pars[N*M];
vector<tuple<I,I,I>>adjs[N*M];
I viss1[N*M];
B viss2[N+M];
pair<I,I>cycs[N*M];
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

I ind(I i,I j){
  return i*m+j;
}

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

B dfs(I a,pair<I,I>cyc={0,0}){
  if(viss1[a]==1)return cyc!=cycs[a];
  if(viss1[a]==2)return 0;
  viss1[a]=1;
  cycs[a]=cyc;
  for(auto[b,i,t]:adjs[a]){
    if(viss2[i])continue;
    viss2[i]=1;
    auto[x,y]=cyc;
    if(dfs(b,{x+di[t],y+dj[t]}))return 1;
  }
  viss1[a]=2;
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  fill_n(pars,n*m,-1);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]=='#')continue;
    for(I k=0;k<4;k++){
      I x=i+di[k],y=j+dj[k];
      if(!bnd(x,y)||cels[x][y]=='#')continue;
      uni(ind(i,j),ind(x,y));
    }
  }
  I cur=0;
  for(I i=0;i<n;i++){
    if(cels[i][0]=='#'||cels[i][m-1]=='#')continue;
    I a=fnd(ind(i,0)),b=fnd(ind(i,m-1));
    adjs[a].push_back({b,cur,0});
    adjs[b].push_back({a,cur,1});
    cur++;
  }
  for(I i=0;i<m;i++){
    if(cels[0][i]=='#'||cels[n-1][i]=='#')continue;
    I a=fnd(ind(0,i)),b=fnd(ind(n-1,i));
    adjs[a].push_back({b,cur,2});
    adjs[b].push_back({a,cur,3});
    cur++;
  }
  I r;
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    if(cels[i][j]=='S')r=fnd(ind(i,j));
  printf("%s\n",dfs(r)?"Yes":"No");
}