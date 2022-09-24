#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1e3;
const I M=1e3;

I dx[]{0,0,-1,1},dy[]{-1,1,0,0};
C cels[N][M+1];
vector<I>adjs[N*M];
vector<I>tops;
B viss[N*M];
I invs[N*M];
I dp[N*M];
I n,m;

B bnd(I i,I j){
  return i>=0&&i<n&&j>=0&&j<m;
}

C mov(C a){
  if(a=='D')return 'I';
  if(a=='I')return 'M';
  if(a=='M')return 'A';
  if(a=='A')return 'D';
  exit(1);
}

I ind(I i,I j){
  return i*m+j;
}

void dfs(I a){
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    for(I k=0;k<4;k++){
      I x=i+dx[k],y=j+dy[k];
      if(bnd(x,y)&&mov(cels[i][j])==cels[x][y])
        adjs[ind(i,j)].push_back(ind(x,y));
    }
  }
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    if(cels[i][j]=='D')dfs(ind(i,j));
  reverse(tops.begin(),tops.end());
  for(I i=0;i<tops.size();i++)invs[tops[i]]=i;
  for(auto i:tops)for(auto j:adjs[i])
    if(invs[j]<invs[i])printf("Poor Inna!"),exit(0);
  fill_n(dp,tops.size(),1);
  I res=0;
  for(auto i:tops)for(auto j:adjs[i])
    res=max(res,dp[j]=max(dp[j],dp[i]+1));
  res/=4;
  if(res==0)printf("Poor Dima!"),exit(0);
  printf("%i\n",res);
}