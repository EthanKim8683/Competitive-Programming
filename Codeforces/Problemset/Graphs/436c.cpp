#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<tuple>

using namespace std;

using I=int;
using C=char;
using B=bool;
using Lli=long long int;

const I N=10;
const I M=10;
const I K=1000;

C cels[K][N][M];
vector<tuple<Lli,I,I>>edgs;
I pars[K+1];
vector<I>adjs[K+1];
B viss[K+1];
vector<pair<I,I>>ress;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

B uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return 0;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  return 1;
}

void dfs(I a){
  viss[a]=1;
  for(auto b:adjs[a]){
    if(viss[b])continue;
    ress.push_back({b,a});
    dfs(b);
  }
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k,w;cin>>n>>m>>k>>w;
  fill_n(pars,k+1,-1);
  for(I i=0;i<k;i++)for(I j=0;j<n;j++)cin>>cels[i][j];
  for(I i=0;i<k;i++)for(I j=i+1;j<k;j++){
    Lli cst=0;
    for(I k=0;k<n;k++)for(I l=0;l<m;l++)
      cst+=(cels[i][k][l]!=cels[j][k][l])*w;
    edgs.push_back({cst,i+1,j+1});
  }
  for(I i=0;i<k;i++)edgs.push_back({n*m,0,i+1});
  sort(edgs.begin(),edgs.end());
  Lli res=0;
  for(auto[w,i,j]:edgs){
    if(!uni(i,j))continue;
    res+=w;
    adjs[i].push_back(j);
    adjs[j].push_back(i);
  }
  dfs(0);
  printf("%lli\n",res);
  for(auto[i,j]:ress)printf("%i %i\n",i,j);
  return 0;
}