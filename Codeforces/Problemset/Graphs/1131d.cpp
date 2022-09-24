#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using C=char;
using B=bool;

const I N=1000;
const I M=1000;

C cels[N][M+1];
vector<I>adjs[N+M];
vector<I>tops;
B viss[N+M];
I invs[N+M];
I ress[N+M];
I pars[N+M];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

void dfs(I a){
  a=fnd(a);
  if(viss[a])return;
  viss[a]=1;
  for(auto b:adjs[a])dfs(b);
  tops.push_back(a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n+m,-1);
  for(I i=0;i<n;i++)cin>>cels[i];
  for(I i=0;i<n;i++)for(I j=0;j<m;j++)
    if(cels[i][j]=='=')uni(i,n+j);
  for(I i=0;i<n;i++)for(I j=0;j<m;j++){
    if(cels[i][j]=='<')adjs[fnd(i)].push_back(fnd(n+j));
    if(cels[i][j]=='>')adjs[fnd(n+j)].push_back(fnd(i));
  }
  for(I i=0;i<n+m;i++)dfs(i);
  reverse(tops.begin(),tops.end());
  for(I i=0;i<tops.size();i++)invs[tops[i]]=i;
  for(auto i:tops)for(auto j:adjs[i])
    if(invs[j]<=invs[i])printf("No\n"),exit(0);
  for(auto i:tops)for(auto j:adjs[i])
    ress[j]=max(ress[j],ress[i]+1);
  printf("Yes\n");
  for(I i=0;i<n;i++)printf("%i ",ress[fnd(i)]+1);
  printf("\n");
  for(I i=0;i<m;i++)printf("%i ",ress[fnd(i+n)]+1);
}