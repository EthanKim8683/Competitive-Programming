#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=1000000;
S cels[N];
vector<B>viss[N];
vector<B>cons[N];
vector<B>uses[N];
queue<pair<I,I>>que;
I n,m;
B dfs(I i,I j){
  if(i>=n||j>=m)return 0;
  if(cels[i][j]=='#')return 0;
  if(viss[i][j])return cons[i][j];
  viss[i][j]=1;
  B res=i==n-1&&j==m-1;
  res|=dfs(i+1,j);
  res|=dfs(i,j+1);
  return cons[i][j]=res;
}
void add(I i,I j){
  if(i>=n||j>=m)return;
  if(cels[i][j]=='#')return;
  if(!cons[i][j])return;
  if(uses[i][j])return;
  uses[i][j]=1;
  que.push({i,j});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n>>m;
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)viss[i].resize(m);
  for(I i=0;i<n;i++)cons[i].resize(m);
  for(I i=0;i<n;i++)uses[i].resize(m);
  I res=2;
  dfs(0,0);
  add(0,0);
  while(que.size()){
    auto[i,j]=que.front();
    if(!(i==0&&j==0)&&!(i==n-1&&j==m-1)&&que.size()==1)res=1;
    que.pop();
    add(i+1,j);
    add(i,j+1);
  }
  if(!viss[n-1][m-1])res=0;
  printf("%i\n",res);
}