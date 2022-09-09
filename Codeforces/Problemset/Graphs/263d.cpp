#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;

vector<I>adjs[N];
I viss[N];
I deps[N];
I pars[N];
vector<I>ress;
I k;

B dfs(I a,I p=-1,I d=0){
  if(viss[a]==1&&d-deps[a]>k){
    for(I i=d-deps[a];i>0;i--)
      ress.push_back(p),p=pars[p];
    return 1;
  }
  if(viss[a])return 0;
  deps[a]=d;
  viss[a]=1;
  pars[a]=p;
  for(auto b:adjs[a])if(b!=p)
    if(dfs(b,a,d+1))return 1;
  viss[a]=2;
  return 0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
  return 0;
}