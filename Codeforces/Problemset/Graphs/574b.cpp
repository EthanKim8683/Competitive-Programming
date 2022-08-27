#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=4000;
const I MAX=1e9;

vector<I>adjs[N];
I wars[3];
B viss[N];
I res=MAX;
I dep=0;

void chk(){
  I sum=0;
  for(I i=0;i<3;i++)
    sum+=adjs[wars[i]].size();
  res=min(res,sum-6);
}

void dfs(I a,I p=-1){
  if(viss[a]){chk();return;}
  if(dep==3)return;
  viss[a]=true;
  wars[dep]=a;
  dep++;
  for(auto b:adjs[a]){
    if(b==p)continue;
    dfs(b,a);
  }
  dep--;
  viss[a]=false;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++){
    fill_n(viss,n,false);
    dfs(i);
  }
  if(res==MAX)printf("-1\n");
  else printf("%i\n",res);
  return 0;
}